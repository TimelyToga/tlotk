//
// Created by Timothy Blumberg on 26/02/17.
//

#ifndef TLOTK_GAMEOBJECT_H
#define TLOTK_GAMEOBJECT_H


#include "IRenderable.h"
#include "IUpdatable.h"
#include "../graphics/Model.h"

class GameObject : public IUpdatable, public IRenderable
{
    public:
        GameObject();
        GameObject(Model *m);
//        ~GameObject();

        void render() override;
        void update() override;

        virtual void setUniforms(GLint m_h);
        void setModel(Model* _model);
        glm::vec3 getPosition();
        void setPosition(glm::vec3 position);

    protected:
        Model *model;
};


#endif //TLOTK_GAMEOBJECT_H
