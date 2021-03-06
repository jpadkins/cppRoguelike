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
                State::get().leftClick) {

                State::get().windowManager->setHighest(tag);
                Window::focus = tag;

                if (withinDraggableRegion(State::get().mousePosition)) {
                    m_dragging = true;
                }
            }
            else if (m_dragging && canBeDragged()) {
                matchLastMouseMovement();
            }
            else if (m_dragging) {
                if (!containsMouse()) {
                    Window::focus.clear();
                    m_dragging = false;
                }
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

///////////////////////////////////////////////////////////////////////////
bool DraggableWindow::canBeDragged()
{
    return true;
}
