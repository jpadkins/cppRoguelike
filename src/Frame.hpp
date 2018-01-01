///////////////////////////////////////////////////////////////////////////////
/// @file   Frame.hpp
/// @author Jacob Adkins (jpadkins)
/// @brief  Parent class of all Gui Elements
///////////////////////////////////////////////////////////////////////////////

#ifndef ROGUELIKE__FRAME_HPP
#define ROGUELIKE__FRAME_HPP

#include "Common.hpp"

///////////////////////////////////////////////////////////////////////////////
/// @brief Highest parent class for all GUI elements
///////////////////////////////////////////////////////////////////////////////
class Frame : public Updatable, public DrawAndTransform {
public:

    explicit Frame(const std::string& tag);

    Frame() = delete;

    Frame(const Frame&) = delete;

    void operator=(const Frame&) = delete;

    bool focus = false;
    const std::string tag;
    bool consumeMouse = false;

};

#endif
