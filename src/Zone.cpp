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

///////////////////////////////////////////////////////////////////////////////
Zone::Zone()
{
    name = "default";

    auto glyphMap = new GlyphTileMap(
        State::get().font,
        {50, 50},
        {32, 32},
        32
    );

    m_map = std::unique_ptr<GlyphTileMap>(glyphMap);

    if (!m_mapBuffer.create(
        m_map->getArea().x * m_map->getSpacing().y,
        m_map->getArea().y * m_map->getSpacing().y)) {
        log_exit("Zone map buffer creation failed");
    }

    // TODO: Reomve
    for (sf::Uint32 x = 0; x < m_map->getArea().x; ++x) {
        for (sf::Uint32 y = 0; y < m_map->getArea().y; ++y) {
            m_map->setTile({x, y}, GlyphTileMap::Tile());
            if (x == m_map->getArea().x - 1 ||
                x == 0 ||
                y == m_map->getArea().y - 1 ||
                y == 0) {
                m_map->setTileCharacter({x, y}, '@');
            }
        }
    }
    // TODO: ^

    m_mapSection = sf::IntRect(
        (m_map->getArea().x * m_map->getSpacing().x) / 2,
        (m_map->getArea().y * m_map->getSpacing().y) / 2,
        static_cast<int>(State::get().frameSize.x),
        static_cast<int>(State::get().frameSize.y)
    );
    m_mapSection.left -= m_mapSection.width / 2;
    m_mapSection.top -= m_mapSection.height / 2;
}

///////////////////////////////////////////////////////////////////////////////
void Zone::update()
{
    // Mouse is near right edge
    if (State::get().mousePosition.x + m_scrollThreshold >=
        static_cast<int>(State::get().frameSize.x) &&
        m_mapSection.left + m_mapSection.width <
        static_cast<int>(m_mapBuffer.getSize().x) +
        m_scrollSpeed + m_mapPadding) {

        m_mapSection.left += m_scrollSpeed;
    }
    // Mouse is near left edge
    else if (State::get().mousePosition.x <= m_scrollThreshold &&
        m_mapSection.left >= m_scrollSpeed) {
        m_mapSection.left -= m_scrollSpeed;
    }

    // Mouse is near top edge
    if (State::get().mousePosition.y + m_scrollThreshold >=
        static_cast<int>(State::get().frameSize.y) &&
        m_mapSection.top + m_mapSection.height <
        static_cast<int>(m_mapBuffer.getSize().y) +
        m_scrollSpeed + m_mapPadding) {

        m_mapSection.top += m_scrollSpeed;
    }
    // Mouse is near top edge
    else if (State::get().mousePosition.y <= m_scrollThreshold &&
        m_mapSection.top >= m_scrollSpeed) {
        m_mapSection.top -= m_scrollSpeed;
    }

    m_mapBuffer.draw(*m_map);
    m_mapBuffer.display();
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
