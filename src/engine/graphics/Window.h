//
// Created by Timothy Blumberg on 26/02/17.
//

#ifndef TLOTK_WINDOW_H
#define TLOTK_WINDOW_H

#include <iostream>

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>


#define KEYS 256
#define MOUSE 10

class Window
{
    public:
        Window(const int width, const int height, const char* title);
        ~Window();

        bool initialize();
        bool close();

        void clear();
        void update();

        double getGLFWTime();

        static Window* getWindowPointer(GLFWwindow* gWindow);

        void setKey(int key, bool value);
        void setMouse(int button, bool value);

    private:
        int WIDTH;
        int HEIGHT;
        const char* windowTitle;
        GLFWwindow* glfwWindow;

        // Key + mouse arrays
        bool* keys;
        bool* mouse;

        // Callbacks
        static void error_callback(int error, const char* description);
        static void key_callback(GLFWwindow* gwindow, int key, int scancode, int action, int mods);
        static void mouse_button_callback(GLFWwindow* gwindow, int button, int action, int mods);
};


#endif //TLOTK_WINDOW_H
