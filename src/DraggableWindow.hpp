///////////////////////////////////////////////////////////////////////////////
/// @file   DraggableWindow.hpp
/// @author Jacob Adkins (jpadkins)
/// @brief  Parent class for UI elements that can be dragged with the mouse
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////

#include "Window.hpp"

///////////////////////////////////////////////////////////////////////////////
/// @brief  Parent class for UI elements that can be dragged with the mouse
///////////////////////////////////////////////////////////////////////////////
class DraggableWindow : public Window {
public:

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Constructor
    ///////////////////////////////////////////////////////////////////////////
    explicit DraggableWindow(const std::string& tag);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Disable default constructor
    ///////////////////////////////////////////////////////////////////////////
    DraggableWindow() = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Disable default constructor
    ///////////////////////////////////////////////////////////////////////////
    DraggableWindow(const DraggableWindow&) = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Disable assignment operator
    ///////////////////////////////////////////////////////////////////////////
    void operator=(const DraggableWindow&) = delete;

protected:

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Updates the drag logic and drags the window if needed
    ///
    /// Children should call this once per frame (i.e. in their update() func)
    ///////////////////////////////////////////////////////////////////////////
    void updateDrag();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief Checks whether or not a position is within the draggable region
    ///
    /// Override this in children to implement class-specific dragging
    /// behavior. By default this always returns true.
    ///
    /// @param position Position in frame-space to check
    ///
    /// @return True if the position is within the window's draggable region,
    ///         false otherwise
    ///////////////////////////////////////////////////////////////////////////
    virtual bool withinDraggableRegion(const sf::Vector2i& position);

private:

    ///////////////////////////////////////////////////////////////////////////

    bool m_dragging = false;
};
