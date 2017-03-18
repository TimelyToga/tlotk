//
// Created by Timothy Blumberg on 15/03/17.
//

#ifndef TLOTK_SQUARE_H
#define TLOTK_SQUARE_H

#include <glm/vec2.hpp>
#include "Resource.h"

struct Square
{
    // Represents the lower-left-hand corner of the square
    float x;
    float y;

    Resource rtype;

    Square(float x, float y, Resource r)
    {
        this->x = x;
        this->y = y;
        this->rtype = r;
    }

    Square(glm::vec2 pos, Resource r)
    {
        this->x = pos.x;
        this->y = pos.y;
        this->rtype = r;
    }

    static glm::vec3 getColor(Resource r){
        switch(r)
        {
//            case IRON: return glm::vec3(0.42, 0.42, 0.42);
//            case ICE: return glm::vec3(205/255, 221/255, 247/255);
//            case STONE: return glm::vec3(216/255, 216/255, 216/255);

            default: return glm::vec3(1, 1, 1);
        }
    }
};

#endif //TLOTK_SQUARE_H
