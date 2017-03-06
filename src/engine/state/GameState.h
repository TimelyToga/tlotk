//
// Created by Timothy Blumberg on 26/02/17.
//

#ifndef TLOTK_GAMESTATE_H
#define TLOTK_GAMESTATE_H


#include "../graphics/Window.h"

/*
 * Holds all important game state needed during the game
 */
class GameState
{
        std::shared_ptr<Window> window;
        static GameState *instance;
        GameState(std::shared_ptr<Window> _window = nullptr);

    public:
        static GameState* create(std::shared_ptr<Window> _window);
        static GameState* get();

        bool keyPressed(int keyID);
        bool mouseButtonPressed(int mButtonID);
        double getGLFWTime();
};


#endif //TLOTK_GAMESTATE_H
