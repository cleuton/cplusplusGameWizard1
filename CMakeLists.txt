cmake_minimum_required(VERSION 3.1)
project(projeto2 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

# encontra o OpenGL e o GLFW já instalados no sistema
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

# inclui os headers do GLAD e do GLM
include_directories(
  ${CMAKE_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/glad.c
)

# linka contra as libs do sistema
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    OpenGL::GL
    glfw
)