
#include "FrameManager.hpp"

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
void FrameManager::add(const std::string& tag, Frame* frame)
{
    m_frames.emplace_back(std::make_pair(tag, std::unique_ptr<Frame>(frame)));
}

///////////////////////////////////////////////////////////////////////////////
void FrameManager::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    for (auto& frame : m_frames) { target.draw(*frame.second); }
}

///////////////////////////////////////////////////////////////////////////////
std::list<FrameManager::FrameHandle>::iterator FrameManager::getFrameIter(
    const std::string& tag)
{
    auto tagsEqual = [tag](const FrameHandle& handle) {
        return handle.first == tag;
    };

    return std::find_if(m_frames.begin(), m_frames.end(), tagsEqual);
}
