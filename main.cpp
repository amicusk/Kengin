#include <iostream>
#include <memory>
#include "VulkanApplication.h"

int main()
{
    using namespace std::literals::string_view_literals;

    auto application = VulkanContext::VulkanApplication::GetInstance();

    application->Init();
    application->Prepare();
    application->Update();
    application->Render();
    application->Release();
}
