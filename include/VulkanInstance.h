//
// Created by Amik on 2024/1/30.
//

#ifndef KENGIN_VULKANINSTANCE_H
#define KENGIN_VULKANINSTANCE_H

#include <vulkan/vulkan.h>
#include "VulkanTools.h"

#include <vector>
#include <ranges>

namespace VulkanContext
{
    class VulkanInstance
    {
    public:
        VkInstance instance;

        void CreateInstance(std::string_view appName);
        void DestroyInstance();

        void EnableExtension(const char* ext) { requestedInstanceExtensions.push_back(ext); }
        void EnableLayer(const char* layer) { enabledLayers.push_back(layer); }

    private:
        std::vector<const char*> requestedInstanceExtensions = {};  // 获取所有需要的拓展
        std::vector<const char*> enabledInstanceExtensions = {};    // 需要且支持的拓展
        std::vector<const char*> enabledLayers = {};
        void CheckExtensionsIfSupported();
    };
}

#endif //KENGIN_VULKANINSTANCE_H
