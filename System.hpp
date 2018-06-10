#pragma once

#include "Cpu.hpp"
#include "Mmu.hpp"
#include "Cartrigbe.hpp"
#include "Screen.hpp"
#include "Bootstrap.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

class System {
public:
    System() {}

    void start(std::string_view file) {
        std::cout << "starting" << std::endl;
        m_pWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(256, 256), "MoeGB");
        auto cart = Cartrigbe(file);
        cpu().boot(cart);
        update();
    }

    Cpu& cpu() noexcept;

    sf::RenderWindow& window();
private:
    void update();

    std::unique_ptr<sf::RenderWindow> m_pWindow;
    sf::Event m_event;

    Screen m_screen;
    Cpu m_cpu;
    MMU m_mmu;
};