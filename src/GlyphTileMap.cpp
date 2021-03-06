///////////////////////////////////////////////////////////////////////////////
/// @file   GlyphTileMap.cpp
/// @author Jacob P Adkins (jpadkins)
/// @brief  An SFML-based drawable/transformable class for displaying a grid of
///         characters with colored backgrounds and several spacing options
///////////////////////////////////////////////////////////////////////////////

#include "State.hpp"
#include "GlyphTileMap.hpp"

///////////////////////////////////////////////////////////////////////////////
GlyphTileMap::Tile::Tile()
    : type(Type::Center),
      offset(0, 0),
      foreground(sf::Color::Red),
      background(sf::Color::Blue),
      character('?') {}

///////////////////////////////////////////////////////////////////////////////
GlyphTileMap::Tile::Tile(sf::Uint32 character,
                         Type type,
                         const sf::Color& foreground,
                         const sf::Color& background,
                         const sf::Vector2i& offset)
    : type(type),
      offset(offset),
      foreground(foreground),
      background(background),
      character(character) {}

///////////////////////////////////////////////////////////////////////////////
GlyphTileMap::GlyphTileMap(sf::Font& font,
                           const sf::Vector2u& area,
                           const sf::Vector2u& spacing,
                           sf::Uint32 charSize)
    : m_font(font),
      m_area(area),
      m_charSize(charSize),
      m_spacing(spacing),
      m_tiles(area.x * area.y),
      m_foreground(sf::Quads, area.x * area.y * 4),
      m_background(sf::Quads, area.x * area.y * 4) {}

void GlyphTileMap::create(sf::Font& font,
                          const sf::Vector2u& area,
                          const sf::Vector2u& spacing,
                          sf::Uint32 charSize)
{
    m_font = font;
    m_area = area;
    m_charSize = charSize;
    m_spacing = spacing;
    m_tiles.resize(area.x * area.y);
    m_foreground.setPrimitiveType(sf::Quads);
    m_foreground.resize(area.x * area.y * 4);
    m_background.setPrimitiveType(sf::Quads);
    m_background.resize(area.x * area.y * 4);
}

///////////////////////////////////////////////////////////////////////////////
const sf::Vector2u& GlyphTileMap::getArea() const
{
    return m_area;
}

///////////////////////////////////////////////////////////////////////////////
const sf::Vector2u& GlyphTileMap::getSpacing() const
{
    return m_spacing;
}

///////////////////////////////////////////////////////////////////////////////
sf::Uint32 GlyphTileMap::getCharSize() const
{
    return m_charSize;
}

///////////////////////////////////////////////////////////////////////////////
void GlyphTileMap::setTile(const sf::Vector2u& coord, const Tile& tile)
{
    updateTile(coord, tile);
    m_tiles[getIndex(coord)] = tile;
}

///////////////////////////////////////////////////////////////////////////////
void GlyphTileMap::setTileCharacter(const sf::Vector2u& coord,
                                    sf::Uint32 character,
                                    Tile::Type type,
                                    const sf::Vector2i& offset)
{
    updateCharacter(coord, character, type, offset);
    m_tiles[getIndex(coord)].character = character;
    m_tiles[getIndex(coord)].type = type;
}

///////////////////////////////////////////////////////////////////////////////
void GlyphTileMap::setTileColors(const sf::Vector2u& coord,
                                 sf::Color& foreground,
                                 sf::Color& background)
{
    updateFgColor(coord, foreground);
    updateBgColor(coord, background);
    m_tiles[getIndex(coord)].foreground = foreground;
    m_tiles[getIndex(coord)].background = background;
}

///////////////////////////////////////////////////////////////////////////////
void GlyphTileMap::setTileFgColor(const sf::Vector2u& coord,
                                  const sf::Color& color)
{
    updateFgColor(coord, color);
    m_tiles[getIndex(coord)].foreground = color;
}

///////////////////////////////////////////////////////////////////////////////
void GlyphTileMap::setTileBgColor(const sf::Vector2u& coord,
                                  const sf::Color& color)
{
    updateBgColor(coord, color);
    m_tiles[getIndex(coord)].background = color;
}


///////////////////////////////////////////////////////////////////////////
void GlyphTileMap::setTileAnimation(const sf::Vector2u& coord,
                                    const Tile::Animation& animation)
{
    m_tiles[getIndex(coord)].animation = animation;
}

///////////////////////////////////////////////////////////////////////////
bool GlyphTileMap::containsMouse() const
{
    return containsPosition(State::get().mousePosition);
}

