///////////////////////////////////////////////////////////////////////////////
/// @file   State.hpp
/// @author Jacob Adkins (jpadkins)
/// @brief  Global singleton class containing references to different
///         management classes for the roguelike game and the root class for
///         update() and draw() calls
///////////////////////////////////////////////////////////////////////////////

#include "State.hpp"
#include "FrameManager.hpp"

// TODO: State should load from a config file eventually
static const std::string fontFile = "assets/unifont.ttf";

///////////////////////////////////////////////////////////////////////////////
State& State::get()
{
    static State state;
    return state;
}

///////////////////////////////////////////////////////////////////////////////
void State::update()
{
    frameManager->update();
}

///////////////////////////////////////////////////////////////////////////////
State::State() : frameManager(new FrameManager())
{
    if (!font.loadFromFile(fontFile)) {
        log_exit("Font loading failed: " + fontFile);
    }
}

///////////////////////////////////////////////////////////////////////////
void State::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    target.draw(*frameManager);
}
