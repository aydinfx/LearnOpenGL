#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "window.h"

int main()
{
    Window window;

    while (!window.shouldClose())
    {
        window.pollEvents();
        window.swapBuffers();
    }

    return 0;
}
