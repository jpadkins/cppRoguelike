///////////////////////////////////////////////////////////////////////////////
/// @file   ZoneManager.hpp
/// @author Jacob Adkins (jpadkins)
/// @brief  A class managing active Zones, overall Zone layout, serialization,
///         etc...
///////////////////////////////////////////////////////////////////////////////

#ifndef ROGUELIKE__ZONE_MANAGER_HPP
#define ROGUELIKE__ZONE_MANAGER_HPP

///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////

#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Zone.hpp"

///////////////////////////////////////////////////////////////////////////////
/// @brief  A class managing active Zones, overall Zone layout, serialization,
///         etc...
///////////////////////////////////////////////////////////////////////////////
class ZoneManager : public sf::Drawable {
public:

    ZoneManager() = default;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Adds a new Zone to be managed
    ///
    /// @param zone the Zone to be managed
    ///////////////////////////////////////////////////////////////////////////
    void addZone(Zone* zone);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Sets the current Zone by name
    ///
    /// @param name Name of the Zone to set current
    ///////////////////////////////////////////////////////////////////////////
    void setCurrentZone(const std::string& name);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Updates internal state, should be called once per frame
    ///////////////////////////////////////////////////////////////////////////
    void update();

private:

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Overloaded draw function from sf::Drawable
    ///////////////////////////////////////////////////////////////////////////
    void draw(sf::RenderTarget& target, sf::RenderStates) const override;

    ///////////////////////////////////////////////////////////////////////////

    std::string m_currentZone;
    std::unordered_map<std::string, std::unique_ptr<Zone>> m_zones;
};

#endif
