// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
// Local Headers
#include "glitter.hpp"
#include "game.h"
#include "resource_manager.h"

// Standard Headers
#include <cstdio>
#include <cstdlib>

// Prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Globals
Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char * argv[]) {

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GLBreakout", nullptr, nullptr);

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    // GLFW Settings
    glfwSetKeyCallback(mWindow, KeyCallback);

    // OpenGL Configuration
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Breakout.Init();

    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    Breakout._state = GAME_ACTIVE;

    // Rendering Loop
    while (!glfwWindowShouldClose(mWindow)) 
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        Breakout.ProcessInput(deltaTime);

        Breakout.Update(deltaTime);

        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }   

    ResourceManager::Clear();
    glfwTerminate();
    return EXIT_SUCCESS;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key >= 0 && key <= 1024)
    {
        if(action == GLFW_PRESS)
            Breakout._keys[key] = GL_TRUE;
        else if(action == GLFW_RELEASE)
            Breakout._keys[key] == GL_FALSE;
    }
}
