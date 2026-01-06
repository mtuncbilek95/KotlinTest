#include "VAssert.h"

#define VOLK_IMPLEMENTATION
#include <Graphics/Volk/volk.h>

#include <Log/Log.h>

void VAssert::VkAssert(VkResult res, const std::string_view &name) {
    if (res != VK_SUCCESS && res != VK_ERROR_DEVICE_LOST && res != VK_ERROR_INITIALIZATION_FAILED)
        Log::Error("{} - {}", name,int32_t(res));

    if(res == VK_ERROR_DEVICE_LOST || res == VK_ERROR_INITIALIZATION_FAILED)
        Log::Fatal("{} - {}", name, int32_t(res));
}
