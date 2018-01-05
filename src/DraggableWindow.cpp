///////////////////////////////////////////////////////////////////////////////
/// @file   DraggableWindow.hpp
/// @author Jacob Adkins (jpadkins)
/// @brief  Parent class for UI elements that can be dragged with the mouse
///////////////////////////////////////////////////////////////////////////////

#include "DraggableWindow.hpp"

///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////

#include "State.hpp"
#include "WindowManager.hpp"

///////////////////////////////////////////////////////////////////////////////
DraggableWindow::DraggableWindow(const std::string& tag) : Window(tag) {}

///////////////////////////////////////////////////////////////////////////////
void DraggableWindow::updateDrag()
{
    if (consumeMouse) {
        if (State::get().getMouseStatus(MouseButton::Left)) {
            if (!m_dragging &&
                State::get().leftClick &&
                !m_lastPressed & Window::focus.empty() &&
                withinDraggableRegion(State::get().mousePosition)) {

                State::get().windowManager->setHighest(tag);
                Window::focus = tag;
                m_dragging = true;
            }
            else if (m_dragging) {
                matchLastMouseMovement();
            }
            m_lastPressed = true;
        }
        else if (m_dragging || m_lastPressed || !Window::focus.empty()) {
            Window::focus.clear();
            m_lastPressed = false;
            m_dragging = false;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
bool DraggableWindow::withinDraggableRegion(const sf::Vector2i&)
{
    return true;
}
