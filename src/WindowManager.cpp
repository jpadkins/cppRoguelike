///////////////////////////////////////////////////////////////////////////////
/// @file   WindowManager.cpp
/// @author Jacob Adkins (jpadkins)
/// @brief  Class that manages open Windows (in the GUI)
///////////////////////////////////////////////////////////////////////////////

#include "WindowManager.hpp"

///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////

#include <memory>

///////////////////////////////////////////////////////////////////////////////
void WindowManager::remove(const std::string& tag)
{
    auto frameIter = getWindowIter(tag);

    if (frameIter != m_windows.end()) {
        m_windows.erase(frameIter);
    }
    else {
        log_warn("Window is not open: " + tag);
    }
}

///////////////////////////////////////////////////////////////////////////////
void WindowManager::setHighest(const std::string& tag)
{
    auto frameIter = getWindowIter(tag);

    if (frameIter != m_windows.end()) {
        m_windows.splice(m_windows.end(), m_windows, frameIter);
    }
    else {
        log_warn("Window is not open: " + tag);
    }
}

///////////////////////////////////////////////////////////////////////////////
void WindowManager::add(Window* frame)
{
    m_windows.emplace_back(std::unique_ptr<Window>(frame));
}

///////////////////////////////////////////////////////////////////////////////
void WindowManager::update()
{
    bool mouseConsumed = false;

    for (auto it = m_windows.rbegin(); it != m_windows.rend(); ++it) {
        if (!mouseConsumed &&
            ((*it)->containsMouse() || Window::focus == (*it)->tag)) {

            (*it)->consumeMouse = true;
            mouseConsumed = true;
        }
        else {
            (*it)->consumeMouse = false;
        }

        (*it)->update();
    }
}

///////////////////////////////////////////////////////////////////////////////
void WindowManager::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    for (auto& frame : m_windows) { target.draw(*frame); }
}

///////////////////////////////////////////////////////////////////////////////
WindowManager::WindowList::iterator WindowManager::getWindowIter(
    const std::string& tag)
{
    auto tagsEqual = [tag](const auto& frame) {
        return frame->tag == tag;
    };

    return std::find_if(m_windows.begin(), m_windows.end(), tagsEqual);
}
