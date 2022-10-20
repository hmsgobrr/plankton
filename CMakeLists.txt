cmake_minimum_required(VERSION 3.0)
project(plankton C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} vendor/glad-gl4.3/src/glad.c src/main.cpp src/GLErrorManager.cpp src/Shader.cpp)
# target_compile_definitions(${PROJECT_NAME} PUBLIC DEBUG)

# glfw
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" force)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" force)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" force)
add_subdirectory(vendor/glfw)

target_link_libraries(${PROJECT_NAME} glfw GL pthread)
target_include_directories(${PROJECT_NAME} PRIVATE src vendor/glad-gl4.3/include vendor/glfw/include vendor/stb vendor/glm)
# Macro for absolute path to assets folder
# NOTE: use relative path for release
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