///////////////////////////////////////////////////////////////////////////
bool GlyphTileMap::containsPosition(const sf::Vector2i& position) const
{
    auto thisPosition = getPosition();
    return (position.x > thisPosition.x &&
            position.x < thisPosition.x + (m_area.x * m_spacing.x) &&
            position.y > thisPosition.y &&
            position.y < thisPosition.y + (m_area.y * m_spacing.y));
}

///////////////////////////////////////////////////////////////////////////////
sf::Vector2i GlyphTileMap::getTileCoordFromPosition(
    const sf::Vector2i& position) const
{
    auto coord = sf::Vector2i(0, 0);
    auto thisPosition = this->getPosition();

    if (position.x - thisPosition.x < 0) {
        coord.x = -1 *
            static_cast<int>((position.x - thisPosition.x) / m_spacing.x);
    } else {
        coord.x =
            static_cast<int>((position.x - thisPosition.x) / m_spacing.x);
    }

    if (position.y - thisPosition.y < 0) {
        coord.y = -1 *
            static_cast<int>((position.y - thisPosition.y) / m_spacing.y);
    } else {
        coord.y =
            static_cast<int>((position.y - thisPosition.y) / m_spacing.y);
    }

    return coord;
}

///////////////////////////////////////////////////////////////////////////////
sf::Vector2i GlyphTileMap::getTileCoordFromPosition(
    const sf::Vector2i& position, const sf::Vector2f& thisPosition) const
{
    auto coord = sf::Vector2i(0, 0);

    if (position.x - thisPosition.x < 0) {
        coord.x = -1 *
            static_cast<int>((position.x - thisPosition.x) / m_spacing.x);
    } else {
        coord.x =
            static_cast<int>((position.x - thisPosition.x) / m_spacing.x);
    }

    if (position.y - thisPosition.y < 0) {
        coord.y = -1 *
            static_cast<int>((position.y - thisPosition.y) / m_spacing.y);
    } else {
        coord.y =
            static_cast<int>((position.y - thisPosition.y) / m_spacing.y);
    }

    return coord;
}

