///////////////////////////////////////////////////////////////////////////////
/// @file   Game.hpp
/// @author Jacob Adkins (jpadkins)
/// @brief  A high level class representing a roguelike game
///////////////////////////////////////////////////////////////////////////////

#include "Game.hpp"

///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <iostream>
#include "State.hpp"
#include "Common.hpp"

///////////////////////////////////////////////////////////////////////////////
Game::Game(Settings& settings) : m_frameSize(settings.frame.size)
{
    m_window.create(settings.window.mode,
                    settings.window.title,
                    settings.window.style);

    if (!m_window.isOpen()) {
        log_exit("Could not open window");
    }
    else if (!m_frame.create(m_frameSize.x, m_frameSize.y)) {
        log_exit("Could not create frame buffer");
    }

    m_window.setVerticalSyncEnabled(settings.window.vsync);
    m_window.setFramerateLimit(settings.window.fpsLimit);
    m_window.setMouseCursorVisible(false);
    m_window.setActive();

    updateFrameScale();
}

///////////////////////////////////////////////////////////////////////////////
void Game::play()
{
    sf::Clock clock;

    while (m_window.isOpen()) {
        updateFrameMouseCoord();
        State::get().deltaMs = clock.restart().asMilliseconds();

        sf::Event event;
        while (m_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                case sf::Event::Resized:
                    updateFrameScale();
                    break;
                default:
                    break;
            }
        }

        updateState();
        renderFrame();

        State::get().lastMousePosition = State::get().mousePosition;
    }
}

///////////////////////////////////////////////////////////////////////////////
void Game::updateState()
{
    State::get().update();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        m_window.close();
    }
}

///////////////////////////////////////////////////////////////////////////////
void Game::renderFrame()
{
    m_frame.clear();
    m_frame.draw(State::get());
    m_frame.display();

    sf::Sprite frameSprite(m_frame.getTexture());
    frameSprite.setScale(m_frameScale);

    m_window.clear();
    m_window.draw(frameSprite);
    m_window.display();
}

///////////////////////////////////////////////////////////////////////////////
void Game::updateFrameScale()
{
    m_frameScale.x = static_cast<float>(m_window.getSize().x)
                     / static_cast<float>(m_frameSize.x);
    m_frameScale.y = static_cast<float>(m_window.getSize().y)
                     / static_cast<float>(m_frameSize.y);
}

///////////////////////////////////////////////////////////////////////////////
void Game::updateFrameMouseCoord()
{
    sf::Vector2f windowPosition = m_window.mapPixelToCoords(
        sf::Mouse::getPosition(m_window));
    State::get().mousePosition = sf::Vector2i(
        static_cast<int>(std::round(windowPosition.x / m_frameScale.x)),
        static_cast<int>(std::round(windowPosition.y / m_frameScale.y))
    );
}
