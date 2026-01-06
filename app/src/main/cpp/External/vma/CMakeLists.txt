include(FetchContent)

if(NOT DEFINED VMA_URL)
    set(VMA_URL https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator.git)
endif()

FetchContent_Declare(
        VulkanMemoryAllocator
        GIT_REPOSITORY ${VMA_URL}
        GIT_TAG master
)

FetchContent_MakeAvailable(VulkanMemoryAllocator)