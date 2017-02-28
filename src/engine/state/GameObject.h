//
// Created by Timothy Blumberg on 26/02/17.
//

#ifndef TLOTK_GAMEOBJECT_H
#define TLOTK_GAMEOBJECT_H


#include "IRenderable.h"
#include "IUpdatable.h"

class GameObject : public IUpdatable, public IRenderable
{
    public:
        GameObject();
        ~GameObject();

    private:

};


#endif //TLOTK_GAMEOBJECT_H
