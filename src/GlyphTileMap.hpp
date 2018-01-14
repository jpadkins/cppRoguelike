///////////////////////////////////////////////////////////////////////////////
/// @file   GlyphTileMap.hpp
/// @author Jacob P Adkins (jpadkins)
/// @brief  An SFML-based drawable/transformable class for displaying a grid of
///         characters with colored backgrounds and several spacing options
///////////////////////////////////////////////////////////////////////////////

#ifndef ROGUELIKE__GLYPH_TILE_MAP_H
#define ROGUELIKE__GLYPH_TILE_MAP_H

///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Common.hpp"

///////////////////////////////////////////////////////////////////////////////
class GlyphTileMap : public DrawAndTransform {
public:

    struct Tile {
        ///////////////////////////////////////////////////////////////////////
        /// @brief Type is used to determine placement of a Tile's character
        ///
        /// Text:   Spacing is based on font kerning (e.g. characters like g
        ///         and y will intrude partially on the Tile below them)
        /// Exact:  Spacing is based on the Tile's offset values, which are
        ///         relative to the offsets of Type::Center
        /// Floor:  The Tile's character is centered horizontally but aligned
        ///         vertically with the bottom of the tile
        /// Center: The Tile's character is centered both horizontally and
        ///         vertically
        ///////////////////////////////////////////////////////////////////////
        enum Type { Text, Exact, Floor, Center };

        ///////////////////////////////////////////////////////////////////////
        /// @brief The Animation function type is used for the update callback
        ///
        /// This should be some self-contained lambda that takes a Tile
        /// reference and a delta time value and updates the Tile's appearance
        ///////////////////////////////////////////////////////////////////////
        typedef std::function<void(GlyphTileMap::Tile&, sf::Int32)> Animation;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Default Tile constructor
        ///
        /// The default values of a GlyphTileMap::Tile are:
        ///
        /// character:  L' '
        /// type:       Type::Center
        /// foreground: sf::Color::White
        /// background: sf::Color::Black
        /// offset:     {0, 0}
        ///////////////////////////////////////////////////////////////////////
        Tile();

        ///////////////////////////////////////////////////////////////////////
        /// @brief Constructor for a Tile
        ///
        /// @param character    UTF-8 value of the character of the Tile
        /// @param type         Type of the Tile (determines spacing)
        /// @param foreground   Color of the Tile's character
        /// @param background   Color to display behind the Tile's character
        /// @param offset       Manual spacing offset values of the Tile
        ///////////////////////////////////////////////////////////////////////
        Tile(sf::Uint32 character,
             Type type,
             const sf::Color& foreground,
             const sf::Color& background,
             const sf::Vector2i& offset = {0, 0});

