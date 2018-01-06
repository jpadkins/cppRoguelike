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
    auto it = getWindowIter(tag);

    if (it != m_windows.end()) {
        m_windows.erase(it);
    }
    else {
        log_warn("Window is not open: " + tag);
    }
}

///////////////////////////////////////////////////////////////////////////////
void WindowManager::setHighest(const std::string& tag)
{
    auto it = getWindowIter(tag);

    if (it != m_windows.end()) {
        m_windows.splice(m_windows.end(), m_windows, it);
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
    auto it = m_windows.rbegin();

    while (it != m_windows.rend()) {

        // Update window
        if (!mouseConsumed &&
            ((*it)->containsMouse() || Window::focus == (*it)->tag)) {

            (*it)->consumeMouse = true;
            mouseConsumed = true;
        }
        else {
            (*it)->consumeMouse = false;
        }

        (*it)->update();

        // Remove if need be
        if ((*it)->shouldClose) {
            auto tmpIt = it;
            std::advance(tmpIt, 1);
            m_windows.erase(tmpIt.base());
        }

        ++it;
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
