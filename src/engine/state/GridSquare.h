//
// Created by Timothy Blumberg on 18/03/17.
//

#ifndef TLOTK_GRIDSQUARE_H
#define TLOTK_GRIDSQUARE_H


#include "GameObject.h"
#include "GridGO.h"
#include "ResourceBundle.h"

class GridSquare : public GameObject
{
    public:
        friend class GridGO;
        void update() override;

    private:
        // Local grid coordinates
        int gX;
        int gY;

        GridGO owner;

        ResourceBundle rbundle;
};


#endif //TLOTK_GRIDSQUARE_H
