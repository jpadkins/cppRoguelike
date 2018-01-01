///////////////////////////////////////////////////////////////////////////////
/// @file   FrameManager.cpp
/// @author Jacob Adkins (jpadkins)
/// @brief  Class that manages Frames (windows in the GUI)
///////////////////////////////////////////////////////////////////////////////

#include "FrameManager.hpp"

///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////

#include <memory>

///////////////////////////////////////////////////////////////////////////////
void FrameManager::remove(const std::string& tag)
{
    auto frameIter = getFrameIter(tag);

    if (frameIter != m_frames.end()) {
        m_frames.erase(frameIter);
    }
    else {
        log_warn("Frame is not open: " + tag);
    }
}

///////////////////////////////////////////////////////////////////////////////
void FrameManager::setHighest(const std::string& tag)
{
    auto frameIter = getFrameIter(tag);

    if (frameIter != m_frames.end()) {
        m_frames.splice(m_frames.end(), m_frames, frameIter);
    }
    else {
        log_warn("Frame is not open: " + tag);
    }
}

///////////////////////////////////////////////////////////////////////////////
void FrameManager::add(Frame* frame)
{
    m_frames.emplace_back(std::unique_ptr<Frame>(frame));
}

///////////////////////////////////////////////////////////////////////////////
void FrameManager::update()
{
    bool mouseConsumed = false;

    for (auto it = m_frames.rbegin(); it != m_frames.rend(); ++it) {
        if (!mouseConsumed) {
            (*it)->consumeMouse = true;
            mouseConsumed = true;
        }

        (*it)->update();
    }
}

///////////////////////////////////////////////////////////////////////////////
void FrameManager::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    for (auto& frame : m_frames) { target.draw(*frame); }
}

///////////////////////////////////////////////////////////////////////////////
FrameManager::FrameList::iterator FrameManager::getFrameIter(
    const std::string& tag)
{
    auto tagsEqual = [tag](const auto& frame) {
        return frame->tag == tag;
    };

    return std::find_if(m_frames.begin(), m_frames.end(), tagsEqual);
}
