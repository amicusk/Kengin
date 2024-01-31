//
// Created by Amik on 2024/1/30.
//

#include "VulkanApplication.h"

namespace VulkanContext
{
    VulkanApplication::VulkanApplication()
    {
        vulkanInstance = std::make_unique<VulkanInstance>();
        CollectInstanceExtensionsAndLayers();
        CreateVulkanInstance();

        vulkanDevice = std::make_unique<VulkanDevice>(PickPhysicalDevice());
        CollectDeviceExtensionsAndFeatures();
        vulkanDevice->CreateDevice();
    }

    VulkanApplication::~VulkanApplication()
    {

    }

    void VulkanApplication::CollectInstanceExtensionsAndLayers() const
    {
        //=========================================================================
        // Extensions
        //=========================================================================

        vulkanInstance->EnableExtension(VK_KHR_SURFACE_EXTENSION_NAME);

#if defined(VK_USE_PLATFORM_WIN32_KHR)
        vulkanInstance->EnableExtension(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
        vulkanInstance->EnableExtension(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_IOS_MVK)
        vulkanInstance->EnableExtension(VK_MVK_IOS_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
        vulkanInstance->EnableExtension(VK_MVK_MACOS_SURFACE_EXTENSION_NAME);
#endif

        //=========================================================================
        // Layers
        //=========================================================================

        vulkanInstance->EnableLayer("VK_LAYER_LUNARG_api_dump");
    }

    void VulkanApplication::CollectDeviceExtensionsAndFeatures() const
    {

    }

    VkPhysicalDevice VulkanApplication::PickPhysicalDevice() const
    {
        uint32_t gpuCount = 0;
        std::vector<VkPhysicalDevice> gpuList {};
        vkEnumeratePhysicalDevices(vulkanInstance->instance, &gpuCount, nullptr);
        gpuList.resize(gpuCount);
        vkEnumeratePhysicalDevices(vulkanInstance->instance, &gpuCount, gpuList.data());

        // TODO : 自动选择最优 GPU
        return gpuList[0];
    }
} // VulkanContext