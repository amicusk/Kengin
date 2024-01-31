//
// Created by Amik on 2024/1/30.
//

#include <format>
#include "VulkanInstance.h"

namespace VulkanContext
{
    void VulkanInstance::CreateInstance(std::string_view appName)
    {
        CheckExtensionsIfSupported();

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

    void VulkanInstance::CheckExtensionsIfSupported()
    {
        uint32_t extCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);
        if (extCount > 0)
        {
            std::vector<VkExtensionProperties> extensions(extCount);
            VK_CHECK_RESULT(vkEnumerateInstanceExtensionProperties(nullptr, &extCount, &extensions.front()));

            std::vector<std::string_view> supportedInstanceExtensions;
            supportedInstanceExtensions.reserve(extensions.size());
            std::transform(extensions.begin(), extensions.end(), std::back_inserter(supportedInstanceExtensions), [](const VkExtensionProperties& ext) { return ext.extensionName; });

            for (auto extension : requestedInstanceExtensions)
            {
                if (std::find(supportedInstanceExtensions.begin(), supportedInstanceExtensions.end(), extension) == supportedInstanceExtensions.end())
                    std::cerr << std::format("Enabled instance extension {} is not present at instance level\n", extension);

                enabledInstanceExtensions.push_back(extension);
            }
        }
    }
}