///////////////////////////////////////////////////////////////////////////////
void GlyphTileMap::update()
{
    auto deltaMs = State::get().deltaMs;

    // Important: This relies on the layout of m_tiles, but should be a lot
    // faster than calling getIndex() for every animated tile in every map
    for (sf::Uint32 x = 0; x < m_area.x; ++x) {
        for (sf::Uint32 y = 0; y < m_area.y; ++y) {
            auto index = getIndex({x, y});
            if (m_tiles[index].animation) {
                m_tiles[index].animation(m_tiles[index], deltaMs);
                updateTile({x, y}, m_tiles[index]);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
void GlyphTileMap::draw(sf::RenderTarget& target,
                        sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_font.getTexture(m_charSize);
    target.draw(m_background, states);
    target.draw(m_foreground, states);
}

///////////////////////////////////////////////////////////////////////////////
sf::Uint32 GlyphTileMap::getIndex(const sf::Vector2u& coord) const
{
    return static_cast<sf::Uint32>((coord.y * m_area.x) + coord.x);
}

///////////////////////////////////////////////////////////////////////////////
sf::Vector2i GlyphTileMap::getOffset(const sf::Glyph& glyph,
                                     Tile::Type type,
                                     const sf::Vector2i& offset) const
{
    sf::Vector2i adjustedOffset = {0, 0};

    switch (type) {
        case Tile::Text:
            adjustedOffset.x = static_cast<int>(glyph.bounds.left);
            adjustedOffset.y = static_cast<int>(m_spacing.y +
                                                glyph.bounds.top);
            break;
        case Tile::Exact:
            adjustedOffset.x =
                (static_cast<int>(m_spacing.x) - glyph.textureRect.width) / 2;
            adjustedOffset.y =
                (static_cast<int>(m_spacing.y) - glyph.textureRect.height) / 2;
            adjustedOffset.x += offset.x;
            adjustedOffset.y += offset.y;
            break;
        case Tile::Floor:
            adjustedOffset.x =
                (static_cast<int>(m_spacing.x) - glyph.textureRect.width) / 2;
            adjustedOffset.y =
                static_cast<int>(m_spacing.y) - glyph.textureRect.height;
            break;
        case Tile::Center:
            adjustedOffset.x =
                (static_cast<int>(m_spacing.x) - glyph.textureRect.width) / 2;
            adjustedOffset.y =
                (static_cast<int>(m_spacing.y) - glyph.textureRect.height) / 2;
            break;
    }

    return adjustedOffset;
}

///////////////////////////////////////////////////////////////////////////////
void GlyphTileMap::updateTile(const sf::Vector2u& coord,
                              const Tile& tile)
{
    const sf::Glyph& glyph = m_font.getGlyph(tile.character,
                                             m_charSize,
                                             false);

    sf::Vector2i adjustedOffset = getOffset(glyph, tile.type, tile.offset);

    updateFgPosition(coord, glyph.textureRect, adjustedOffset);
    updateFgColor(coord, tile.foreground);
    updateBgPosition(coord);
    updateBgColor(coord, tile.background);
}

///////////////////////////////////////////////////////////////////////////////
void GlyphTileMap::updateCharacter(const sf::Vector2u& coord,
                                   sf::Uint32 character,
                                   Tile::Type type,
                                   const sf::Vector2i& offset)
{
    const sf::Glyph& glyph = m_font.getGlyph(character,
                                             m_charSize,
                                             false);

    sf::Vector2i adjustedOffset = getOffset(glyph, type, offset);

    updateFgPosition(coord, glyph.textureRect, adjustedOffset);
}

///////////////////////////////////////////////////////////////////////////////
void GlyphTileMap::updateFgPosition(const sf::Vector2u& coord,
                                    const sf::IntRect& texRect,
                                    const sf::Vector2i& offset)
{
    sf::Uint32 index = getIndex(coord) * 4;

    m_foreground[index].position = {
        static_cast<float>(static_cast<int>(coord.x * m_spacing.x) + offset.x),
        static_cast<float>(static_cast<int>(coord.y * m_spacing.y) + offset.y)
    };
    m_foreground[index + 1].position = {
        static_cast<float>(static_cast<int>(coord.x * m_spacing.x) +
                           texRect.width + offset.x),
        static_cast<float>(static_cast<int>(coord.y * m_spacing.y) + offset.y)
    };
    m_foreground[index + 2].position = {
        static_cast<float>(static_cast<int>(coord.x * m_spacing.x) +
                           texRect.width + offset.x),
        static_cast<float>(static_cast<int>(coord.y * m_spacing.y) +
                           texRect.height + offset.y)
    };
    m_foreground[index + 3].position = {
        static_cast<float>(static_cast<int>(coord.x * m_spacing.x) + offset.x),
        static_cast<float>(static_cast<int>(coord.y * m_spacing.y) +
                           texRect.height + offset.y)
    };
    m_foreground[index].texCoords = {
        static_cast<float>(texRect.left),
        static_cast<float>(texRect.top)
    };
    m_foreground[index + 1].texCoords = {
        static_cast<float>(texRect.left + texRect.width),
        static_cast<float>(texRect.top)
    };
    m_foreground[index + 2].texCoords = {
        static_cast<float>(texRect.left + texRect.width),
        static_cast<float>(texRect.top + texRect.height)
    };
    m_foreground[index + 3].texCoords = {
        static_cast<float>(texRect.left),
        static_cast<float>(texRect.top + texRect.height)
    };
}

///////////////////////////////////////////////////////////////////////////////
void GlyphTileMap::updateFgColor(const sf::Vector2u& coord,
                                 const sf::Color& color)
{
    sf::Uint32 index = getIndex(coord) * 4;

    m_foreground[index].color = color;
    m_foreground[index + 1].color = color;
    m_foreground[index + 2].color = color;
    m_foreground[index + 3].color = color;
}

///////////////////////////////////////////////////////////////////////////////
void GlyphTileMap::updateBgPosition(const sf::Vector2u& coord)
{
    sf::Uint32 index = getIndex(coord) * 4;

    m_background[index].position = {
        static_cast<float>(coord.x * m_spacing.x),
        static_cast<float>(coord.y * m_spacing.y)
    };
    m_background[index + 1].position = {
        static_cast<float>((coord.x * m_spacing.x) + m_spacing.x),
        static_cast<float>(coord.y * m_spacing.y)
    };
    m_background[index + 2].position = {
        static_cast<float>((coord.x * m_spacing.x) + m_spacing.x),
        static_cast<float>((coord.y * m_spacing.y) + m_spacing.y)
    };
    m_background[index + 3].position = {
        static_cast<float>(coord.x * m_spacing.x),
        static_cast<float>((coord.y * m_spacing.y) + m_spacing.y)
    };
}

///////////////////////////////////////////////////////////////////////////////
void GlyphTileMap::updateBgColor(const sf::Vector2u& coord,
                                 const sf::Color& color)
{
    sf::Uint32 index = getIndex(coord) * 4;

    m_background[index].color = color;
    m_background[index + 1].color = color;
    m_background[index + 2].color = color;
    m_background[index + 3].color = color;
}

