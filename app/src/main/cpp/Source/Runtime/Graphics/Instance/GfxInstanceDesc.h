#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <vulkan/vulkan.h>

struct GfxInstanceDesc {
    std::string appName       = "VulkanApp";
    uint32_t    appVersion    = VK_MAKE_VERSION(1, 0, 0);
    std::string engineName    = "GfxEngine";
    uint32_t    engineVersion = VK_MAKE_VERSION(1, 0, 0);
    uint32_t    apiVersion    = VK_API_VERSION_1_1;

    std::vector<std::string_view> extensions;
    std::vector<std::string_view> layers;
};