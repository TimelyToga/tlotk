//
// Created by Timothy Blumberg on 26/02/17.
//

#include "GameState.h"

GameState* GameState::instance = nullptr;

GameState* GameState::create(std::shared_ptr<Window> _window)
{
    instance = new GameState;
    instance->window = _window;
    return instance;
}

GameState* GameState::get()
{
    if(!instance)
    {
        // Throw a fucking fit
        std::cout << "ERROR: Cannot call GameState::get() before GameState::create(). Exiting." << std::endl;
        exit(EXIT_FAILURE);
    }

    return instance;
}

GameState::GameState(std::shared_ptr<Window> _window)
{
    this->window = _window;
}

bool GameState::keyPressed(int keyID)
{
    return window->getKey(keyID);
}

bool GameState::mouseButtonPressed(int mButtonID)
{
    return window->getMouse(mButtonID);
}

double GameState::getGLFWTime()
{
    return window->getGLFWTime();
}

void GameState::setUniform(std::string name, GLint handle)
{
    this->uniforms[name] = handle;
}

GLint GameState::getUniform(std::string name)
{
    return uniforms[name];
}
