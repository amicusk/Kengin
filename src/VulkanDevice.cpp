//
// Created by Amik on 2024/1/31.
//

#define ENABLE_DEVICE_FEATURE_IF(x) enabledFeatures.x = gpuFeatures.x ? VK_TRUE : VK_FALSE

#include "VulkanTools.h"
#include "VulkanDevice.h"
#include "VulkanApplication.h"

#include <format>

namespace VulkanContext
{
    VulkanDevice::VulkanDevice(VkPhysicalDevice gpu)
    {
        this->gpu = gpu;
        std::memset(&enabledFeatures, 0, sizeof(enabledFeatures));

        uint32_t queueFamilyCount;
        vkGetPhysicalDeviceQueueFamilyProperties(this->gpu, &queueFamilyCount, nullptr);
        assert(queueFamilyCount > 0);
        queueFamilyProperties.resize(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(this->gpu, &queueFamilyCount, queueFamilyProperties.data());

        vkGetPhysicalDeviceProperties(gpu, &gpuProperties);
        vkGetPhysicalDeviceMemoryProperties(gpu, &memoryProperties);

        SetupDeviceFeatures();
    }

    void VulkanDevice::CreateDevice()
    {
        CheckExtensionsIfSupported();

        const float queuePriority = 0.0f;
        // TODO： 多线程渲染
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};

        queueFamilyIndices.graphics = GetQueueFamilyIndex(VK_QUEUE_GRAPHICS_BIT);
        VkDeviceQueueCreateInfo queueInfo {};
        queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfo.queueFamilyIndex = queueFamilyIndices.graphics;
        queueInfo.queueCount = 1;
        queueInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueInfo);

        VkDeviceCreateInfo deviceCreateInfo {};
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.queueCreateInfoCount = queueCreateInfos.size();
        deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
        deviceCreateInfo.enabledExtensionCount = enabledDeviceExtensions.size();
        deviceCreateInfo.ppEnabledExtensionNames = enabledDeviceExtensions.data();
        deviceCreateInfo.pEnabledFeatures = &enabledFeatures;

        VK_CHECK_RESULT(vkCreateDevice(gpu, &deviceCreateInfo, nullptr, &device));
    }

    void VulkanDevice::DestroyDevice()
    {
        vkDestroyDevice(device, nullptr);
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

    void VulkanDevice::SetupDeviceFeatures()
    {
        VkPhysicalDeviceFeatures gpuFeatures;
        vkGetPhysicalDeviceFeatures(gpu, &gpuFeatures);

        ENABLE_DEVICE_FEATURE_IF(fillModeNonSolid);
        ENABLE_DEVICE_FEATURE_IF(samplerAnisotropy);
    }

    uint32_t VulkanDevice::GetQueueFamilyIndex(VkQueueFlags queueFlags) const
    {
        // Dedicated queue for compute
        // Try to find a queue family index that supports compute but not graphics
        if ((queueFlags & VK_QUEUE_COMPUTE_BIT) == queueFlags)
        {
            auto pred = [](const VkQueueFamilyProperties& qfp) -> bool
            {
                return (qfp.queueFlags & VK_QUEUE_COMPUTE_BIT) && !(qfp.queueFlags & VK_QUEUE_GRAPHICS_BIT);
            };
            auto iterator = std::find_if(queueFamilyProperties.begin(), queueFamilyProperties.end(), pred);
            if (iterator != queueFamilyProperties.end()) return std::distance(queueFamilyProperties.begin(), iterator);
        }

        // Dedicated queue for transfer
        // Try to find a queue family index that supports transfer but not graphics and compute
        if ((queueFlags & VK_QUEUE_TRANSFER_BIT) == queueFlags)
        {
            auto pred = [](const VkQueueFamilyProperties& qfp) -> bool
            {
                return (qfp.queueFlags & VK_QUEUE_TRANSFER_BIT) && !(qfp.queueFlags & VK_QUEUE_GRAPHICS_BIT) && !(qfp.queueFlags & VK_QUEUE_COMPUTE_BIT);
            };
            auto iterator = std::find_if(queueFamilyProperties.begin(), queueFamilyProperties.end(), pred);
            if (iterator != queueFamilyProperties.end()) return std::distance(queueFamilyProperties.begin(), iterator);
        }

        // For other queue types or if no separate compute queue is present, return the first one to support the requested flags
        auto iterator = std::find_if(queueFamilyProperties.begin(), queueFamilyProperties.end(),
                               [queueFlags](const VkQueueFamilyProperties& qfp) { return (qfp.queueFlags & queueFlags) == queueFlags; });
        if (iterator != queueFamilyProperties.end())
            return std::distance(queueFamilyProperties.begin(), iterator);

        throw std::runtime_error("Could not find a matching queue family index");
    }


} // VulkanContext