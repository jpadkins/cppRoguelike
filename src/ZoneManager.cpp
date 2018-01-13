///////////////////////////////////////////////////////////////////////////////
/// @file   ZoneManager.cpp
/// @author Jacob Adkins (jpadkins)
/// @brief  A class managing active Zones, overall Zone layout, serialization,
///         etc...
///////////////////////////////////////////////////////////////////////////////

#include "ZoneManager.hpp"

///////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////

#include "State.hpp"

/// TODO: Change all the managers' addXXXXX() functions to forward an argument
/// pack so that the 'new' keyword can be avoided
///////////////////////////////////////////////////////////////////////////////
void ZoneManager::addZone(Zone* zone)
{
    if (!zone) {
        log_exit("Null argument");
    }

    auto it = m_zones.find(zone->name);
    if (it != m_zones.end()) {
        log_exit("Zone already exists with that name: %s" + zone->name);
    }
    else {
        m_zones.insert({zone->name, std::unique_ptr<Zone>(zone)});
    }
}


///////////////////////////////////////////////////////////////////////////
void ZoneManager::setCurrentZone(const std::string& name)
{
    m_currentZone = name;
}

///////////////////////////////////////////////////////////////////////////
void ZoneManager::update()
{
    auto it = m_zones.find(m_currentZone);
    if (it != m_zones.end()) {
        (*it).second->update();
    }
}

///////////////////////////////////////////////////////////////////////////
void ZoneManager::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    auto it = m_zones.find(m_currentZone);
    if (it != m_zones.end()) {
        target.draw(*(*it).second);
    }
}
