//
// Created by Amik on 2024/1/30.
//

#include "VulkanApplication.h"

namespace VulkanContext
{
    static std::unique_ptr<VulkanApplication> appInstance;
    static std::once_flag onlyOnce;

    VulkanApplication* VulkanApplication::GetInstance()
    {
        std::call_once(onlyOnce, [&](){ appInstance.reset(new VulkanApplication()); });
        return appInstance.get();
    }
    
    VulkanApplication::VulkanApplication()
    {
        instance = std::make_unique<VulkanInstance>();
        CollectInstanceExtensionsAndLayers();
        CreateVulkanInstance();

        device = std::make_unique<VulkanDevice>(PickPhysicalDevice());
        CollectDeviceExtensionsAndFeatures();
        device->CreateDevice();
    }

    VulkanApplication::~VulkanApplication()
    {
        device->DestroyDevice();
        instance->DestroyInstance();
    }

    void VulkanApplication::Init()
    {
    }

    void VulkanApplication::Prepare()
    {
    }

    void VulkanApplication::Update()
    {
    }

    void VulkanApplication::Render()
    {
    }

    void VulkanApplication::Release()
    {
    }

    void VulkanApplication::CollectInstanceExtensionsAndLayers() const
    {
        //=========================================================================
        // Extensions
        //=========================================================================

        instance->EnableExtension(VK_KHR_SURFACE_EXTENSION_NAME);

#if defined(VK_USE_PLATFORM_WIN32_KHR)
        instance->EnableExtension(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
        instance->EnableExtension(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_IOS_MVK)
        instance->EnableExtension(VK_MVK_IOS_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
        instance->EnableExtension(VK_MVK_MACOS_SURFACE_EXTENSION_NAME);
#endif

        if (true)
        {
            instance->EnableExtension(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);	// SRS - Dependency when VK_EXT_DEBUG_MARKER is enabled
            instance->EnableExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        //=========================================================================
        // Layers
        //=========================================================================

        if(true)
        {
            instance->EnableLayer("VK_LAYER_KHRONOS_validation");
        }
    }

    void VulkanApplication::CollectDeviceExtensionsAndFeatures() const
    {
        device->EnableExtension(VK_KHR_SHADER_NON_SEMANTIC_INFO_EXTENSION_NAME);
    }

    VkPhysicalDevice VulkanApplication::PickPhysicalDevice() const
    {
        uint32_t gpuCount = 0;
        std::vector<VkPhysicalDevice> gpuList {};
        vkEnumeratePhysicalDevices(instance->instance, &gpuCount, nullptr);
        gpuList.resize(gpuCount);
        vkEnumeratePhysicalDevices(instance->instance, &gpuCount, gpuList.data());

        // TODO : 自动选择最优 GPU
        return gpuList[0];
    }
} // VulkanContext