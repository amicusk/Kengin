//
// Created by Amik on 2024/1/31.
//

#ifndef KENGIN_VULKANDEVICE_H
#define KENGIN_VULKANDEVICE_H

#include <vulkan/vulkan.h>
#include "VulkanTools.h"

namespace VulkanContext
{
    class VulkanDevice
    {
    public:
        VkDevice device;
        VkPhysicalDevice gpu;

        VkPhysicalDeviceProperties gpuProperties;
        VkPhysicalDeviceMemoryProperties memoryProperties;
        std::vector<VkQueueFamilyProperties> queueFamilyProperties = {};

        VkQueue queue;
        struct
        {
            uint32_t graphics;
            // uint32_t compute;
            // uint32_t transfer;
        } queueFamilyIndices;

    public:
        explicit VulkanDevice(VkPhysicalDevice gpu);
        ~VulkanDevice() = default;

        void CreateDevice();
        void DestroyDevice();
        void EnableExtension(const char* ext) { requestedDeviceExtensions.push_back(ext); }

    private:
        std::vector<const char*> requestedDeviceExtensions = {};  // 获取所有需要的拓展
        std::vector<const char*> enabledDeviceExtensions = {};    // 需要且支持的拓展
        VkPhysicalDeviceFeatures enabledFeatures;

        void CheckExtensionsIfSupported();
        void SetupDeviceFeatures();

        // Utils
    private:
        uint32_t GetQueueFamilyIndex(VkQueueFlags queueFlags) const;
    };

} // VulkanContext

#endif //KENGIN_VULKANDEVICE_H
