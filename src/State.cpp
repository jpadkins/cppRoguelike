///////////////////////////////////////////////////////////////////////////////
/// @file   State.hpp
/// @author Jacob Adkins (jpadkins)
/// @brief  Global singleton class containing references to different
///         management classes for the roguelike game and the root class for
///         update() and draw() calls
///////////////////////////////////////////////////////////////////////////////

#include "State.hpp"
#include "ZoneManager.hpp"
#include "DebugManager.hpp"
#include "WindowManager.hpp"

// TODO: State should load from a config file eventually
const std::string fontFile = "assets/unifont.ttf";
const std::array<sf::Keyboard::Key, static_cast<int>(Key::Count)>
    defaultKeyMappings = {{

                              sf::Keyboard::A, sf::Keyboard::B,
                              sf::Keyboard::C, sf::Keyboard::D,
                              sf::Keyboard::E, sf::Keyboard::F,
                              sf::Keyboard::G, sf::Keyboard::H,
                              sf::Keyboard::I, sf::Keyboard::J,
                              sf::Keyboard::K, sf::Keyboard::L,
                              sf::Keyboard::M, sf::Keyboard::N,
                              sf::Keyboard::O, sf::Keyboard::P,
                              sf::Keyboard::Q, sf::Keyboard::R,
                              sf::Keyboard::S, sf::Keyboard::T,
                              sf::Keyboard::U, sf::Keyboard::V,
                              sf::Keyboard::W, sf::Keyboard::X,
                              sf::Keyboard::Y, sf::Keyboard::Z,
                              sf::Keyboard::Num0, sf::Keyboard::Num1,
                              sf::Keyboard::Num2,
                              sf::Keyboard::Num3, sf::Keyboard::Num4,
                              sf::Keyboard::Num5,
                              sf::Keyboard::Num6, sf::Keyboard::Num7,
                              sf::Keyboard::Num8,
                              sf::Keyboard::Num9,
                              sf::Keyboard::Escape, sf::Keyboard::LControl,
                              sf::Keyboard::LShift,
                              sf::Keyboard::LAlt, sf::Keyboard::Space,
                              sf::Keyboard::Left,
                              sf::Keyboard::Right, sf::Keyboard::Up,
                              sf::Keyboard::Down

                          }};

///////////////////////////////////////////////////////////////////////////////
State& State::get()
{
    static State state;
    return state;
}

///////////////////////////////////////////////////////////////////////////////
void State::update()
{
    zoneManager->update();
    debugManager->update();
    windowManager->update();
}

///////////////////////////////////////////////////////////////////////////////
State::State() : windowManager(new WindowManager())
{
    // Load font
    if (!font.loadFromFile(fontFile)) {
        log_exit("Font loading failed: " + fontFile);
    }

    // Create dependent managers
    zoneManager = std::make_unique<ZoneManager>();
    debugManager = std::make_unique<DebugManager>(font);

    // Set default keybindings
    m_keyMappings = defaultKeyMappings;
}

///////////////////////////////////////////////////////////////////////////
bool State::getKeyStatus(Key key)
{
    return m_keyStatuses[static_cast<size_t>(key)];
}

///////////////////////////////////////////////////////////////////////////
void State::updateKeyStatuses()
{
    for (size_t i = 0; i < static_cast<size_t>(Key::Count); ++i) {
        m_keyStatuses[i] = sf::Keyboard::isKeyPressed(m_keyMappings[i]);
    }
}

///////////////////////////////////////////////////////////////////////////
void State::clearAllKeyStatuses()
{
    m_keyStatuses.fill(false);
}

///////////////////////////////////////////////////////////////////////////
bool State::getKeyPressedStatus(Key key)
{
    return m_keyPressedStatuses[static_cast<size_t>(key)];
}

///////////////////////////////////////////////////////////////////////////
void State::setKeyPressedStatus(sf::Keyboard::Key sfKey, bool status)
{
    auto it = std::find(m_keyMappings.begin(), m_keyMappings.end(), sfKey);

    if (it != m_keyMappings.end()) {
        m_keyPressedStatuses[static_cast<size_t>(*it)] = status;
    }
}

///////////////////////////////////////////////////////////////////////////
void State::clearAllKeyPressedStatuses()
{
    m_keyPressedStatuses.fill(false);
}

///////////////////////////////////////////////////////////////////////////
void State::rebindKey(Key key, sf::Keyboard::Key sfKey)
{
    auto it = std::find(m_keyMappings.begin(), m_keyMappings.end(), sfKey);

    if (it != m_keyMappings.end() &&
        (it - m_keyMappings.begin()) != static_cast<int>(key)) {

        *it = m_keyMappings[static_cast<size_t>(key)];
        m_keyMappings[static_cast<size_t>(key)] = sfKey;
    }
    else {
        m_keyMappings[static_cast<size_t>(key)] = sfKey;
    }
}

///////////////////////////////////////////////////////////////////////////
bool State::getMouseStatus(MouseButton button)
{
    switch (button) {
        case MouseButton::Left:
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);
            break;
        case MouseButton::Right:
            return sf::Mouse::isButtonPressed(sf::Mouse::Right);
            break;
    }
}

///////////////////////////////////////////////////////////////////////////
void State::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    target.draw(*zoneManager);
    target.draw(*windowManager);

    if (showDebug) {
        target.draw(*debugManager);
    }
}
