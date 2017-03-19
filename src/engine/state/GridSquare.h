//
// Created by Timothy Blumberg on 18/03/17.
//

#ifndef TLOTK_GRIDSQUARE_H
#define TLOTK_GRIDSQUARE_H

#include "GridGO.h"
#include "GameObject.h"
#include "ResourceBundle.h"

class GridGO;

class GridSquare : public GameObject
{
    public:
        GridSquare(int x, int y, GridGO* owner);
        ~GridSquare();

        void update() override;

        static std::vector<Vertex> createSquareVertices(glm::vec2 pos, float z, float size, glm::vec3 mColor);
        static Model* createSquareModel(glm::vec2 pos, float z, float size, glm::vec3 mColor);

    private:
        // Local grid coordinates
        int gX;
        int gY;

        GridGO *owner;

        ResourceBundle rbundle;
};


#endif //TLOTK_GRIDSQUARE_H
