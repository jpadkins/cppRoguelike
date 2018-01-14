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
#include "ZoneManager.hpp"
#include "GlyphTileMap.hpp"
#include "WindowManager.hpp"
#include "DraggableWindow.hpp"


// TODO: Remove this
class FooWindow : public DraggableWindow {
public:

    FooWindow() = delete;

    explicit FooWindow(const std::string& tag)
        : DraggableWindow(tag),
          m_glyphMap(State::get().font, {25, 20}, {8, 15}, 16)
    {
        auto randColor = []() {
            return sf::Color(rand() % 255, rand() % 255, rand() % 255);
        };

        sf::Vector2i spacing = sf::Vector2i(
            static_cast<int>(m_glyphMap.getSpacing().x),
            static_cast<int>(m_glyphMap.getSpacing().y));

        auto background_color = randColor();
        auto inc = 0;

        for (uint32_t x = 0; x < m_glyphMap.getArea().x; ++x) {
            for (uint32_t y = 0; y < m_glyphMap.getArea().y; ++y) {
                // Top-left tile
                if (x == 0 && y == 0) {
                    m_glyphMap.setTile({x, y}, GlyphTileMap::Tile(
                        L'█', GlyphTileMap::Tile::Exact, sf::Color::White,
                        sf::Color::Transparent,
                        {static_cast<int>(spacing.x * 0.70),
                         static_cast<int>(spacing.y * 0.75)}
                    ));
                }
                    // Top-right tile
                else if (x == m_glyphMap.getArea().x - 1 && y == 0) {
                    m_glyphMap.setTile({x, y}, GlyphTileMap::Tile(
                        L'█', GlyphTileMap::Tile::Exact, sf::Color::White,
                        sf::Color::Transparent,
                        {-1 * static_cast<int>(spacing.x * 0.70),
                         static_cast<int>(spacing.y * 0.75)}
                    ));
                }
                    // Bottom-right tile
                else if (x == m_glyphMap.getArea().x - 1 &&
                         y == m_glyphMap.getArea().y - 1) {
                    m_glyphMap.setTile({x, y}, GlyphTileMap::Tile(
                        L'█', GlyphTileMap::Tile::Exact, sf::Color::White,
                        sf::Color::Transparent,
                        {-1 * static_cast<int>(spacing.x * 0.70),
                         -1 * static_cast<int>(spacing.y * 0.75)}
                    ));
                }
                    // Bottom-left tile
                else if (x == 0 && y == m_glyphMap.getArea().y - 1) {
                    m_glyphMap.setTile({x, y}, GlyphTileMap::Tile(
                        L'█', GlyphTileMap::Tile::Exact, sf::Color::White,
                        sf::Color::Transparent,
                        {static_cast<int>(spacing.x * 0.70),
                         -1 * static_cast<int>(spacing.y * 0.75)}
                    ));
                }
                    // Left column tiles
                else if (x == 0) {
                    m_glyphMap.setTile({x, y}, GlyphTileMap::Tile(
                        L'▐', GlyphTileMap::Tile::Exact, sf::Color::White,
                        sf::Color::Transparent,
                        {static_cast<int>(spacing.x * 0.70),
                         -1 * static_cast<int>(spacing.y * 0.05)}
                    ));
                }
                    // Right column tiles
                else if (x == m_glyphMap.getArea().x - 1) {
                    m_glyphMap.setTile({x, y}, GlyphTileMap::Tile(
                        L'▌', GlyphTileMap::Tile::Exact, sf::Color::White,
                        sf::Color::Transparent,
                        {-1 * static_cast<int>(spacing.x * 0.70),
                         static_cast<int>(spacing.y * 0.05)}
                    ));
                }
                    // Top row tiles
                else if (y == 0) {
                    m_glyphMap.setTile({x, y}, GlyphTileMap::Tile(
                        L'~', GlyphTileMap::Tile::Exact, sf::Color::White,
                        sf::Color::Transparent,
                        {0, static_cast<int>(spacing.y * 0.75)}
                    ));
                }
                    // Bottom row tiles
                else if (y == m_glyphMap.getArea().y - 1) {
                    m_glyphMap.setTile({x, y}, GlyphTileMap::Tile(
                        L'~', GlyphTileMap::Tile::Exact, sf::Color::White,
                        sf::Color::Transparent,
                        {0, -1 * static_cast<int>(spacing.y * 0.75)}
                    ));
                }
                    // Middle tiles
                else if (x > 1 && y > 1 && x < m_glyphMap.getArea().x - 2
                         && y < m_glyphMap.getArea().y - 2) {

                    GlyphTileMap::Tile tile((rand() % 66) + 65,
                                            GlyphTileMap::Tile::Center,
                                            randColor(),
                                            background_color);

                    tile.animation = [count = inc](GlyphTileMap::Tile& tile,
                                                   sf::Int32 deltaMs) mutable {

                        count += deltaMs;
                        if (count > 500) {
                            tile.foreground = sf::Color(rand() % 255,
                                                        rand() % 255,
                                                        rand() % 255);
                            count -= 500;
                        }
                    };
                    m_glyphMap.setTile({x, y}, tile);
                    inc += 10;
                }
                else {
                    m_glyphMap.setTile({x, y}, GlyphTileMap::Tile(
                        ' ', GlyphTileMap::Tile::Center,
                        sf::Color::Transparent, background_color
                    ));
                }
            }
        }

        setPosition(rand() % static_cast<int>(State::get().frameSize.x),
                    rand() % static_cast<int>(State::get().frameSize.y));
    }

