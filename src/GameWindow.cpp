#include <GameWindow.hpp>

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static void ErrorCallback(int error, const char *description)
{
    std::cerr << "GLFW error " << error << ": " << description << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
}

static void KeyCallback()
{

}

GameWindow::GameWindow(int32_t _width, int32_t _height, std::string _title)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    glfwSetErrorCallback(ErrorCallback);

    GLFWwindow* window = glfwCreateWindow(_width, _height, _title.c_str(), 0, 0);
    mHandle = (Handle*)window;
    if(window == 0) std::cout << "Window creation failed!" << std::endl;
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, (void*)this);


    glewExperimental = GL_TRUE;
    glewInit();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

GameWindow::~GameWindow()
{
    GLFWwindow* window = (GLFWwindow*)mHandle;
    glfwDestroyWindow(window);
}

void GameWindow::show()
{
    GLFWwindow* window = (GLFWwindow*)mHandle;
    glfwShowWindow(window);
}
void GameWindow::hide()
{
    GLFWwindow* window = (GLFWwindow*)mHandle;
    glfwHideWindow(window);
}
void GameWindow::update()
{
    glfwPollEvents();
}
void GameWindow::swapBuffers()
{
    GLFWwindow* window = (GLFWwindow*)mHandle;
    glfwSwapBuffers(window);
}
void GameWindow::resize(int32_t _width, int32_t _height)
{
    GLFWwindow* window = (GLFWwindow*)mHandle;
    glfwSetWindowSize(window, _width, _height);
}
void GameWindow::setFullscreen(bool _fullscreen)
{
    GLFWwindow* window = (GLFWwindow*)mHandle;
}
void GameWindow::makeCurrent()
{
    GLFWwindow* window = (GLFWwindow*)mHandle;
    glfwMakeContextCurrent(window);
}
bool GameWindow::getShouldClose()
{
    GLFWwindow* window = (GLFWwindow*)mHandle;
    return (bool)glfwWindowShouldClose(window);
}

void GameWindow::setClearColor(float _r, float _g, float _b)
{
    glClearColor(_r, _g, _b, 1.0);
}
void GameWindow::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}