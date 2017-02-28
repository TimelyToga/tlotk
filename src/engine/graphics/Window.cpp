//
// Created by Timothy Blumberg on 26/02/17.
//

#include "Window.h"

Window::Window(const int width, const int height, const char *title)
{
    this->WIDTH = width;
    this->HEIGHT = height;
    this->windowTitle = title;
    this->keys = new bool[KEYS];
    this->mouse = new bool[MOUSE];

    if(!initialize())
    {
        std::cout << "Something went wrong when initializing the window." << std::endl;
        exit(EXIT_FAILURE);
    }
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::initialize()
{
    // Initialize GLFW
    if(!glfwInit())
    {
        glfwTerminate();
    }

    // Setup error callback
    glfwSetErrorCallback(Window::error_callback);


    // Set OpenGL Hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFW Window
    glfwWindow = glfwCreateWindow(WIDTH, HEIGHT, windowTitle, NULL, NULL);
    if(!glfwWindow)
    {
        std::cout << "Failed to create a GLFW Window";
        return false;
    }

    // Set up window pointers
    glfwSetWindowUserPointer(glfwWindow, this);
    glfwMakeContextCurrent(glfwWindow);

    // Set all other callbacks
    glfwSetKeyCallback(glfwWindow, Window::key_callback);
    glfwSetMouseButtonCallback(glfwWindow, Window::mouse_button_callback);
    glfwSetScrollCallback(glfwWindow, Window::mouse_scroll_callback);


//    // Makes sure all extensions will be exposed in GLEW and initialize GLEW.
//    glewExperimental = GL_TRUE;
//    glewInit();

    // Print OpenGL Versions
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n\n" << std::endl;

    // Clear colors
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Mode enabling
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    return true;
}

bool Window::close()
{
    return glfwWindowShouldClose(glfwWindow) == GLFW_TRUE;
}

void Window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update()
{
    glfwPollEvents();
    glfwSwapBuffers(glfwWindow);
}

double Window::getGLFWTime()
{
    return glfwGetTime();
}

Window *Window::getWindowPointer(GLFWwindow *gWindow)
{
    return (Window*) glfwGetWindowUserPointer(gWindow);
}

void Window::setKey(int key, bool value)
{
    keys[key] = value;
}

void Window::setMouse(int button, bool value)
{
    mouse[button] = value;
}

void Window::setCamera(std::shared_ptr<Camera> camera)
{
    this->m_Camera = camera;
}

std::shared_ptr<Camera> Window::getCamera()
{
    return m_Camera;
}


// Callbacks
void Window::error_callback(int error, const char *description)
{
    std::cout << "GLFW ERROR (" << error << "): " << description << std::endl;
}

void Window::key_callback(GLFWwindow *gwindow, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(gwindow, GLFW_TRUE);
    }

    // Store the key
    Window* window = Window::getWindowPointer(gwindow);
    window->setKey(key, action != GLFW_RELEASE);
}

void Window::mouse_button_callback(GLFWwindow *gwindow, int button, int action, int mods)
{
    // Store the button
    Window* window = Window::getWindowPointer(gwindow);
    window->setMouse(button, action != GLFW_RELEASE);
}

void Window::mouse_scroll_callback(GLFWwindow *window, double xOffset, double yOffset)
{
    Window *u_Window = (Window *) glfwGetWindowUserPointer(window);

    u_Window->getCamera()->handleMouseScroll((float) yOffset);

    #ifdef PRINT_INPUT
        std::cout << "Mouse Scroll Offsets: (" << xOffset << ", " << yOffset << std::endl;
    #endif
}
