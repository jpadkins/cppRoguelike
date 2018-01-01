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
#include <cstdlib>
#include <iostream>

#include "State.hpp"
#include "Common.hpp"
#include "FrameManager.hpp"
#include "GlyphTileMap.hpp"

// TODO: Remove this
class FooFrame : public Frame {
public:

    FooFrame() = delete;

    explicit FooFrame(const std::string& tag)
        : Frame(tag), m_glyphMap(State::get().font, {10, 10}, {16, 16}, 16)
    {
        auto randColor = []() {
            return sf::Color(rand() % 255, rand() % 255, rand() % 255);
        };

        GlyphTileMap::Tile tile('x',
                                GlyphTileMap::Tile::Center,
                                randColor(),
                                randColor());

        for (int x = 0; x < m_glyphMap.getArea().x; ++x) {
            for (int y = 0; y < m_glyphMap.getArea().y; ++y) {
                m_glyphMap.setTile({x, y}, tile);
            }
        }

        setPosition((rand() % 800) - 80, (rand() % 600) - 80);
    }

    void update() override
    {
        static bool lastLeft = false;
        static bool dragging = false;

        if (consumeMouse) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!dragging && !lastLeft & Frame::focus.empty()) {
                    State::get().frameManager->setHighest(tag);
                    Frame::focus = tag;
                    dragging = true;
                }
                else if (dragging) {
                    matchLastMouseMovement();
                }
                lastLeft = true;
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                State::get().frameManager->remove(tag);
            }
            else if (dragging || lastLeft || !Frame::focus.empty()) {
                Frame::focus.clear();
                lastLeft = false;
                dragging = false;
            }
            consumeMouse = false;
        }
    }

    bool containsMouse() const override
    {
        return containsCoord(State::get().mousePosition);
    }

    bool containsCoord(const sf::Vector2i& coord) const override
    {
        auto position = getPosition();
        auto area = m_glyphMap.getArea();
        auto spacing = m_glyphMap.getSpacing();

        return (coord.x > position.x &&
                coord.x < position.x + (area.x * spacing.x) &&
                coord.y > position.y &&
                coord.y < position.y + (area.y * spacing.y));
    }

private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(m_glyphMap, states);
    }

    GlyphTileMap m_glyphMap;

};
// TODO: ^

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
    m_window.setMouseCursorVisible(true);
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

    // TODO: Remove this
    static int count = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        ++count;
        State::get().frameManager->add(new FooFrame(std::to_string(count)));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && count > 0) {
        State::get().frameManager->remove(std::to_string(count));
        --count;
    }
    // TODO: ^
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
