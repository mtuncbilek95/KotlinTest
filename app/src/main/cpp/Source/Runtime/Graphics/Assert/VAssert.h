#pragma once

#include <string_view>
#include <vulkan/vulkan.h>

struct VAssert {
    static void VkAssert(VkResult res, const std::string_view& name);
};


