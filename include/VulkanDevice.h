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
        VkPhysicalDeviceFeatures gpuFeatures;
        VkPhysicalDeviceMemoryProperties memoryProperties;

        VkQueue queue;
        std::vector<VkQueueFamilyProperties> queueFamilyProperties;
        uint32_t graphicsQueueFamilyIndex;
        uint32_t queueFamilyCount;

    public:
        VulkanDevice(VkPhysicalDevice gpu);
        ~VulkanDevice();

        void CreateDevice();
        void EnableExtension(const char* ext) { requestedDeviceExtensions.push_back(ext); }
        void EnableFeature(const char* feature) { enabledDeviceFeatures.push_back(feature); }

    private:
        std::vector<const char*> requestedDeviceExtensions = {};  // 获取所有需要的拓展
        std::vector<const char*> enabledDeviceExtensions = {};    // 需要且支持的拓展
        std::vector<const char*> enabledDeviceFeatures = {};
        void CollectExtensionsAndLayers();

        void PickPhysicalDevice(VkInstance instance);
        void CheckExtensionsIfSupported();
    };

} // VulkanContext

#endif //KENGIN_VULKANDEVICE_H
