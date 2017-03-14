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

        void setUniforms(GLint m_h);
        void setModel(Model* _model);

    protected:
        Model *model;
};


#endif //TLOTK_GAMEOBJECT_H
