//
// Created by Amik on 2024/2/3.
//

#include "VulkanWrapper.h"
#include <VulkanInitializers.hpp>
#include <VulkanTools.h>

namespace VulkanWrapper
{
    VkCommandBuffer CommandBuffer::CreateCommandBuffer(VkDevice device, VkCommandPool cmdPool, VkCommandBufferLevel level)
    {
        VkCommandBufferAllocateInfo cmdBufAllocateInfo = vks::initializers::commandBufferAllocateInfo(cmdPool, level, 1);
        VkCommandBuffer cmdBuffer;
        VK_CHECK_RESULT(vkAllocateCommandBuffers(device, &cmdBufAllocateInfo, &cmdBuffer));
        return cmdBuffer;
    }

    void CommandBuffer::BeginCommandBuffer(VkCommandBuffer cmd)
    {
        VkCommandBufferBeginInfo cmdBufInfo = vks::initializers::commandBufferBeginInfo();
        VK_CHECK_RESULT(vkBeginCommandBuffer(cmd, &cmdBufInfo));
    }

    void CommandBuffer::EndCommandBuffer(VkCommandBuffer cmd)
    {
        if (cmd == VK_NULL_HANDLE) return;
        VK_CHECK_RESULT(vkEndCommandBuffer(cmd));
    }

    // TODO : 存疑
    void CommandBuffer::SubmitCommandBuffer(VkDevice device, VkQueue queue, VkCommandBuffer cmd)
    {
        // Create fence to ensure that the command buffer has finished executing
        VkFenceCreateInfo fenceInfo = vks::initializers::fenceCreateInfo(VK_FLAGS_NONE);
        VkFence fence;
        VK_CHECK_RESULT(vkCreateFence(device, &fenceInfo, nullptr, &fence));

        VkSubmitInfo submitInfo = vks::initializers::submitInfo();
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &cmd;

        VK_CHECK_RESULT(vkQueueSubmit(queue, 1, &submitInfo, fence));
        VK_CHECK_RESULT(vkWaitForFences(device, 1, &fence, VK_TRUE, DEFAULT_FENCE_TIMEOUT));
        vkDestroyFence(device, fence, nullptr);
    }


} // VulkanWrapper