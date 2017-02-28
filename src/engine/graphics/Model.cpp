//
// Created by Timothy Blumberg on 26/02/17.
//

#include "Model.h"
#include "Shader.h"

Model::Model(std::vector<Vertex> vertices, std::vector<unsigned int> indices, glm::vec3 centerOffset)
{
    mVertices = vertices;
    numVertices = vertices.size();
    numElements = indices.size();

    // Generate + Bind the vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);


    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVertices, &vertices[0], GL_STATIC_DRAW);

//
//    // Bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numElements, &indices[0], GL_STATIC_DRAW);


    // Set up vertex attributes
    glEnableVertexAttribArray(Shader::POSITION_ATTR_INDEX);
    glVertexAttribPointer(Shader::POSITION_ATTR_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, v));

    glEnableVertexAttribArray(Shader::COLOR_ATTR_INDEX);
    glVertexAttribPointer(Shader::COLOR_ATTR_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, c));

    glEnableVertexAttribArray(Shader::TEXTURE_ATTR_INDEX);
    glVertexAttribPointer(Shader::TEXTURE_ATTR_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, t));

    glEnableVertexAttribArray(Shader::NORMAL_ATTR_INDEX);
    glVertexAttribPointer(Shader::NORMAL_ATTR_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, n));


    // Unbind this vao
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(0);
}

Model::~Model()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Model::easyDraw()
{
    bind();
    draw();
    unbind();
}

void Model::bind()
{
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void Model::draw()
{
    glDrawElements(GL_TRIANGLES, (int) numElements, GL_UNSIGNED_INT, 0);
}

void Model::unbind()
{
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
