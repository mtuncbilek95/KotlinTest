#pragma once

#define VK_USE_PLATFORM_ANDROID_KHR
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_android.h>

class VInstance {
public:
    VInstance();
    ~VInstance();

    VkInstance Instance() const { return mInstance; }

private:
    VkInstance mInstance;
    VkPhysicalDevice mVideoCard;

#if defined(ENGINE_DEBUG)
    VkDebugUtilsMessengerEXT mDebugMessenger;
#endif
};