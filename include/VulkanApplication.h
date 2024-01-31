//
// Created by Amik on 2024/1/30.
//

#ifndef KENGIN_VULKANAPPLICATION_H
#define KENGIN_VULKANAPPLICATION_H

#include "VulkanInstance.h"
#include "VulkanDevice.h"

#include <memory>
#include <mutex>

namespace VulkanContext
{
    using namespace std::literals::string_view_literals;

    class VulkanApplication // Singleton
    {
        //========================================================================
        // 单例类基础实现
        //========================================================================

    public:
        VulkanApplication(const VulkanApplication&) = delete;
        VulkanApplication(VulkanApplication&&) = delete;
        VulkanApplication& operator=(const VulkanApplication&) = delete;
        VulkanApplication& operator=(VulkanApplication&&) = delete;

        ~VulkanApplication();

        static VulkanApplication* GetInstance()
        {
            std::call_once(onlyOnce, [](){ instance.reset(new VulkanApplication()); });
            return instance.get();
        }

    private:
        static std::unique_ptr<VulkanApplication> instance;
        static std::once_flag onlyOnce;

    private:
        VulkanApplication();

        //========================================================================
        // Program Life Cycle
        //========================================================================

    public:
        void Init();
        void Prepare();
        void Update();
        void Render();
        void Release();

        //========================================================================
        // Vulkan Context 相关
        //========================================================================

    public:
        std::unique_ptr<VulkanInstance> vulkanInstance;
        std::unique_ptr<VulkanDevice> vulkanDevice;

    private:
        // Instance
        void CreateVulkanInstance() const { vulkanInstance->CreateInstance("Kengin"sv); }
        void CollectInstanceExtensionsAndLayers() const;

        // Device
        VkPhysicalDevice PickPhysicalDevice() const;
        void CollectDeviceExtensionsAndFeatures() const;
    };
} // VulkanContext

#endif //KENGIN_VULKANAPPLICATION_H
