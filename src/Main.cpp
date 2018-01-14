///////////////////////////////////////////////////////////////////////////////
/// @file   Main.cpp
/// @author Jacob Adkins (jpadkins)
/// @brief  Entry point of the application
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////

#include <ctime>
#include <cstdlib>
#include "Game.hpp"

///////////////////////////////////////////////////////////////////////////////
/// Main
///////////////////////////////////////////////////////////////////////////////
int main()
{
    srand(static_cast<uint32_t>(time(nullptr)));
    auto windowMode = sf::VideoMode::getFullscreenModes()[0];
    Game::Settings gameSettings = {
        {
            false,
            sf::Style::Fullscreen,
            "SFML App",
            windowMode,
            0
        },
        {
            {896, 504}
        }
    };

    Game game(gameSettings);
    game.play();

    return 0;
}
