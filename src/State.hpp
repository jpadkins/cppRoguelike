///////////////////////////////////////////////////////////////////////////////
/// @file   State.hpp
/// @author Jacob Adkins (jpadkins)
/// @brief  Global singleton class containing references to different
///         management classes for the roguelike game and the root class for
///         update() and draw() calls
///////////////////////////////////////////////////////////////////////////////

#ifndef ROGUELIKE__STATE_HPP
#define ROGUELIKE__STATE_HPP

///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////

#include <array>
#include <memory>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Common.hpp"

///////////////////////////////////////////////////////////////////////////////
/// @brief Enum of all keyboard inputs used by the game
///////////////////////////////////////////////////////////////////////////////
enum class Key {
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y,
    Z, Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Esc, Ctrl,
    Shift, Alt, Space, Left, Right, Up, Down, Count
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Enum describing mouse input buttons
///////////////////////////////////////////////////////////////////////////////
enum class MouseButton {
    Left, Right
};

///////////////////////////////////////////////////////////////////////////////
/// Forward declarations for State
///////////////////////////////////////////////////////////////////////////////
class ZoneManager;
class DebugManager;
class WindowManager;

///////////////////////////////////////////////////////////////////////////////
/// @brief Singleton holding references to different management classes
///
/// TODO: Add a unique StateInterface class for the rendering, logic, etc...
/// subsystems to hide parts of State that they don't need access to
///////////////////////////////////////////////////////////////////////////////
class State : public sf::Drawable {
public:

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Disable copy constructor
    ///////////////////////////////////////////////////////////////////////////
    State(const State&) = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Disable assignment operator
    ///////////////////////////////////////////////////////////////////////////
    void operator=(const State&) = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Returns a reference to the global State instance
    ///
    /// @return A reference to the global State instance
    ///////////////////////////////////////////////////////////////////////////
    static State& get();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Updates all private management classes
    ///////////////////////////////////////////////////////////////////////////
    void update();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Returns pressed status of a given key
    ///
    /// @param key  Key value to check
    ///
    /// @return True if the key is pressed, false otherwise
    ///////////////////////////////////////////////////////////////////////////
    bool getKeyStatus(Key key);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Sets the pressed status of all keys based on sf::Keyboard
    ///
    /// This should be called once per frame
    ///////////////////////////////////////////////////////////////////////////
    void updateKeyStatuses();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Sets the pressed status for all keys to false
    ///////////////////////////////////////////////////////////////////////////
    void clearAllKeyStatuses();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Returns whether or not a key was pressed this frame
    ///
    /// @param key  Key value to check
    ///
    /// @return True if the key was pressed this frame, false otherwise
    ///////////////////////////////////////////////////////////////////////////
    bool getKeyPressedStatus(Key key);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Sets whether or not a key was pressed this frame
    ///
    /// @param sfKey    Key value to search for in the mappings and set
    /// @param status   Whether or not the key was pressed
    ///////////////////////////////////////////////////////////////////////////
    void setKeyPressedStatus(sf::Keyboard::Key sfKey, bool status);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Sets the pressed (this frame) status for all keys to false
    ///////////////////////////////////////////////////////////////////////////
    void clearAllKeyPressedStatuses();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Updates a key mapping
    ///
    /// If another Key is bound to sfKey, then the sfKey bound to that Key
    /// will be swapped with this one.
    ///
    /// @param key      Key value to update
    /// @param sfKey    New sf::Keyboard::Key value to tie the Key to
    ///////////////////////////////////////////////////////////////////////////
    void rebindKey(Key key, sf::Keyboard::Key sfKey);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Returns the pressed state of a mouse button
    ///
    /// This is more for brevity's sake than decoupling SFML
    ///////////////////////////////////////////////////////////////////////////
    bool getMouseStatus(MouseButton button);

    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// Display
    ///////////////////////////////////////////////////////////////////////////

    sf::Font font;
    sf::Vector2u frameSize;
    sf::Vector2f frameScale;
    sf::RenderWindow gameWindow;
    sf::RenderTexture frameBuffer;

    ///////////////////////////////////////////////////////////////////////////
    /// Input
    ///////////////////////////////////////////////////////////////////////////

    sf::Int32 deltaMs = 0;
    bool showDebug = false;
    bool leftClick = false;
    bool rightClick = false;
    float scrollDelta = 0.0f;
    sf::Vector2i mousePosition = {0, 0};
    sf::Vector2i lastMousePosition = {0, 0};

    ///////////////////////////////////////////////////////////////////////////
    /// Managers
    ///////////////////////////////////////////////////////////////////////////

    std::unique_ptr<ZoneManager> zoneManager;
    std::unique_ptr<DebugManager> debugManager;
    std::unique_ptr<WindowManager> windowManager;

private:

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Private constructor
    ///////////////////////////////////////////////////////////////////////////
    State();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Overloaded draw function from sf::Drawable/sf::Transformable
    ///
    /// The draw call passes through to all managed objects, rendering a frame
    ///////////////////////////////////////////////////////////////////////////
    void draw(sf::RenderTarget& target, sf::RenderStates) const override;

    std::array<bool, static_cast<int>(Key::Count)> m_keyStatuses;
    std::array<bool, static_cast<int>(Key::Count)> m_keyPressedStatuses;
    std::array<sf::Keyboard::Key, static_cast<int>(Key::Count)> m_keyMappings;
};

#endif
