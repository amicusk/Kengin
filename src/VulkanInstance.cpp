//
// Created by Amik on 2024/1/30.
//

#include "VulkanInstance.h"

namespace VulkanContext
{
    VkResult VulkanInstance::CreateInstance(std::vector<const char*>& layers, std::vector<const char*>& extensions, std::string_view appName)
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

        instanceCreateInfo.enabledExtensionCount = supportedInstanceExtensions.size();
        instanceCreateInfo.ppEnabledExtensionNames = supportedInstanceExtensions.data();

        instanceCreateInfo.enabledLayerCount = requestedLayers.size();
        instanceCreateInfo.ppEnabledLayerNames = requestedLayers.data();

        VK_CHECK_RESULT(vkCreateInstance(&instanceCreateInfo, nullptr, &instance));
    }

    void VulkanInstance::DestroyInstance()
    {
        vkDestroyInstance(instance, nullptr);
    }

    void VulkanInstance::CollectExtensionsAndLayers()
    {
        requestedInstanceExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);

//#if defined(_WIN32)
//        requestedInstanceExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
//#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
//        requestedInstanceExtensions.push_back(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
//#elif defined(_DIRECT2DISPLAY)
//	    requestedInstanceExtensions.push_back(VK_KHR_DISPLAY_EXTENSION_NAME);
//#elif defined(VK_USE_PLATFORM_DIRECTFB_EXT)
//	    requestedInstanceExtensions.push_back(VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME);
//#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
//	    requestedInstanceExtensions.push_back(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);
//#elif defined(VK_USE_PLATFORM_XCB_KHR)
//	    requestedInstanceExtensions.push_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);
//#elif defined(VK_USE_PLATFORM_IOS_MVK)
//	    requestedInstanceExtensions.push_back(VK_MVK_IOS_SURFACE_EXTENSION_NAME);
//#elif defined(VK_USE_PLATFORM_MACOS_MVK)
//	    requestedInstanceExtensions.push_back(VK_MVK_MACOS_SURFACE_EXTENSION_NAME);
//#elif defined(VK_USE_PLATFORM_HEADLESS_EXT)
//	    requestedInstanceExtensions.push_back(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME);
//#elif defined(VK_USE_PLATFORM_SCREEN_QNX)
//	    requestedInstanceExtensions.push_back(VK_QNX_SCREEN_SURFACE_EXTENSION_NAME);
//#endif
    }
}