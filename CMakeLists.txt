cmake_minimum_required(VERSION 3.27)

# 项目设置
project ("Kengin")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vulkan SDK设置
if(NOT DEFINED ENV{VK_SDK_PATH})
    message(FATAL_ERROR "VK_SDK_PATH not defined!")
endif()
set(VK_SDK_PATH $ENV{VK_SDK_PATH})
set(VK_SDK_INCLUDE ${VK_SDK_PATH}/Include)
set(VK_SDK_LIB ${VK_SDK_PATH}/Lib/vulkan-1.lib)

# imgui 和 eigen 引入包
find_package(imgui CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

# 将源代码添加到此项目的可执行文件
file(GLOB_RECURSE HEADER_FILES "include/*.h" "include/*.hpp")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})
add_executable(Kengin main.cpp ${HEADER_FILES} ${SOURCE_FILES})

# 链接到库文件
target_link_libraries(Kengin PRIVATE imgui::imgui)
target_link_libraries(Kengin PRIVATE Eigen3::Eigen)
target_link_libraries(Kengin PRIVATE ${VK_SDK_LIB})

# 添加包含目录
target_include_directories(Kengin PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(Kengin PRIVATE ${VK_SDK_INCLUDE})