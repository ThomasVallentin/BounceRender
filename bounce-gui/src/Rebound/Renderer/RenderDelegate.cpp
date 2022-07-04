//
// Created by Thomas Vallentin on 26/04/2022.
//

#include "RenderDelegate.h"


namespace Rebound {

    bool RenderDelegate::IsRunning() {
        return false;
    }

    bool RenderDelegate::Stop() {
        return false;
    }

    bool RenderDelegate::Restart() {
        return false;
    }

    bool RenderDelegate::Pause() {
        return false;
    }

    bool RenderDelegate::Resume() {
        return false;
    }

    void RenderDelegate::SetDefaultMaterial(std::shared_ptr<Material> material) {
        m_defaultMaterial = std::move(material);
    }

    void RenderDelegate::SetFrameBuffer(std::shared_ptr<FrameBuffer> frameBuffer) {
        m_frameBuffer = std::move(frameBuffer);
    }

    RenderSharedData *RenderDelegate::GetSharedData() const {
        return nullptr;
    }

}