        ///////////////////////////////////////////////////////////////////////
        Type type;
        sf::Vector2i offset;
        Animation animation;
        sf::Color foreground;
        sf::Color background;
        sf::Uint32 character;
    };

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Disable default constructor
    ///////////////////////////////////////////////////////////////////////////
    GlyphTileMap() = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Disable copy constructor
    /// TODO: Change the Font reference member variable to a shared_ptr and
    /// implement this in a smart way
    ///////////////////////////////////////////////////////////////////////////
    GlyphTileMap(const GlyphTileMap&) = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Disable assignment operator
    ///////////////////////////////////////////////////////////////////////////
    void operator=(const GlyphTileMap&) = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Constructor
    ///
    /// @param font     Reference to a loaded sf::Font to use for glyph data
    /// @param area     Width and height of the GlyphTileMap in # of tiles
    /// @param spacing  Width and height of each tile in pixels
    /// @param charSize Size of each glyph
    ///////////////////////////////////////////////////////////////////////////
    GlyphTileMap(sf::Font& font,
                 const sf::Vector2u& area,
                 const sf::Vector2u& spacing,
                 sf::Uint32 charSize);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Reconstructs the GlyphTileMap, or constructs at a later time
    ///
    /// @param font     Reference to a loaded sf::Font to use for glyph data
    /// @param area     Width and height of the GlyphTileMap in # of tiles
    /// @param spacing  Width and height of each tile in pixels
    /// @param charSize Size of each glyph
    ///////////////////////////////////////////////////////////////////////////
    void create(sf::Font& font,
                const sf::Vector2u& area,
                const sf::Vector2u& spacing,
                sf::Uint32 charSize);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Returns a const reference to the area of the GlyphTileMap
    ///
    /// @return a const reference to the area of the GlyphTileMap
    ///////////////////////////////////////////////////////////////////////////
    const sf::Vector2u& getArea() const;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Returns a const reference to the spacing of the GlyphTileMap
    ///
    /// @return a const reference to the spacing of the GlyphTileMap
    ///////////////////////////////////////////////////////////////////////////
    const sf::Vector2u& getSpacing() const;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Returns the character size of the GlyphTileMap
    ///
    /// @return the character size of the GlyphTileMap
    ///////////////////////////////////////////////////////////////////////////
    sf::Uint32 getCharSize() const;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Updates the GlyphTileMap at a coord with data from a Tile
    ///
    /// @param coord    Coordinate in the GlyphTileMap to update
    /// @param tile     GlyphTileMap::Tile to update the GlyphTileMap with
    ///////////////////////////////////////////////////////////////////////////
    void setTile(const sf::Vector2u& coord, const Tile& tile);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Updates the character at a coord in the GlyphTileMap
    ///
    /// @param coord        Coordinate in the GlyphTileMap to update
    /// @param character    New character for the tile
    /// @param type         Tile::Type of the new character (default Center)
    /// @param offset       Exact spacing offset value of the new character
    ///                     (default {0, 0})
    ///////////////////////////////////////////////////////////////////////////
    void setTileCharacter(const sf::Vector2u& coord,
                          sf::Uint32 character,
                          Tile::Type type = Tile::Center,
                          const sf::Vector2i& offset = {0, 0});

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Updates the foreground and background colors at a coord
    ///
    /// @param coord        Coordinate in the GlyphTileMap to update
    /// @param foreground   New foreground color for the tile
    /// @param background   New background color for the tile
    ///////////////////////////////////////////////////////////////////////////
    void setTileColors(const sf::Vector2u& coord,
                       sf::Color& foreground,
                       sf::Color& background);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Updates the foreground color at a coord
    ///
    /// @param coord    Coordinate in the GlyphTileMap to update
    /// @param color    New foreground color for the tile
    ///////////////////////////////////////////////////////////////////////////
    void setTileFgColor(const sf::Vector2u& coord,
                        const sf::Color& color);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Updates the background color at a coord
    ///
    /// @param coord    Coordinate in the GlyphTileMap to update
    /// @param color    New background color for the tile
    ///////////////////////////////////////////////////////////////////////////
    void setTileBgColor(const sf::Vector2u& coord,
                        const sf::Color& color);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Updates the animation at a coord
    ///
    /// Pass in nullptr to clear the tile's animation
    ///
    /// @param coord        Coordinate in the GlyphTileMap to update
    /// @param animation    New animation color for the tile
    ///////////////////////////////////////////////////////////////////////////
    void setTileAnimation(const sf::Vector2u& coord,
                          const Tile::Animation& animation);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Returns true if the current mouse position is within the object
    ///
    /// @return True if the mouse is within the object, false otherwise
    ///////////////////////////////////////////////////////////////////////////
    bool containsMouse() const override;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Returns true if a coord is contained within the object
    ///
    /// @param position Location in frame-space to check if the object contains
    ///
    /// @return True if the coord is within the object, false otherwise
    ///////////////////////////////////////////////////////////////////////////
    bool containsPosition(const sf::Vector2i& position) const override;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Returns the Tile coordinate corresponding to a pixel coordinate
    ///
    /// @param position Pixel coordinate to determine Tile coordinate from
    ///
    /// @return The Tile coordinate corresponding to the position. This value
    ///         may be out-of-bounds of the GlyphTileMap
    ///////////////////////////////////////////////////////////////////////////
    sf::Vector2i getTileCoordFromPosition(const sf::Vector2i& position) const;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Returns the Tile coordinate corresponding to a pixel coordinate
    ///
    /// @param position     Pixel coordinate to determine Tile coordinate from
    /// @param thisPosition Position to use instead of getPosition()
    ///
    /// @return The Tile coordinate corresponding to the position. This value
    ///         may be out-of-bounds of the GlyphTileMap
    ///////////////////////////////////////////////////////////////////////////
    sf::Vector2i getTileCoordFromPosition(
        const sf::Vector2i& position, const sf::Vector2f& thisPosition) const;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Updates all the contained Tiles
    ///
    /// Should be called once per frame
    ///////////////////////////////////////////////////////////////////////////
    void update();

private:

