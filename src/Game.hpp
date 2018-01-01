///////////////////////////////////////////////////////////////////////////////
/// @file   Game.hpp
/// @author Jacob Adkins (jpadkins)
/// @brief  A high level class representing a game
///////////////////////////////////////////////////////////////////////////////

#ifndef ROGUELIKE__GAME_HPP
#define ROGUELIKE__GAME_HPP

///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////////////////////////
/// @class  Game
/// @brief  Highest level class representing a game
///////////////////////////////////////////////////////////////////////////////
class Game {
public:

    ///////////////////////////////////////////////////////////////////////////
    /// @struct Game::Settings
    /// @brief  Defines all the dependencies for a Game class
    ///////////////////////////////////////////////////////////////////////////
    struct Settings {
        struct {
            bool vsync;
            sf::Uint32 style;
            std::string title;
            sf::VideoMode mode;
            sf::Uint32 fpsLimit;
        } window;

        struct {
            sf::Vector2i size;
        } frame;

        Settings() = delete;
    };

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Disable default constructor
    ///////////////////////////////////////////////////////////////////////////
    Game() = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Constructor
    ///
    /// @param settings Defines dependencies for the new Game
    ///////////////////////////////////////////////////////////////////////////
    explicit Game(Settings& settings);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Begin the main game loop
    ///////////////////////////////////////////////////////////////////////////
    void play();

private:

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Updates the game state
    ///
    /// This should be called once per frame.
    ///////////////////////////////////////////////////////////////////////////
    void updateState();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Renders the current frame
    ///
    /// This should be called once per frame.
    ///////////////////////////////////////////////////////////////////////////
    void renderFrame();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Updates the frame scale factor
    ///
    /// This should be called when the once initially and then again whenever
    /// the window is resized.
    ///////////////////////////////////////////////////////////////////////////
    void updateFrameScale();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Updates the global State's mouse coordinate
    ///
    /// This should be called once per frame.
    ///////////////////////////////////////////////////////////////////////////
    void updateFrameMouseCoord();

    ///////////////////////////////////////////////////////////////////////////
    sf::Vector2u m_frameSize;
    sf::Vector2f m_frameScale;
    sf::RenderWindow m_window;
    sf::RenderTexture m_frame;
};

#endif
