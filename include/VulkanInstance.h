//
// Created by Amik on 2024/1/30.
//

#ifndef KENGIN_VULKANINSTANCE_H
#define KENGIN_VULKANINSTANCE_H

#include <vulkan/vulkan_core.h>
#include "VulkanTools.h"

#include <vector>
#include <ranges>
using namespace std::literals::string_view_literals;

namespace VulkanContext
{
    class VulkanInstance
    {
    public:
        VkInstance instance;

        VkResult CreateInstance(std::vector<const char*>& layers, std::vector<const char*>& extensions, std::string_view appName);
        void DestroyInstance();

    private:
        std::vector<const char*> requestedInstanceExtensions = {};
        std::vector<const char*> supportedInstanceExtensions = {};

        std::vector<const char*> requestedLayers = {};
        void CollectExtensionsAndLayers();
    };
}





#endif //KENGIN_VULKANINSTANCE_H