    ///////////////////////////////////////////////////////////////////////////
    /// Overloaded draw function from sf::Drawable/sf::Transformable
    ///////////////////////////////////////////////////////////////////////////
    void draw(sf::RenderTarget& target,
              sf::RenderStates states) const override;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Returns the 1-dimensional index of a tile at x and y coord
    ///
    /// @param coord    x and y coordinates of the tile
    ///
    /// @return Index of the tile in a 1-dimensional array
    ///////////////////////////////////////////////////////////////////////////
    sf::Uint32 getIndex(const sf::Vector2u& coord) const;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Calculates the offset of a character given the Type of the tile
    ///
    /// @param glyph    The Glyph of the character
    /// @param type     The Type of the tile
    /// @param offset   The exact offset value from the tile
    ///
    /// @return Spacing for the character
    ///////////////////////////////////////////////////////////////////////////
    sf::Vector2i getOffset(const sf::Glyph& glyph,
                           Tile::Type type,
                           const sf::Vector2i& offset) const;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Updates the vertices at a coord with data from a Tile
    ///
    /// @param coord    Coordinate of the tile to update
    /// @param tile     Tile structure holding data to update with
    ///////////////////////////////////////////////////////////////////////////
    void updateTile(const sf::Vector2u& coord, const Tile& tile);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Updates just the character at a coord
    ///
    /// @param coord        Coordinate of the tile to update
    /// @param character    New character of the tile
    /// @param type         Type of the tile's new character
    /// @param offset       Offset of the tile's new character
    ///////////////////////////////////////////////////////////////////////////
    void updateCharacter(const sf::Vector2u& coord,
                         sf::Uint32 character,
                         Tile::Type type,
                         const sf::Vector2i& offset);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Update the foreground vertices positions at a coord
    ///
    /// @param coord    Coordinate of the tile to update
    /// @param texRect  IntRect with the coord of the character texture
    /// @param offset   Extra right and bottom spacing
    ///////////////////////////////////////////////////////////////////////////
    void updateFgPosition(const sf::Vector2u& coord,
                          const sf::IntRect& texRect,
                          const sf::Vector2i& offset);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Update the foreground vertices colors at a coord
    ///
    /// @param coord    Coordinate of the tile to update
    /// @param color    Color for each of the vertices
    ///////////////////////////////////////////////////////////////////////////
    void updateFgColor(const sf::Vector2u& coord,
                       const sf::Color& color);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Update the background vertices positions at a coord
    ///
    /// Since the background vertices are independent of the character data of
    /// the tile, this should only need to be called once for each tile.
    ///
    /// @param coord   Coordinates of the tile to update
    /////////////////////////////////////////////////////////////////////////// 
    void updateBgPosition(const sf::Vector2u& coord);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Update the background vertices' colors at a coord
    ///
    /// @param coord    Coordinate of the tile to update
    /// @param color    Color for each of the vertices
    ///////////////////////////////////////////////////////////////////////////
    void updateBgColor(const sf::Vector2u& coord,
                       const sf::Color& color);

    ///////////////////////////////////////////////////////////////////////////
    sf::Font& m_font;
    sf::Vector2u m_area;
    sf::Uint32 m_charSize;
    sf::Vector2u m_spacing;
    std::vector<Tile> m_tiles;
    sf::VertexArray m_foreground;
    sf::VertexArray m_background;
};

#endif
