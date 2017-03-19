//
// Created by Timothy Blumberg on 18/03/17.
//

#include "GridSquare.h"

GridSquare::GridSquare(int x, int y, GridGO* owner)
{
    this->gX = x;
    this->gY = y;

    this->owner = owner;
    owner->addSquare(this);
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

Model* GridSquare::createSquareModel(glm::vec2 pos, float z, float size, glm::vec3 mColor)
{
    std::vector<Vertex> vertices = createSquareVertices(pos, z, size, mColor);
    std::vector<unsigned int> indices = utils::createIndiceArray(vertices);

    return new Model(vertices, indices, glm::vec3(0, 0, 0));
}

std::vector<Vertex> GridSquare::createSquareVertices(glm::vec2 pos, float z, float size, glm::vec3 mColor)
{
    float xPos = pos.x;
    float yPos = pos.y;

    std::vector<Vertex> vertices;
    glm::vec2 eT;
    
    // Create unique points
    glm::vec3 p1 = glm::vec3(xPos,             yPos,             z);
    glm::vec3 p2 = glm::vec3(xPos + size, yPos,             z);
    glm::vec3 p3 = glm::vec3(xPos,             yPos + size, z);
    glm::vec3 p4 = glm::vec3(xPos + size, yPos + size, z);

    // Generate normals for both triangles 
    glm::vec3 n1 = utils::calculateNormal(p1, p2, p3);
    glm::vec3 n2 = utils::calculateNormal(p3, p2, p4);

    // Create Triangle 1
    vertices.push_back(Vertex(p1, mColor, eT, n1));
    vertices.push_back(Vertex(p2, mColor, eT, n1));
    vertices.push_back(Vertex(p3, mColor, eT, n1));

    // Create Triangle 2
    vertices.push_back(Vertex(p3, mColor, eT, n2));
    vertices.push_back(Vertex(p2, mColor, eT, n2));
    vertices.push_back(Vertex(p4, mColor, eT, n2));

    return vertices;
}

