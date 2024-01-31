//
// Created by Amik on 2024/1/31.
//

#include "VulkanTools.h"
#include "VulkanDevice.h"
#include "VulkanApplication.h"

#include <format>

namespace VulkanContext
{
    VulkanDevice::VulkanDevice(VkPhysicalDevice gpu)
    {
        this->gpu = gpu;

        vkGetPhysicalDeviceProperties(gpu, &gpuProperties);
        vkGetPhysicalDeviceFeatures(gpu, &gpuFeatures);
        vkGetPhysicalDeviceMemoryProperties(gpu, &memoryProperties);
    }

    void VulkanDevice::CreateDevice()
    {
        CheckExtensionsIfSupported();

        VkDeviceCreateInfo deviceCreateInfo {};
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        VK_CHECK_RESULT(vkCreateDevice(gpu, &deviceCreateInfo, nullptr, &device));
    }

    void VulkanDevice::PickPhysicalDevice(VkInstance instance)
    {
        uint32_t gpuCount = 0;
        std::vector<VkPhysicalDevice> gpuList {};
        vkEnumeratePhysicalDevices(instance, &gpuCount, nullptr);
        gpuList.resize(gpuCount);
        vkEnumeratePhysicalDevices(instance, &gpuCount, gpuList.data());

        // TODO : 自动选择最优 GPU
        gpu = gpuList[0];
    }

    void VulkanDevice::CheckExtensionsIfSupported()
    {
        uint32_t extCount = 0;
        vkEnumerateDeviceExtensionProperties(gpu, nullptr, &extCount, nullptr);
        if (extCount > 0)
        {
            std::vector<VkExtensionProperties> extensions(extCount);
            VK_CHECK_RESULT(vkEnumerateDeviceExtensionProperties(gpu, nullptr, &extCount, &extensions.front()));

            std::vector<std::string_view> supportedDeviceExtensions;
            supportedDeviceExtensions.reserve(extensions.size());
            std::transform(extensions.begin(), extensions.end(), std::back_inserter(supportedDeviceExtensions), [](const VkExtensionProperties& ext) { return ext.extensionName; });

            for (auto extension : requestedDeviceExtensions)
            {
                if (std::find(supportedDeviceExtensions.begin(), supportedDeviceExtensions.end(), extension) == supportedDeviceExtensions.end())
                    std::cerr << std::format("Enabled instance extension {} is not present at device level\n", extension);

                enabledDeviceExtensions.push_back(extension);
            }
        }
    }
} // VulkanContext