#include "VInstance.h"

#include <unordered_map>

#include <Log/Log.h>
#include <Graphics/Assert/VAssert.h>
#include <Graphics/Volk/volk.h>

static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                    VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                    void *pUserData) {
    switch (messageSeverity) {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            Log::Info("{}", pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            Log::Debug("{}", pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            Log::Warn("{}", pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            Log::Error("{}", pCallbackData->pMessage);
            break;
        default:
            break;
    }

    return false;
}

VInstance::VInstance() : mInstance(nullptr), mVideoCard(nullptr) {
    VAssert::VkAssert(volkInitialize(), "VInstance");

#if defined(ENGINE_DEBUG)
    mDebugMessenger = VK_NULL_HANDLE;
#endif

    struct ExtensionEntry {
        const char *name;
        bool support;
    };

    std::vector<ExtensionEntry> extensions;
    std::vector<const char *> workingExtensions;

    extensions.push_back({VK_KHR_SURFACE_EXTENSION_NAME, false});
    extensions.push_back({VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME, false});
    extensions.push_back({VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME, false});

    extensions.push_back({VK_KHR_ANDROID_SURFACE_EXTENSION_NAME, false});

#if defined(ENGINE_DEBUG)
    extensions.push_back({VK_EXT_DEBUG_UTILS_EXTENSION_NAME, false});
    extensions.push_back({VK_EXT_DEBUG_REPORT_EXTENSION_NAME, false});
#endif

    uint32_t extensionCount = 0;
    VAssert::VkAssert(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr), "VInstance");

    std::vector<VkExtensionProperties> allExtensions(extensionCount);
    VAssert::VkAssert(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, allExtensions.data()), "VInstance");

    for (size_t i = 0; i < extensions.size(); ++i) {
        for (auto &extension: allExtensions) {
            if (strcmp(extensions[i].name, extension.extensionName) == 0) {
                extensions[i].support = true;
                workingExtensions.push_back(extensions[i].name);
                break;
            }
        }
    }

    // Print unsupported extensions
    for (auto &extension: extensions) {
        if (!extension.support)
            Log::Warn("Extension not supported: {}", extension.name);
    }

    uint32_t layerCount = 0;
    VAssert::VkAssert(vkEnumerateInstanceLayerProperties(&layerCount, nullptr), "VInstance");
    std::vector<VkLayerProperties> allLayers(layerCount);
    VAssert::VkAssert(vkEnumerateInstanceLayerProperties(&layerCount, allLayers.data()), "VInstance");

    std::vector<ExtensionEntry> wantedLayers;
    std::vector<const char *> workingLayers;

#if defined(ENGINE_DEBUG)
    wantedLayers.push_back({"VK_LAYER_KHRONOS_validation", false});
    wantedLayers.push_back({"VK_LAYER_LUNARG_screenshot", false});
    wantedLayers.push_back({"VK_LAYER_LUNARG_monitor", false});
#endif

    for (size_t i = 0; i < wantedLayers.size(); ++i) {
        for (auto &layer: allLayers) {
            if (strcmp(wantedLayers[i].name, layer.layerName) == 0) {
                wantedLayers[i].support = true;
                workingLayers.push_back(wantedLayers[i].name);
                break;
            }
        }
    }

    // Print unsupported layers
    for (auto &layer: wantedLayers) {
        if (!layer.support)
            Log::Warn("Layer not supported: {}", layer.name);
    }

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Testing Android";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Testing Android";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_1;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(workingExtensions.size());
    createInfo.ppEnabledExtensionNames = workingExtensions.data();
    createInfo.enabledLayerCount = static_cast<uint32_t>(workingLayers.size());
    createInfo.ppEnabledLayerNames = workingLayers.data();

    VAssert::VkAssert(vkCreateInstance(&createInfo, nullptr, &mInstance), "VInstance");
    Log::Verbose("VkInstance created successfully!");

    volkLoadInstance(mInstance);

#if defined(ENGINE_DEBUG)
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
        debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugCreateInfo.pfnUserCallback = DebugCallback;
        debugCreateInfo.pUserData = nullptr;

        VAssert::VkAssert(vkCreateDebugUtilsMessengerEXT(mInstance, &debugCreateInfo, nullptr, &mDebugMessenger), "GfxVkInstance");
#endif

    uint32_t deviceCount = 0;
    VAssert::VkAssert(vkEnumeratePhysicalDevices(mInstance, &deviceCount, nullptr), "VInstance");

    // Temporary struct to hold the device and its score
    std::unordered_map<std::string, std::pair<VkPhysicalDevice, uint32_t>> allDevices;

    // Get the physical devices
    std::vector<VkPhysicalDevice> devices(deviceCount);
    VAssert::VkAssert(vkEnumeratePhysicalDevices(mInstance, &deviceCount, devices.data()), "VInstance");

    for (auto& device : devices)
    {
        // Get the device properties
        VkPhysicalDeviceProperties deviceProperties = {};
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        // Get the device features
        VkPhysicalDeviceFeatures deviceFeatures = {};
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        // Get the device memory properties
        VkPhysicalDeviceMemoryProperties deviceMemoryProperties = {};
        vkGetPhysicalDeviceMemoryProperties(device, &deviceMemoryProperties);

        // Get the device queue family properties
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties.data());

        // Hold device on allDevices
        allDevices[deviceProperties.deviceName] = { device, 0 };

        for (auto& queueFamily : queueFamilyProperties)
            allDevices[deviceProperties.deviceName].second += queueFamily.queueCount;

        // Check if the device is discrete
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            allDevices[deviceProperties.deviceName].second += 1000;
        else
            allDevices[deviceProperties.deviceName].second += 100;

        // Check if the device supports geometry shaders
        if (deviceFeatures.geometryShader)
            allDevices[deviceProperties.deviceName].second += 10;
    }

    // Get the best device
    auto bestDevice = std::max_element(allDevices.begin(), allDevices.end(),
                                       [](const std::pair<std::string, std::pair<VkPhysicalDevice, uint32_t>>& a, const std::pair<std::string, std::pair<VkPhysicalDevice, uint32_t>>& b)
                                       {
                                           return a.second.second < b.second.second;
                                       });

    Log::Info("Best device found: {}", bestDevice->first.c_str());
    mVideoCard = bestDevice->second.first;
}

VInstance::~VInstance() {

}
