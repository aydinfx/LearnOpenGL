cmake_minimum_required(VERSION 3.20)

project(
    LearnOpenGL
    VERSION 1.0.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(EXT_DIR "${CMAKE_SOURCE_DIR}/external")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_SOURCE_DIR}/include")

if(MSVC)

    add_compile_options(
        /W4
        /permissive-
    )

else()

    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
    )

endif()

# GLFW
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${EXT_DIR}/glfw)

# GLM
add_subdirectory(${EXT_DIR}/glm)

# GLAD
add_library(glad
    ${EXT_DIR}/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    ${EXT_DIR}/glad/include
)

# Application
add_executable(${PROJECT_NAME}
    ${SRC_DIR}/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${INC_DIR} ${EXT_DIR}/glm
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
    glfw
    glm::glm
)

# OpenGL

if(WIN32)

    target_link_libraries(${PROJECT_NAME} PRIVATE
        opengl32
    )

elseif(APPLE)

    find_library(OpenGL_LIBRARY OpenGL)

    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${OpenGL_LIBRARY}
    )

else() # Linux

    target_link_libraries(${PROJECT_NAME} PRIVATE
        GL
    )

endif()
