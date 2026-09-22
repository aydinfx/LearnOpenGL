#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include <iostream>

int glfwWindowWidth = 1200;
int glfwWindowHeight = 800;

void glfwKeyCallback(GLFWwindow *window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods)
{
    if (key = GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void glfwFramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    // update width and height
    glfwWindowWidth = width;
    glfwWindowHeight = height;

    // update OpenGL viewport
    glViewport(0, 0, width, height);
}

int main()
{

    // Initialize glfw
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize glfw\n";
        return 1;
    }

    // Set window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow *window = glfwCreateWindow(glfwWindowWidth, glfwWindowHeight, "LearnOpenGL", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create glfw window\n";
        glfwTerminate();
        return 1;
    }

    // Set current context
    glfwMakeContextCurrent(window);

    // Load OpenGL functions
    if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
    {
        std::cerr << "Glad failed to load OpenGL functions\n";
        glfwTerminate();
        return 1;
    }

    // Set swap interval
    glfwSwapInterval(1);

    glViewport(0, 0, glfwWindowWidth, glfwWindowHeight);

    // Set callbacks
    glfwSetFramebufferSizeCallback(window, glfwFramebufferSizeCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glfwTerminate();

    return 0;
}
