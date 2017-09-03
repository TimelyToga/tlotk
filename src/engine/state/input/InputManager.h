//
// Created by Timothy Blumberg on 27/08/17.
//

#ifndef TLOTK_INPUTMANAGER_H
#define TLOTK_INPUTMANAGER_H


#include "../IUpdatable.h"

class InputManager : public IUpdatable
{
    public:
        InputManager();

        void update() override;


    private:
};


#endif //TLOTK_INPUTMANAGER_H
