#pragma once

#include <Runtime/Graphics/Instance/VInstance.h>

class RenderEngine {
public:
    void OnDraw(double deltaTime = 0.16);

private:
    VInstance mInstance;
    // VDevice mDevice;
    // VSurface mSurface;
    // VSwapchain mSwapchain;
    // VCmdPool mPresentPool;
    // std::array<VCmdBuffer, 2> mPresentBuffers;

    // std::unordered<std::thread::id, VCmdPool> mThreadedPools; // <threadId, CommandPool>
    // std::unordered_map<Guid, VCmdBuffer> mCmdBuffers; // <PoolId, CmdBuffer>
    // std::unoredered_map<std::string, VDescLayout> mCachedLayouts;
    // std::unoredered_map<std::string, VPipeline> mCachedPipelines;
    // std::unordered_map<Guid, std::shared_ptr<Mesh>> mLoadedMeshes;
};