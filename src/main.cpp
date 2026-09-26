#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "window.h"
#include "shader.h"

int main()
{
    Window window;

    float vertices[] =
        {
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f};

    GLuint indices[]{
        0, 1, 2,
        2, 3, 0};

    Shader shader;
    shader.init("shaders/basic.vert", "shaders/basic.frag");

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!window.shouldClose())
    {
        window.clearColor();

        shader.useProgram();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);

        window.pollEvents();
        window.swapBuffers();
    }

    return 0;
}
