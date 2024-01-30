#include <iostream>
#include <memory>
#include "VulkanInstance.h"

int main()
{
    using namespace std::literals::string_view_literals;

    auto instance = std::make_shared<VulkanContext::VulkanInstance>();
    instance->CreateInstance("Kengin"sv);
    instance->DestroyInstance();
}
