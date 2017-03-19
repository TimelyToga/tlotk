cmake_minimum_required(VERSION 3.6)
project(tlotk)

set(CMAKE_CXX_STANDARD 11)

# Create executable
set(SOURCE_FILES main.cpp src/engine/Application.cpp src/engine/Application.h src/engine/state/GameState.cpp src/engine/state/GameState.h src/engine/graphics/Window.cpp src/engine/graphics/Window.h src/engine/state/IRenderable.h src/engine/state/IUpdatable.h src/engine/state/GameObject.cpp src/engine/state/GameObject.h src/engine/graphics/Model.cpp src/engine/graphics/Model.h src/engine/graphics/Vertex.h src/engine/graphics/Shader.cpp src/engine/graphics/Shader.h src/engine/utils/FileUtils.h src/engine/utils/utils.h src/engine/graphics/Camera.cpp src/engine/graphics/Camera.h src/engine/graphics/Mesh.cpp src/engine/graphics/Mesh.h src/engine/graphics/AbLayer.cpp src/engine/graphics/AbLayer.h src/engine/utils/debug.h src/engine/utils/Spawner.cpp src/engine/utils/Spawner.h src/engine/player/Player.cpp src/engine/player/Player.h src/engine/state/Square.h src/engine/state/Resource.h src/engine/state/GridGO.cpp src/engine/state/GridGO.h src/engine/state/GridSquare.cpp src/engine/state/GridSquare.h src/engine/utils/VectorUtils.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})


# Find GLEW
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
else()
    message(FATAL_ERROR "Couldn't find GLEW. Build Failed.")
endif()


# Find GLFW
find_library(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})


# Find OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})


# Find GLM
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
include_directories(/usr/local/Cellar/glm/0.9.7.1/include/)