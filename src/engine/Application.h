//
// Created by Timothy Blumberg on 26/02/17.
//

#ifndef TLOTK_APPLICATION_H
#define TLOTK_APPLICATION_H

#include <iostream>
#include "graphics/Model.h"
#include "graphics/Shader.h"
#include "state/GameState.h"
#include "graphics/Window.h"
#include "graphics/Camera.h"

#define WIDTH 800
#define HEIGHT 600

class Application
{
    public:
        Application();
        ~Application();

        void initialize();
        void runMainGameLoop();
        void terminate();

    private:
        GameState* gameState;
        Window* window;
        std::shared_ptr<Camera> camera;
};


#endif //TLOTK_APPLICATION_H
