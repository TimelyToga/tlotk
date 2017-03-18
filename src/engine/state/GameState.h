//
// Created by Timothy Blumberg on 26/02/17.
//

#ifndef TLOTK_GAMESTATE_H
#define TLOTK_GAMESTATE_H


#include <unordered_map>
#include "../graphics/Window.h"
#include "../player/Player.h"

/*
 * Holds all important game state needed during the game
 */
class GameState
{
    public:
        static constexpr auto LIGHT_POS_H = "lightPos";
        static constexpr auto LIGHT_COLOR_H = "lightColor";

    private:
        std::shared_ptr<Window> window;
        static GameState *instance;
        GameState(std::shared_ptr<Window> _window = nullptr);
        GLint lightPos;

        std::unordered_map<std::string, GLint> uniforms;


    public:
        static GameState* create(std::shared_ptr<Window> _window);
        static GameState* get();

        bool keyPressed(int keyID);
        bool mouseButtonPressed(int mButtonID);
        double getGLFWTime();

        void setUniform(std::string name, GLint handle);
        GLint getUniform(std::string name);
};


#endif //TLOTK_GAMESTATE_H
