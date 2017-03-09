//
// Created by Timothy Blumberg on 26/02/17.
//

#include "GameObject.h"

void GameObject::render()
{
    model->easyDraw();
}

void GameObject::setUniforms(GLint m_h)
{
    glUniformMatrix4fv(m_h, 1, GL_FALSE, &model->getModelMatrix()[0][0]);
}

void GameObject::setModel(Model *_model)
{
    model = _model;
}

void GameObject::update()
{
    // TODO: Update model (for transformable models)

    // TODO: Update GameObject itself (Physics, game logic, etc)
}
