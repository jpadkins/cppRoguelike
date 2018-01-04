///////////////////////////////////////////////////////////////////////////////
/// @file   Window.hpp
/// @author Jacob Adkins (jpadkins)
/// @brief  Parent class of all Gui elements
///////////////////////////////////////////////////////////////////////////////

#include "Window.hpp"

///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////

#include "State.hpp"

///////////////////////////////////////////////////////////////////////////////
/// Static variables
///////////////////////////////////////////////////////////////////////////////
std::string Window::focus = "";

///////////////////////////////////////////////////////////////////////////////
Window::Window(const std::string& tag) : tag(tag) {}