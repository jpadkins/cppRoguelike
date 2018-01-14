///////////////////////////////////////////////////////////////////////////////
/// @file   Zone.cpp
/// @author Jacob Adkins (jpadkins)
/// @brief  Class describing a discreet area within the game world
///////////////////////////////////////////////////////////////////////////////

#include "Zone.hpp"

///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////

#include "State.hpp"

// TODO: Implement a way for Zones to be very, very large without running out
// of space for the m_mapBuffer texture. This could be done by finding how many
// 512x512 RenderTextures would be needed to completely cover the large map,
// then dividing the map up amongst them. When the Zone goes to draw, it will
// calculate texture rects for each of the RenderTextures based on the
// mapSection, and render them together seamlessly

// TODO: Actually implement this based on arguments
///////////////////////////////////////////////////////////////////////////////
Zone::Zone() : m_map(State::get().font, {50, 50}, {28, 28}, 32)
{
    name = "default";

    if (!m_mapBuffer.create(
        m_map.getArea().x * m_map.getSpacing().y,
        m_map.getArea().y * m_map.getSpacing().y)) {
        log_exit("Zone map buffer creation failed");
    }

    // TODO: Reomve
    for (sf::Uint32 x = 0; x < m_map.getArea().x; ++x) {
        for (sf::Uint32 y = 0; y < m_map.getArea().y; ++y) {
            m_map.setTile({x, y}, GlyphTileMap::Tile());
            if (x == m_map.getArea().x - 1 ||
                x == 0 ||
                y == m_map.getArea().y - 1 ||
                y == 0) {
                if (rand() % 2 == 0) {
                    m_map.setTileCharacter({x, y}, '#');
                }
                else {
                    m_map.setTileCharacter({x, y}, '=');
                }
                m_map.setTileFgColor({x, y}, sf::Color(
                    rand() % 5 + 30,
                    rand() % 5 + 10,
                    rand() % 5 + 5
                ));
                m_map.setTileBgColor({x, y}, sf::Color(
                    rand() % 20 + 50,
                    rand() % 10 + 50,
                    rand() % 5 + 50
                ));
            }
            else if (rand() % 5 == 0) {
                if (rand() % 2 == 0) {
                    m_map.setTileCharacter({x, y}, '#');
                }
                else {
                    m_map.setTileCharacter({x, y}, '=');
                }
                m_map.setTileFgColor({x, y}, sf::Color(
                    rand() % 5 + 30,
                    rand() % 5 + 10,
                    rand() % 5 + 5
                ));
                m_map.setTileBgColor({x, y}, sf::Color(
                    rand() % 20 + 50,
                    rand() % 10 + 50,
                    rand() % 5 + 50
                ));
            }
            else if (rand() % 3 == 0) {
                m_map.setTileCharacter({x, y}, ',');
                m_map.setTileFgColor({x, y}, sf::Color(
                    rand() % 5 + 30,
                    rand() % 5 + 10,
                    rand() % 5 + 5
                ));
                m_map.setTileBgColor({x, y}, sf::Color(
                    rand() % 5 + 30,
                    rand() % 5 + 10,
                    rand() % 5 + 5
                ));
            }
            else if (rand() % 3 == 0) {
                m_map.setTileCharacter({x, y}, '.');
                m_map.setTileFgColor({x, y}, sf::Color(
                    rand() % 5 + 30,
                    rand() % 5 + 10,
                    rand() % 5 + 5
                ));
                m_map.setTileBgColor({x, y}, sf::Color(
                    rand() % 5 + 30,
                    rand() % 5 + 10,
                    rand() % 5 + 5
                ));
            }
            else {
                m_map.setTileCharacter({x, y}, ' ');
                m_map.setTileFgColor({x, y}, sf::Color(
                    rand() % 5 + 30,
                    rand() % 5 + 10,
                    rand() % 5 + 5
                ));
                m_map.setTileBgColor({x, y}, sf::Color(
                    rand() % 5 + 30,
                    rand() % 5 + 10,
                    rand() % 5 + 5
                ));
            }
        }
    }
    // TODO: ^

    m_mapSection = sf::IntRect(
        (m_map.getArea().x * m_map.getSpacing().x) / 2,
        (m_map.getArea().y * m_map.getSpacing().y) / 2,
        static_cast<int>(State::get().frameSize.x),
        static_cast<int>(State::get().frameSize.y)
    );
    m_mapSection.left -= m_mapSection.width / 2;
    m_mapSection.top -= m_mapSection.height / 2;

    m_mapBuffer.draw(m_map);
    m_mapBuffer.display();
}

///////////////////////////////////////////////////////////////////////////////
void Zone::update()
{
    // Mouse is near right edge
    if (State::get().mousePosition.x + m_scrollThreshold >=
        static_cast<int>(State::get().frameSize.x) ||
        State::get().getKeyStatus(Key::Right)) {

        // And the map section has room to move
        if (m_mapSection.left + m_mapSection.width <=
            static_cast<int>(m_mapBuffer.getSize().x) - m_scrollSpeed +
            m_mapPadding) {
            m_mapSection.left += m_scrollSpeed;
        }
    }
        // Mouse is near left edge
    else if (State::get().mousePosition.x <= m_scrollThreshold ||
             State::get().getKeyStatus(Key::Left)) {

        // And the map section has room to move
        if (m_mapSection.left >= m_scrollSpeed - m_mapPadding) {
            m_mapSection.left -= m_scrollSpeed;
        }
    }

    // Mouse is near bottom edge
    if (State::get().mousePosition.y + m_scrollThreshold >=
        static_cast<int>(State::get().frameSize.y) ||
        State::get().getKeyStatus(Key::Down)) {

        // And the map section has room to move
        if (m_mapSection.top + m_mapSection.height <=
            static_cast<int>(m_mapBuffer.getSize().y) -
            m_scrollSpeed + m_mapPadding) {
            m_mapSection.top += m_scrollSpeed;

        }
    }
        // Mouse is near top edge
    else if (State::get().mousePosition.y <= m_scrollThreshold ||
             State::get().getKeyStatus(Key::Up)) {

        // And the map section has room to move
        if (m_mapSection.top >= m_scrollSpeed - m_mapPadding) {
            m_mapSection.top -= m_scrollSpeed;
        }
    }
}

///////////////////////////////////////////////////////////////////////////
void Zone::setMapSection(const sf::IntRect& section)
{
    m_mapSection = section;
}

///////////////////////////////////////////////////////////////////////////
void Zone::setMapSectionToFrameSize()
{
    m_mapSection.width = static_cast<int>(State::get().frameSize.x);
    m_mapSection.height = static_cast<int>(State::get().frameSize.y);
}

///////////////////////////////////////////////////////////////////////////
void Zone::setMapSectionCenter(const sf::Vector2i& center)
{
    m_mapSection.left = center.x - (m_mapSection.width / 2);
    m_mapSection.top = center.y - (m_mapSection.height / 2);
}

///////////////////////////////////////////////////////////////////////////
const sf::IntRect& Zone::getMapSection()
{
    return m_mapSection;
}

///////////////////////////////////////////////////////////////////////////
void Zone::moveMapSection(const sf::Vector2i& delta)
{
    m_mapSection.left += delta.x;
    m_mapSection.top += delta.y;
}

///////////////////////////////////////////////////////////////////////////
void Zone::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    sf::Sprite mapSprite(m_mapBuffer.getTexture());
    mapSprite.setTextureRect(m_mapSection);
    target.draw(mapSprite);
}
