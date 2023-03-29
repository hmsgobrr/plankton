cmake_minimum_required(VERSION 3.0)
project(plankton C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE "src/*.cpp" "src/*.h")
file(GLOB ASSETS
	"assets/shaders/*.vert"
	"assets/shaders/*.frag"
)

add_library(${PROJECT_NAME} ${SOURCE} ${ASSETS})
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

target_include_directories(${PROJECT_NAME} PRIVATE include vendor/glad-gl4.3/include vendor/glfw/include vendor/stb vendor/glm vendor/spdlog)

# Macro for absolute path to shaders folder
# NOTE: use relative path for release
target_compile_definitions(${PROJECT_NAME} PUBLIC SHADERS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/shaders/")
