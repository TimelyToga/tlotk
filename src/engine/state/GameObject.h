//
// Created by Timothy Blumberg on 26/02/17.
//

#ifndef TLOTK_GAMEOBJECT_H
#define TLOTK_GAMEOBJECT_H


#include "IRenderable.h"
#include "IUpdatable.h"
#include "../graphics/Model.h"

class GameObject : public IUpdatable, public Model
{
    public:
        GameObject();
        ~GameObject();

        void render() override;

    private:

};


#endif //TLOTK_GAMEOBJECT_H
