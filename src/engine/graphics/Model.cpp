//
// Created by Timothy Blumberg on 26/02/17.
//

#include "Model.h"

Model::Model(std::vector<Vertex> vertices, std::vector<unsigned int> indices, glm::vec3 centerOffset)
{
    this->mVertices = vertices;
    this->numVertices = vertices.size();
    this->numElements = indices.size();
    this->centerOffset = centerOffset;


    // Generate + Bind the vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    // Initialize VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVertices, &vertices[0], GL_STATIC_DRAW);

    // Initialize EBO
    glGenBuffers(1, &ebo);
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

    regenModelMatrix();
}

Model::~Model()
{
    glDeleteBuffers(1, &ebo);
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

glm::vec2 Model::getDirection()
{
    return direction;
}

glm::mat4 &Model::getModelMatrix()
{
    return modelMatrix;
}

glm::vec3 Model::getPosition()
{
    return position;
}

void Model::regenModelMatrix()
{
    glm::mat4 id = glm::mat4(1.0f);

    // Composite matrix of Translation + Rotation
    modelMatrix = translationMatrix * rotationMatrix * glm::translate(id, centerOffset);
}

void Model::regenRotationMatrix()
{
    glm::mat4 id(1.0f);
    rotationMatrix = glm::rotate(id, rotation, glm::vec3(0.0f, 0.0f, 1.0f)); // Around positive z

    regenModelMatrix();
}

void Model::regenTranslationMatrix()
{
    glm::vec3 center = position;
    translationMatrix = glm::translate(glm::mat4(1.0f), center);
    regenModelMatrix();
}

void Model::setPosition(float p_x, float p_y)
{
    this->position.x = p_x;
    this->position.y = p_y;

    regenModelMatrix();
}

void Model::translatePosition(float xDelta, float yDelta)
{
    this->position.x += xDelta;
    this->position.y += yDelta;
}

void Model::translatePosition(glm::vec2 delta)
{
    this->position.x += delta.x;
    this->position.y += delta.y;
}

void Model::setZCoord(float p_z)
{
    this->position.z = p_z;
}

void Model::setDirection(glm::vec2 directionVec)
{
    this->direction = directionVec;
}

void Model::setRotation(float newAngle)
{
    rotation = newAngle;
    auto newX = cos(rotation);
    auto newY = sin(rotation);

    direction = glm::vec2(newX, newY);
    regenRotationMatrix();
}

void Model::initializeRotation(float initialAngle)
{
    rotation = initialAngle;
}

void Model::rotate(float angleDelta)
{
    rotation += angleDelta;

    auto newX = cos(rotation);
    auto newY = sin(rotation);

    direction = glm::vec2(newX, newY);
    regenRotationMatrix();
}

void Model::update()
{
    regenTranslationMatrix();
    regenRotationMatrix();
}
