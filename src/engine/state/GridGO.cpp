//
// Created by Timothy Blumberg on 18/03/17.
//

#include "GridGO.h"

GridGO::GridGO(const float p_squareSize)
    : updateList()
{
    this->squareSize = p_squareSize;

    Model *myModel = new Model({}, {}, glm::vec3(0, 0, 0));
    setModel(myModel);
}

GridGO::~GridGO()
{
    // TODO: Make sure all GridSquares are torn down
}

void GridGO::render()
{
    for(GridSquare* g : squares)
    {
        g->render();
    }
}

void GridGO::update()
{
    while(!updateList.empty())
    {
        GridSquare* curSquare = updateList.back();
        curSquare->update();
        updateList.pop_back();
    }
}

void GridGO::clearSquares()
{
    squares.clear();
}

void GridGO::addSquare(GridSquare* gsquare)
{
    squares.push_back(gsquare);
}

void GridGO::addSquares(std::vector<GridSquare*> gsquares)
{
    for(GridSquare* g : gsquares)
    {
        squares.push_back(g);
    }
}

void GridGO::addToUpdateList(GridSquare* gsquare)
{
    updateList.push_back(gsquare);
}

GridGO* GridGO::createFromArray(const bool *objectDesign, int xDim, int yDim, float sSize, glm::vec3 pos)
{
    GridGO* owner = new GridGO(sSize);

    for(int x = 0; x < xDim; x++)
    {
        for(int y = 0; y < yDim; y++)
        {
            if(objectDesign[x + y * yDim])
            {
                GridSquare* curSquare = new GridSquare(x, y, owner);
                glm::vec3 color(1, 1, 1);
                glm::vec2 curPos(x * sSize, y*sSize);

                int type = std::rand() % 3;

                switch(type)
                {
                    case 0:
                        color = glm::vec3(1, 0, 0);
                        break;
                    case 1:
                        color = glm::vec3(0, 1, 0);
                        break;
                    case 2:
                        color = glm::vec3(0, 0, 1);
                        break;
                    default:
                        color = glm::vec3(1, 1, 1);
                }

                // Create a model
                Model* squareModel = GridSquare::createSquareModel(curPos, pos.z, 10.0f, color);
                curSquare->setModel(squareModel);

                owner->addSquare(curSquare);
            }
        }
    }

    return owner;
}
