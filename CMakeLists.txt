cmake_minimum_required(VERSION 3.0)
project(plankton C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES src/main.cpp src/GLErrorManager.cpp src/Shader.cpp src/core.cpp src/Window.cpp src/Log.cpp)
set(HEADERS src/GLErrorManager.h src/Shader.h src/plankton.h src/Window.h src/Log.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
# target_compile_definitions(${PROJECT_NAME} PUBLIC DEBUG)

# glad
add_library(glad STATIC vendor/glad-gl4.3/src/glad.c)
target_include_directories(glad PRIVATE vendor/glad-gl4.3/include)
target_link_libraries(${PROJECT_NAME} glad)

# glfw
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" force)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" force)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" force)
add_subdirectory(vendor/glfw)

target_link_libraries(${PROJECT_NAME} glfw)
if (UNIX)
	target_link_libraries(${PROJECT_NAME} GL pthread)
endif (UNIX)

target_include_directories(${PROJECT_NAME} PRIVATE src vendor/glad-gl4.3/include vendor/glfw/include vendor/stb vendor/glm vendor/spdlog)

# Macro for absolute path to assets folder
# NOTE: use relative path for release
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
