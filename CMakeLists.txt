cmake_minimum_required(VERSION 3.8)

project(origins)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Game/game.cpp
    src/Mesh/mesh.cpp
    src/Config/config.cpp
    src/stb_image.cpp
)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm-header-only)

find_package(Stb REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})
