///////////////////////////////////////////////////////////////////////////////
/// @file   Common.cpp
/// @author Jacob Adkins (jpadkins)
/// @brief  Defines commonly used macros and interfaces
///////////////////////////////////////////////////////////////////////////////

#include "Common.hpp"

///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////

#include "State.hpp"

///////////////////////////////////////////////////////////////////////////////
void DrawAndTransform::matchLastMouseMovement()
{
    State& state = State::get();
    auto position = this->getPosition();

    this->setPosition(
        position.x + (state.mousePosition.x - state.lastMousePosition.x),
        position.y + (state.mousePosition.y - state.lastMousePosition.y)
    );
}
