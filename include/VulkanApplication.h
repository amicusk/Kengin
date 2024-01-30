//
// Created by Amik on 2024/1/30.
//

#ifndef KENGIN_VULKANAPPLICATION_H
#define KENGIN_VULKANAPPLICATION_H

#include "VulkanInstance.h"

namespace VulkanContext
{
    class VulkanApplication
    {
    public:
        VkInstance instance;

    public:
        VulkanApplication();
        ~VulkanApplication();
    };
} // VulkanContext

#endif //KENGIN_VULKANAPPLICATION_H
