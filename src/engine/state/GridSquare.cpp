//
// Created by Timothy Blumberg on 18/03/17.
//

#include "GridSquare.h"

GridSquare::GridSquare(int x, int y, GridGO* owner)
{
    this->gX = x;
    this->gY = y;

    this->owner = owner;
    owner->addSquare(*this);
}

GridSquare::~GridSquare()
{
    // do nothing
}

void GridSquare::update()
{
    // Most likely just calls model->update()
    GameObject::update();

    // Run simulation
}


