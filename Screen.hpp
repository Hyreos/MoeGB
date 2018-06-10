#pragma once

#include <SFML/Graphics.hpp>

class Screen {
public:
    Screen() {
        m_screenBuffer.create(256, 256);
        m_view.setSize(sf::Vector2f(160, 144)); 
        m_screenBuffer.setView(m_view);
        m_screenBuffer.setRepeated(true);
    }

    ~Screen() = default;

    sf::Sprite& getSprite() {
        return m_sprite;
    }

    sf::RenderTexture& getScreenbuffer() {
        return m_screenBuffer;
    }

    sf::View& getView() {
        return m_view;
    }

    void setCoord(sf::Vector2f coord) {
        m_sprite.setPosition(coord);
    }
private:
    sf::Sprite m_sprite;
    sf::RenderTexture m_screenBuffer;
    sf::View m_view;
};