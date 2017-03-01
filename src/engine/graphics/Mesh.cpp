//
// Created by Timothy Blumberg on 28/02/17.
//

#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const glm::vec3 &centerOffset)
        : Model(vertices, indices, centerOffset)
{

}

Mesh Mesh::createMesh(const int xSize, const int ySize)
{
    glm::vec3 color = glm::vec3(0.9, 0.1, 0.0);
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    
    glm::vec2 eT = glm::vec2(0, 0);
    glm::vec3 red = glm::vec3(1, 0, 0);

    // Generate mesh of zvalues 
    float* zValues = new float[xSize * ySize];
    for (int x = 0; x < xSize; x++)
    {
        for (int y = 0; y < ySize; y++)
        {  
            zValues[meshVertIndex(x, y, ySize)] = std::rand() % 10;
        }
    }
    
    // Generate mesh
    for (int x = 0; x < xSize; x++)
    {
        for (int y = 0; y < ySize; y++)
        {
            // Each iteration generates a quad of two triangles
            float xPos = x * MESH_SIZE;
            float yPos = y * MESH_SIZE;

            // Generate zPos
            float zPos = std::rand() % 10;

            // Create unique points
            glm::vec3 p1 = glm::vec3(xPos,             yPos,             zValues[meshVertIndex(x, y, ySize)]);
            glm::vec3 p2 = glm::vec3(xPos + MESH_SIZE, yPos,             zValues[meshVertIndex(x+1, y, ySize)]);
            glm::vec3 p3 = glm::vec3(xPos,             yPos + MESH_SIZE, zValues[meshVertIndex(x, y+1, ySize)]);
            glm::vec3 p4 = glm::vec3(xPos + MESH_SIZE, yPos + MESH_SIZE, zValues[meshVertIndex(x+1, y+1, ySize)]);
            
            // Generate normals for both triangles 
            glm::vec3 n1 = calculateNormal(p1, p2, p3);
            glm::vec3 n2 = calculateNormal(p3, p4, p2);
            
            // Create Triangle 1
            vertices.push_back(Vertex(p1, red, eT, n1));
            vertices.push_back(Vertex(p2, red, eT, n1));
            vertices.push_back(Vertex(p3, red, eT, n1));

            // Create Triangle 2
            vertices.push_back(Vertex(p3, red, eT, n2));
            vertices.push_back(Vertex(p4, red, eT, n2));
            vertices.push_back(Vertex(p2, red, eT, n2));
        }
    }

    // Assemble indices (essentially wasted space for this situation)
    for (unsigned int x = 0; x < vertices.size(); x++)
    {
        indices.push_back(x);
    }

    float xCenter = (xSize / 2) * MESH_SIZE;
    float yCenter = (ySize / 2) * MESH_SIZE;
    return Mesh(vertices, indices, glm::vec3(-xCenter,-yCenter, 0));
}

int Mesh::meshVertIndex(int x, int y, int height)
{
    return x + y * height;
}

glm::vec3 Mesh::calculateNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
    /*
     *  PSEUDO-CODE FROM (https://www.khronos.org/opengl/wiki/Calculating_a_Surface_Normal):
     *  Set Vector U to (Triangle.p2 minus Triangle.p1)
     *  Set Vector V to (Triangle.p3 minus Triangle.p1)
     *
     *  Set Normal.x to (multiply U.y by V.z) minus (multiply U.z by V.y)
     *  Set Normal.y to (multiply U.z by V.x) minus (multiply U.x by V.z)
     *  Set Normal.z to (multiply U.x by V.y) minus (multiply U.y by V.x)
     */
    glm::vec3 u = p2 - p1;
    glm::vec3 v = p3 - p1; // maybe this is fine?

    glm::vec3 n;

    n.x = (u.y * v.z) - (u.z * v.y);
    n.y = (u.z * v.x) - (u.x * v.z);
    n.z = (u.x * v.y) - (u.y * v.x);

    return n;
}
