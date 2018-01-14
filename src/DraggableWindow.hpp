///////////////////////////////////////////////////////////////////////////////
/// @file   DraggableWindow.hpp
/// @author Jacob Adkins (jpadkins)
/// @brief  Parent class for UI elements that can be dragged with the mouse
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////

#include "Window.hpp"

// TODO: Add a virtual function in the style of withinDraggableRegion() but for
// when deciding if the window should consume mouse. For example, if a window
// has an outside border of tiles with a transparent background which are
// manually moved towards the center of the map to create a border, the
// player should be able to click through that transparent, unused outside
// border of tiles

// TODO: Don't drag the window when the new location would be outside the frame

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
