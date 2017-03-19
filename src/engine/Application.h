//
// Created by Timothy Blumberg on 26/02/17.
//

#ifndef TLOTK_APPLICATION_H
#define TLOTK_APPLICATION_H

#include <iostream>
#include "graphics/Model.h"
#include "graphics/Shader.h"
#include "graphics/Window.h"
#include "graphics/Camera.h"
#include "graphics/Mesh.h"
#include "graphics/AbLayer.h"

#include "state/GameState.h"
#include "state/MousePicker.h"

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
        std::shared_ptr<Window> window;
        std::shared_ptr<Camera> camera;

        std::vector<AbLayer*> layers;
        MousePicker* mPicker;
        GameObject* mouseFollower;
};


#endif //TLOTK_APPLICATION_H
