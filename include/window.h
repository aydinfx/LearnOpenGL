#pragma once

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include <string>
#include <cstdio>
#include <cstdlib>

class Window
{
private:
    /// @brief Default width of the window
    static constexpr int DEFAULT_WIDTH = 800;

    /// @brief Default height of the window
    static constexpr int DEFAULT_HEIGHT = 600;

    /// @brief Default name of the window
    static constexpr const char *DEFAULT_NAME = "LearnOpenGL";

    /// @brief Pointer to the GLFW window
    GLFWwindow *m_handle{};

    /// @brief Width of the window in pixels
    int m_width{};

    /// @brief Height of the window in pixels
    int m_height{};

    /// @brief Title displayed in the window's title bar
    std::string m_name{};

    /// @brief Initializes the GLFW library
    void init_glfw()
    {
        if (!glfwInit())
        {
            fprintf(stderr, "Failed to initialize GLFW\n");
            std::exit(EXIT_FAILURE);
        }
    }

    /// @brief Load OpenGL functions
    void init_glad()
    {
        if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
        {
            fprintf(stderr, "Failed to load OpenGL functions\n");
            std::exit(EXIT_FAILURE);
        }
    }

    /// @brief Configures the properties of the OpenGL context and window
    void set_window_hints()
    {
        // Request OpenGL version 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        // Use the modern OpenGL core profile
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Required for OpenGL on macOS
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
    }

    /// @brief Creates the GLFW window and makes its OpenGL context current
    void create_glfw_window()
    {
        set_window_hints();

        m_handle = glfwCreateWindow(m_width, m_height, m_name.c_str(), nullptr, nullptr);
        if (!m_handle)
        {
            fprintf(stderr, "Failed to create GLFW window\n");
            glfwTerminate();
            std::exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(m_handle);
        glfwSetWindowUserPointer(m_handle, this);
    }

    /// @brief  Updates the window dimensions and OpenGL viewport when the framebuffer is resized.
    /// @param window The GLFW window whose framebuffer was resized.
    /// @param width The new framebuffer width.
    /// @param height The new framebuffer height.
    static void framebufferSizeCallback(GLFWwindow *window, int width, int height)
    {
        Window *self =
            static_cast<Window *>(glfwGetWindowUserPointer(window));

        self->m_width = width;
        self->m_height = height;

        glViewport(0, 0, width, height);
    }

public:
    /// @brief Creates a window with the specified dimensions and title
    /// @param width Width of the window in pixels
    /// @param height Height of the window in pixels
    /// @param name Title displayed in the window's title bar
    Window(int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, const std::string &name = DEFAULT_NAME)
        : m_width{width}, m_height{height}, m_name{name}
    {
        // Initialize GLFW and create the OpenGL context.
        init_glfw();
        create_glfw_window();

        // Load OpenGL functions using GLAD.
        init_glad();

        // Get the actual framebuffer dimensions, which may differ from
        // the window dimensions on high-DPI displays.
        int framebufferWidth;
        int framebufferHeight;

        glfwGetFramebufferSize(m_handle, &framebufferWidth, &framebufferHeight);
        m_width = framebufferWidth;
        m_height = framebufferHeight;

        // Set the initial OpenGL viewport to match the framebuffer size.
        glViewport(0, 0, m_width, m_height);

        // Update the viewport and framebuffer dimensions when the window is resized.
        glfwSetFramebufferSizeCallback(m_handle, framebufferSizeCallback);
    }

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    /// @brief Destroys the GLFW window and terminates the GLFW library
    ~Window()
    {
        glfwDestroyWindow(m_handle);
        glfwTerminate();
    }

    /// @brief Returns the width of the window
    /// @return Window width in pixels
    int width() const
    {
        return m_width;
    }

    /// @brief Returns the height of the window
    /// @return Window height in pixels
    int height() const
    {
        return m_height;
    }

    /// @brief Checks whether the window has been requested to close
    /// @return true if the window should close, otherwise false
    bool shouldClose() const
    {
        return glfwWindowShouldClose(m_handle);
    }

    void clearColor(float r = 0.2f, float g = 0.2f, float b = 0.2f)
    {
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    /// @brief Processes pending GLFW events such as keyboard and mouse input
    void pollEvents() const
    {
        glfwPollEvents();
    }

    /// @brief Swaps the front and back buffers of the window
    void swapBuffers() const
    {
        glfwSwapBuffers(m_handle);
    }

    /// @brief Returns the handle to window
    GLFWwindow *getHandle() const
    {
        return m_handle;
    }
};
