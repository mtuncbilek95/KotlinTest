#pragma once

#include <Runtime/Graphics/Instance/GfxInstanceDesc.h>
#include <Runtime/Graphics/Volk/volk.h>

#include <vector>
#include <string>

#define VK_USE_PLATFORM_ANDROID_KHR
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_android.h>

class GfxInstance {
public:
    explicit GfxInstance(const GfxInstanceDesc& desc);
    ~GfxInstance();

    // No Copy
    GfxInstance(const GfxInstance&) = delete;
    GfxInstance& operator=(const GfxInstance&) = delete;

    [[nodiscard]] VkInstance Instance() const { return mInstance; }
    [[nodiscard]] VkPhysicalDevice PhysicalDevice() const { return mPhysicalDevice; }

private:
    VkInstance mInstance;
    VkPhysicalDevice mPhysicalDevice;

#if defined(ENGINE_DEBUG)
    VkDebugUtilsMessengerEXT mDebugMessenger;
#endif
};


