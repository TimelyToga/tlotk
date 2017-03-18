//
// Created by Timothy Blumberg on 18/03/17.
//

#ifndef TLOTK_GRIDGO_H
#define TLOTK_GRIDGO_H


#include <queue>
#include "GameObject.h"
#include "GridSquare.h"

/*
 * GridGOs is the base class for any Objects that are aligned on Grids. This
 * includes asteroids and any ships that would be built.
 *
 * IMPORTANT: GridGO should never have a model associated with it.
 */
class GridGO : public GameObject
{
    public:
        GridGO(const float p_squareSize);
        ~GridGO();

        void addSquare(GridSquare gsquare);
        void addSquares(std::vector<GridSquare> gsquares);
        void clearSquares();
        GridSquare squareClosestTo(float x, float y);

        void update() override;

    private:

        glm::vec3 position;


        std::vector<GridSquare> squares;
        std::deque<GridSquare> updateList;

        float squareSize;

        void addToUpdateList(GridSquare gsquare);


};


#endif //TLOTK_GRIDGO_H
