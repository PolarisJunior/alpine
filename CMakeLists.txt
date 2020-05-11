cmake_minimum_required(VERSION 3.10)

project(Alpine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ALPINE_SOURCE_DIR src)
set(THIRD_PARTY_DIR thirdparty)
set(MODULES_DIR modules)

add_executable(Alpine
               ${ALPINE_SOURCE_DIR}/main/main.cpp
               ${ALPINE_SOURCE_DIR}/math/mat4.cpp
               ${ALPINE_SOURCE_DIR}/math/quaternion.cpp
               ${ALPINE_SOURCE_DIR}/graphics/graphics_client.cpp
               ${ALPINE_SOURCE_DIR}/graphics/material.cpp
               ${ALPINE_SOURCE_DIR}/graphics/shader_program_builder.cpp
               ${ALPINE_SOURCE_DIR}/graphics/shader_program.cpp
               ${ALPINE_SOURCE_DIR}/drivers/drivers.cpp
               ${ALPINE_SOURCE_DIR}/drivers/rasterizer.cpp
               ${ALPINE_SOURCE_DIR}/drivers/peripherals/keyboard.cpp
               ${ALPINE_SOURCE_DIR}/drivers/peripherals/mouse.cpp
               ${ALPINE_SOURCE_DIR}/core/camera.cpp
               ${ALPINE_SOURCE_DIR}/core/event_broadcaster.cpp
               ${ALPINE_SOURCE_DIR}/core/game_loop.cpp
               ${ALPINE_SOURCE_DIR}/core/input.cpp
               ${ALPINE_SOURCE_DIR}/core/loop_registry.cpp
               ${ALPINE_SOURCE_DIR}/core/primitive.cpp
               ${ALPINE_SOURCE_DIR}/core/program.cpp
               ${ALPINE_SOURCE_DIR}/core/resource.cpp
               ${ALPINE_SOURCE_DIR}/core/sys.cpp
               ${ALPINE_SOURCE_DIR}/core/transform.cpp
               ${ALPINE_SOURCE_DIR}/core/world/skybox.cpp
               ${ALPINE_SOURCE_DIR}/core/meshes/mesh.cpp
               ${ALPINE_SOURCE_DIR}/core/io/file.cpp
               ${ALPINE_SOURCE_DIR}/ui/window_builder.cpp
               ${ALPINE_SOURCE_DIR}/ui/window.cpp
               )

target_include_directories(Alpine PUBLIC
                           ${THIRD_PARTY_DIR}/entt/single_include
                           ${THIRD_PARTY_DIR}/glew/include 
                           ${THIRD_PARTY_DIR}/json/include 
                           ${THIRD_PARTY_DIR}/SDL/include
                           ${THIRD_PARTY_DIR}/SDL2_image/include
                           ${THIRD_PARTY_DIR}/glm
                           ${MODULES_DIR}/pjmath/include
                           ./include)

target_link_libraries(Alpine
                      ${CMAKE_SOURCE_DIR}/thirdparty/glew/lib/Release/x64/glew32s.lib
                      ${CMAKE_SOURCE_DIR}/thirdparty/SDL/lib/x64/SDL2.lib
                      ${CMAKE_SOURCE_DIR}/thirdparty/SDL/lib/x64/SDL2main.lib
                      ${CMAKE_SOURCE_DIR}/thirdparty/SDL2_image/lib/x64/SDL2_image.lib
                      OpenGL32)

# Prevent GLEW Link warnings, LNK4286
target_compile_definitions(Alpine PUBLIC 
                           -DGLEW_STATIC)
