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

#define WIDTH 1600
#define HEIGHT 800

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
};


#endif //TLOTK_APPLICATION_H