    void update() override
    {
        DraggableWindow::updateDrag();

        if (consumeMouse && State::get().rightClick) {
            shouldClose = true;
        }

        m_glyphMap.update();
    }

    bool containsMouse() const override
    {
        return containsPosition(State::get().mousePosition);
    }

    bool containsPosition(const sf::Vector2i& position) const override
    {
        auto thisPosition = getPosition();
        auto area = m_glyphMap.getArea();
        auto spacing = m_glyphMap.getSpacing();

        return (position.x > thisPosition.x &&
                position.x < thisPosition.x + (area.x * spacing.x) &&
                position.y > thisPosition.y &&
                position.y < thisPosition.y + (area.y * spacing.y));
    }

private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(m_glyphMap, states);
    }

    bool withinDraggableRegion(const sf::Vector2i& position) override
    {
        auto coord = m_glyphMap.getTileCoordFromPosition(position,
                                                         getPosition());
        return (coord.x > 0 && coord.x < 2) ||
               (coord.y > 0 && coord.y < 2) ||
               (coord.x > static_cast<int>(m_glyphMap.getArea().x - 3) &&
                coord.x < static_cast<int>(m_glyphMap.getArea().x - 1)) ||
               (coord.y > static_cast<int>(m_glyphMap.getArea().y - 3) &&
                coord.y < static_cast<int>(m_glyphMap.getArea().y - 1));
    }

    GlyphTileMap m_glyphMap;

};
// TODO: ^

///////////////////////////////////////////////////////////////////////////////
Game::Game(Settings& settings)
{
    State::get().frameSize = settings.frame.size;
    State::get().gameWindow.create(settings.window.mode,
                                   settings.window.title,
                                   settings.window.style);

    if (!State::get().gameWindow.isOpen()) {
        log_exit("Could not open window");
    }
    else if (!State::get().frameBuffer.create(settings.frame.size.x,
                                              settings.frame.size.y)) {
        log_exit("Could not create frame buffer");
    }

    State::get().gameWindow.setVerticalSyncEnabled(settings.window.vsync);
    State::get().gameWindow.setFramerateLimit(settings.window.fpsLimit);
    State::get().gameWindow.setMouseCursorVisible(true);
    State::get().gameWindow.setActive();

    updateFrameScale();

    // TODO: Remove this!

    State::get().zoneManager->addZone(new Zone());
    State::get().zoneManager->setCurrentZone("default");

    // TODO: ^
}

///////////////////////////////////////////////////////////////////////////////
void Game::play()
{
    sf::Clock clock;

    while (State::get().gameWindow.isOpen()) {
        updateFrameMouseCoord();
        State::get().leftClick = false;
        State::get().rightClick = false;
        State::get().updateKeyStatuses();
        State::get().clearAllKeyPressedStatuses();
        State::get().deltaMs = clock.restart().asMilliseconds();

        sf::Event event;
        while (State::get().gameWindow.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    State::get().gameWindow.close();
                    break;
                case sf::Event::Resized:
                    updateFrameScale();
                    break;
                case sf::Event::MouseButtonPressed:
                    switch (event.mouseButton.button) {
                        case sf::Mouse::Left:
                            State::get().leftClick = true;
                            break;
                        case sf::Mouse::Right:
                            State::get().rightClick = true;
                            break;
                        default:
                            break;
                    }
                    break;
                case sf::Event::MouseWheelScrolled:
                    State::get().scrollDelta
                        = event.mouseWheelScroll.delta;
                    break;
                case sf::Event::KeyPressed:
                    State::get().setKeyPressedStatus(event.key.code, true);
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

    if (State::get().getKeyStatus(Key::Esc)) {
        State::get().gameWindow.close();
    }

    if (State::get().getKeyStatus(Key::D)) {
        State::get().showDebug = true;
    }

    // TODO: Remove this
    static int count = 0;
    if (State::get().getKeyPressedStatus(Key::A)) {
        ++count;
        State::get().windowManager->addWindow(
            new FooWindow(std::to_string(count)));
    }
    else if (State::get().getKeyPressedStatus(Key::R) && count > 0) {
        State::get().windowManager->remove(std::to_string(count));
        --count;
    }
    // TODO: ^
}

///////////////////////////////////////////////////////////////////////////////
void Game::renderFrame()
{
    State::get().frameBuffer.clear();
    State::get().frameBuffer.draw(State::get());
    State::get().frameBuffer.display();

    sf::Sprite frameSprite(State::get().frameBuffer.getTexture());
    frameSprite.setScale(State::get().frameScale);

    //State::get().gameWindow.clear();
    State::get().gameWindow.draw(frameSprite);
    State::get().gameWindow.display();
}

///////////////////////////////////////////////////////////////////////////////
void Game::updateFrameScale()
{
    State::get().frameScale.x =
        static_cast<float>(State::get().gameWindow.getSize().x)
        / static_cast<float>(State::get().frameSize.x);
    State::get().frameScale.y =
        static_cast<float>(State::get().gameWindow.getSize().y)
        / static_cast<float>(State::get().frameSize.y);
}

///////////////////////////////////////////////////////////////////////////////
void Game::updateFrameMouseCoord()
{
    sf::Vector2f windowPosition = State::get().gameWindow.mapPixelToCoords(
        sf::Mouse::getPosition(State::get().gameWindow));

    State::get().mousePosition = sf::Vector2i(
        static_cast<int>(std::round(
            windowPosition.x / State::get().frameScale.x)),
        static_cast<int>(std::round(
            windowPosition.y / State::get().frameScale.y))
    );
}
