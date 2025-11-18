cmake_minimum_required(VERSION 3.20)
project(Game VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Game main.cpp)

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG v5.3.1
)
FetchContent_MakeAvailable(assimp)

file(GLOB IMGUI_SRC
    external/imgui/*.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

add_library(glad STATIC
    external/glad/src/glad.c
)
target_include_directories(glad PUBLIC
    external/glad/include
)

add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC external/imgui external/imgui/backends)
target_link_libraries(imgui PUBLIC glfw glad)

target_sources(${PROJECT_NAME} PRIVATE main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${glfw_SOURCE_DIR}/include ${glm_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw opengl32 assimp imgui glad)

add_subdirectory(Game)