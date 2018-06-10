#include "System.hpp"

#include "Cpu.hpp"
#include "Mmu.hpp"
#include "Cartrigbe.hpp"
#include "Screen.hpp"
#include "Bootstrap.hpp"

void System::update() {
    sf::Sprite sprScreen;
    sprScreen.setPosition(sf::Vector2f(0.f, 0.f));
    sprScreen.setTexture(cpu().screen().getScreenbuffer().getTexture());

    while(m_pWindow->isOpen()) {
        cpu().update();

        while(m_pWindow->pollEvent(m_event)) {
            switch(m_event.type) {
                case sf::Event::Closed:
                    m_pWindow->close();
                    break;
            }
        }
        m_pWindow->draw(sprScreen);
        m_pWindow->display();
        sf::sleep(sf::milliseconds(1000/60));
    }
}

Cpu& System::cpu() noexcept {
    return m_cpu;
}

sf::RenderWindow& System::window() {
    assert(m_pWindow);
    return *m_pWindow;
}