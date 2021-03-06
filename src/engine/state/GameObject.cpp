//
// Created by Timothy Blumberg on 26/02/17.
//

#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(Model *m)
{
    setModel(m);
}

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
    if(model) model->update();

    // TODO: Update GameObject itself (Physics, game logic, etc)
}

glm::vec3 GameObject::getPosition()
{
    if(model != nullptr){
        return model->getPosition();
    } else {
        // TODO: Do something more obvious?
        return glm::vec3();
    }
}

void GameObject::setPosition(glm::vec3 position)
{
    if(model != nullptr)
    {
        model->setPosition(position.x, position.y);
    }
}
