//
// Created by Timothy Blumberg on 28/02/17.
//

#include "Mesh.h"
#include "../state/GameState.h"

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const glm::vec3 &centerOffset,
           const std::vector<Square> squares)
        : Model(vertices, indices, centerOffset)
{
    this->squares = squares;
}

void Mesh::update()
{
//    // Rotate model if r
//    if(GameState::get()->keyPressed(GLFW_KEY_RIGHT))
//    {
//        rotate(0.03f);
//    } else if(GameState::get()->keyPressed(GLFW_KEY_LEFT))
//    {
//        rotate(-0.03f);
//    }
}

Mesh* Mesh::createMesh(const int xSize, const int ySize)
{
    glm::vec3 color = glm::vec3(0.9, 0.1, 0.0);
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Square> squares;
    
    glm::vec2 eT = glm::vec2(0, 0);
    glm::vec3 red = glm::vec3(1, 0, 0);

    float sX = 1;
    float sY = 1;

    // Generate mesh of zvalues 
    float* zValues = new float[xSize * ySize];
    for (int x = 0; x < xSize; x++)
    {
        for (int y = 0; y < ySize; y++)
        {  
            zValues[meshVertIndex(x, y, ySize)] = std::rand() % 20;
        }
    }
    
    // Generate mesh
    for (int x = 0; x < xSize - 1; x++)
    {
        for (int y = 0; y < ySize - 1; y++)
        {
            // Each iteration generates a quad of two triangles
            float xPos = x * MESH_SIZE + sX;
            float yPos = y * MESH_SIZE + sY;

            // Generate zPos
            float zPos = std::rand() % 10;

            // Generate resource
            Resource r = generateResource();
            glm::vec3 mColor = Square::getColor(r);

            // Create unique points
            glm::vec3 p1 = glm::vec3(xPos,             yPos,             zValues[meshVertIndex(x, y, ySize)]);
            glm::vec3 p2 = glm::vec3(xPos + MESH_SIZE, yPos,             zValues[meshVertIndex(x+1, y, ySize)]);
            glm::vec3 p3 = glm::vec3(xPos,             yPos + MESH_SIZE, zValues[meshVertIndex(x, y+1, ySize)]);
            glm::vec3 p4 = glm::vec3(xPos + MESH_SIZE, yPos + MESH_SIZE, zValues[meshVertIndex(x+1, y+1, ySize)]);
            
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
        }
    }

    // Assemble indices (essentially wasted space for this situation)
    for (unsigned int x = 0; x < vertices.size(); x++)
    {
        indices.push_back(x);
    }

    float xCenter = (xSize / 2) * MESH_SIZE;
    float yCenter = (ySize / 2) * MESH_SIZE;
    return new Mesh(vertices, indices, glm::vec3(-xCenter,-yCenter, 0), squares);
}

Mesh *Mesh::createMeshFromArray(const bool *objectDesign, const float squareSize,
                                int gridX, int gridY, float xPos, float yPos, glm::vec3 color)
{
    std::vector<Vertex>* vertices = new std::vector<Vertex>();
    std::vector<unsigned int> indices;
    std::vector<Square> squares;

    int numSquares = 0;
    for(int x = 0; x < gridX; x++)
    {
        for(int y = 0; y < gridY; y++)
        {
            bool curSquare = objectDesign[meshVertIndex(x, y, gridY)];

            if(curSquare)
            {
                // Construct a square
                // Define UL corner of square.
                float curX = squareSize * x;
                float curY = squareSize * y;

                createSquare(curX, curY, 0.0f, color, vertices);

                numSquares++;
            }
        }
    }

    // Assemble indices (essentially wasted space for this situation)
    for (unsigned int x = 0; x < vertices->size(); x++)
    {
        indices.push_back(x);
    }

    glm::vec3 position(xPos, yPos, 0);
    glm::vec3 center((((float) -gridX) / 2) * squareSize, ((float) -gridY / 2) * squareSize, 0);

    return new Mesh(*vertices, indices, center, squares);
}

int Mesh::meshVertIndex(int x, int y, int height)
{
    return x + y * height;
}

void Mesh::createSquare(float xPos, float yPos, float zPos, glm::vec3 color, std::vector<Vertex> *vertices)
{
    // Fake texture coordinates
    glm::vec2 eT = glm::vec2(0, 0);

    // Create unique points
    glm::vec3 p1 = glm::vec3(xPos,             yPos,             zPos);
    glm::vec3 p2 = glm::vec3(xPos + MESH_SIZE, yPos,             zPos);
    glm::vec3 p3 = glm::vec3(xPos,             yPos + MESH_SIZE, zPos);
    glm::vec3 p4 = glm::vec3(xPos + MESH_SIZE, yPos + MESH_SIZE, zPos);
    
    // Generate normals for both triangles 
    glm::vec3 n1 = utils::calculateNormal(p1, p2, p3);
    glm::vec3 n2 = utils::calculateNormal(p3, p2, p4);
    
    // Create Triangle 1
    vertices->push_back(Vertex(p1, color, eT, n1));
    vertices->push_back(Vertex(p2, color, eT, n1));
    vertices->push_back(Vertex(p3, color, eT, n1));
    
    // Create Triangle 2
    vertices->push_back(Vertex(p3, color, eT, n2));
    vertices->push_back(Vertex(p2, color, eT, n2));
    vertices->push_back(Vertex(p4, color, eT, n2));
}

Resource Mesh::generateResource()
{
    switch(std::rand() % 5)
    {
        case 0: return IRON;
        case 1: return ICE;

        default: return STONE;
    }
}
