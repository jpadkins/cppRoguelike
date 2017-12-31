///////////////////////////////////////////////////////////////////////////////
/// @file   Game.hpp
/// @author Jacob Adkins (jpadkins)
/// @brief  A high level class representing a roguelike game
///////////////////////////////////////////////////////////////////////////////

#include "Game.hpp"

///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Macros.hpp"

///////////////////////////////////////////////////////////////////////////////
Game::Game(Settings& settings) : m_frameSize(settings.frame.size)
{
    m_window.create(settings.window.mode,
                    settings.window.title,
                    settings.window.style);

    if (!m_window.isOpen()) {
        log_exit("Could not open window");
    }
    else if (!m_frame.create(m_frameSize.x, m_frameSize.y)) {
        log_exit("Could not create frame buffer");
    }

    m_window.setVerticalSyncEnabled(settings.window.vsync);
    m_window.setFramerateLimit(settings.window.fpsLimit);
    m_window.setMouseCursorVisible(false);
    m_window.setActive();
}

///////////////////////////////////////////////////////////////////////////////
void Game::play()
{
    std::cout << "Playing game!" << std::endl;
}
