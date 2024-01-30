//
// Created by Amik on 2024/1/30.
//

#include <format>
#include "VulkanInstance.h"

namespace VulkanContext
{
    VkResult VulkanInstance::CreateInstance(std::string_view appName)
    {
        CollectExtensionsAndLayers();

        VkApplicationInfo appInfo {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = appName.data();
        appInfo.pEngineName = appName.data();
        appInfo.engineVersion = 1;
        appInfo.apiVersion = VK_API_VERSION_1_3;

        VkInstanceCreateInfo instanceCreateInfo {};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pNext = nullptr;
        instanceCreateInfo.pApplicationInfo = &appInfo;

        instanceCreateInfo.enabledExtensionCount = enabledInstanceExtensions.size();
        instanceCreateInfo.ppEnabledExtensionNames = enabledInstanceExtensions.data();

        instanceCreateInfo.enabledLayerCount = enabledLayers.size();
        instanceCreateInfo.ppEnabledLayerNames = enabledLayers.data();

        VK_CHECK_RESULT(vkCreateInstance(&instanceCreateInfo, nullptr, &instance));
    }

    void VulkanInstance::DestroyInstance()
    {
        vkDestroyInstance(instance, nullptr);
    }

    void VulkanInstance::CollectExtensionsAndLayers()
    {
        //=========================================================================
        // Extensions
        //=========================================================================

        requestedInstanceExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);

#if defined(VK_USE_PLATFORM_WIN32_KHR)
        requestedInstanceExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
        requestedInstanceExtensions.push_back(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_IOS_MVK)
	    requestedInstanceExtensions.push_back(VK_MVK_IOS_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
	    requestedInstanceExtensions.push_back(VK_MVK_MACOS_SURFACE_EXTENSION_NAME);
#endif

        uint32_t extCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);
        if (extCount > 0)
        {
            std::vector<VkExtensionProperties> extensions(extCount);
            VK_CHECK_RESULT(vkEnumerateInstanceExtensionProperties(nullptr, &extCount, &extensions.front()));
            auto supportedInstanceExtensions = extensions | std::views::transform([](VkExtensionProperties extension) { return extension.extensionName; });

            for (auto extension : requestedInstanceExtensions)
            {
                if (std::find(supportedInstanceExtensions.begin(), supportedInstanceExtensions.end(), extension) == supportedInstanceExtensions.end())
                    std::cerr << std::format("Enabled instance extension {} is not present at instance level\n", extension);

                enabledInstanceExtensions.push_back(extension);
            }
        }

        //=========================================================================
        // Layers
        //=========================================================================

        enabledLayers.push_back("VK_LAYER_LUNARG_api_dump");
    }
}