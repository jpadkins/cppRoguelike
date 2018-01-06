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
                Window::focus.empty() &&
                State::get().leftClick &&
                withinDraggableRegion(State::get().mousePosition)) {

                State::get().windowManager->setHighest(tag);
                Window::focus = tag;
                m_dragging = true;
            }
            else if (m_dragging) {
                matchLastMouseMovement();
            }
        }
        else if (m_dragging || !Window::focus.empty()) {
            Window::focus.clear();
            m_dragging = false;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
bool DraggableWindow::withinDraggableRegion(const sf::Vector2i&)
{
    return true;
}
