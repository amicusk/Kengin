//
// Created by Amik on 2024/2/3.
//

#ifndef KENGIN_VULKANWRAPPER_H
#define KENGIN_VULKANWRAPPER_H

#include <vulkan/vulkan.h>

namespace VulkanWrapper
{
    class CommandBuffer
    {
    public:
        static VkCommandBuffer CreateCommandBuffer(VkDevice device, VkCommandPool cmdPool, VkCommandBufferLevel level);
        static void BeginCommandBuffer(VkCommandBuffer cmd);
        static void EndCommandBuffer(VkCommandBuffer cmd);
        static void SubmitCommandBuffer(VkDevice device, VkQueue queue, VkCommandBuffer cmd);
    };

} // VulkanWrapper

#endif //KENGIN_VULKANWRAPPER_H
