//
// Created by Timothy Blumberg on 14/03/17.
//

#include "Player.h"
#include "../state/GameState.h"

Player::Player(const float xPos, const float yPos, std::shared_ptr<Window> window)
{
    mWindow = window;

    createModel();
    model->setPosition(xPos, yPos);

    lightPos_h = GameState::get()->getUniform(GameState::LIGHT_POS_H);
    lightColor_h = GameState::get()->getUniform(GameState::LIGHT_COLOR_H);
    lightCutoffAngle_h = GameState::get()->getUniform(GameState::LIGHT_CUTOFF_ANGLE_H);
    lightDirection_h = GameState::get()->getUniform(GameState::LIGHT_DIRECTION_H);
    lightColor = glm::vec3(1, 1, .87);
    lightPos = glm::vec3(0, 0, LIGHT_POS_Z);
}

void Player::update()
{
    float delta = 0.15f;

    if(mWindow->getKey(GLFW_KEY_LEFT))  model->rotate( ROTATION_SPEED);
    if(mWindow->getKey(GLFW_KEY_RIGHT)) model->rotate(-ROTATION_SPEED);
    if(mWindow->getKey(GLFW_KEY_UP)) powerThrusters(true, 1.0f);
    if(mWindow->getKey(GLFW_KEY_DOWN)) powerThrusters(false, 1.0f);

    // Light Pos
    if(mWindow->getKey(GLFW_KEY_O)){
        this->lightPos.z += 1.0f;
        std::cout << "z: " << lightPos.z << std::endl;
    }
    if(mWindow->getKey(GLFW_KEY_I)){
        this->lightPos.z -= 1.0f;
        std::cout << "z: " << lightPos.z << std::endl;
    }

    // Light cutoff angle
    if(mWindow->getKey(GLFW_KEY_Z)){
        this->lightCutoffAngle += 0.01f;
        std::cout << "cangle: " << lightCutoffAngle << std::endl;
    }
    if(mWindow->getKey(GLFW_KEY_X)){
        this->lightCutoffAngle -= 0.01f;
        std::cout << "cangle: " << lightCutoffAngle << std::endl;
    }

    // Physics update 
    // TODO: Abstract away
    acceleration = force * (1 / SHIP_MASS);

    glm::vec2 deltaPos = 0.5f * acceleration * (delta * delta) + velocity * delta; //s(t)= a*t^2 + v*t
    velocity += acceleration * delta;
    model->translatePosition(deltaPos);

    velocity *= SPEED_DECAY;

    // Force has been applied, remove it from future calculations
    force = glm::vec2(0,0);
    acceleration = glm::vec2(0,0);

    model->update();

    // Update light position
    float lX = model->getDirection().x * 25;
    float lY = model->getDirection().y * 25;

    this->lightPos.x = model->getPosition().x + lX;
    this->lightPos.y = model->getPosition().y + lY;
}

void Player::createModel()
{
    std::vector<Vertex> vertices = createPlayerVertices(PLAYER_SIZE);
    std::vector<unsigned int> indices;

    for(unsigned int a = 0; a < vertices.size(); a++)
    {
        indices.push_back(a);
    }

    model = new Model(vertices, indices, glm::vec3(0.0f, 0.0f, 0.0f));
}

std::vector<Vertex> Player::createPlayerVertices(float size)
{
    const float m = size;
    const float h = size * 0.5f;
    const float q = size * 0.25f;
    const float s = size * 0.15f;

    glm::vec3 playerColor   = glm::vec3(0.86f, 0.13f, 0.19f);

    // If anyone sees this--I'm deeply sorry. Don't ever do this

    // Main Body
    const Vertex v1  = Vertex(glm::vec3(-m,          h,        0.0f), playerColor);
    const Vertex v2  = Vertex(glm::vec3(-m,         -h,        0.0f), playerColor);
    const Vertex v3  = Vertex(glm::vec3(0.0f,        h,        0.0f), playerColor);
    const Vertex v4  = Vertex(glm::vec3(0.0f,       -h,        0.0f), playerColor);
    const Vertex v5  = Vertex(glm::vec3(m,         h-q,        0.0f), playerColor);
    const Vertex v6  = Vertex(glm::vec3(m + q,    0.0f,        0.0f), playerColor);
    const Vertex v7  = Vertex(glm::vec3(m,        -h+q,        0.0f), playerColor);
    const Vertex v8  = Vertex(glm::vec3(0.0f,     -h+q,        0.0f), playerColor);
    const Vertex v9  = Vertex(glm::vec3(0.0f,      h-q,        0.0f), playerColor);
    const Vertex v10 = Vertex(glm::vec3(-m,        h-q,        0.0f), playerColor);
    const Vertex v11 = Vertex(glm::vec3(-m,       -h+q,        0.0f), playerColor);
    const Vertex v12 = Vertex(glm::vec3(-m-q,      h-q,        0.0f), playerColor);
    const Vertex v13 = Vertex(glm::vec3(-m-q,     -h+q,        0.0f), playerColor);

    // Left Extension
    const Vertex v14 = Vertex(glm::vec3(-m+s,        h,        0.0f), playerColor);
    const Vertex v15 = Vertex(glm::vec3(-m+s+q,      h,        0.0f), playerColor);
    const Vertex v16 = Vertex(glm::vec3(-m+s,      h+s,        0.0f), playerColor);
    const Vertex v17 = Vertex(glm::vec3(-m+s+q,    h+s,        0.0f), playerColor);

    // Left Rocket
    const Vertex v18 = Vertex(glm::vec3(-m,        h+s,        0.0f), playerColor);
    const Vertex v19 = Vertex(glm::vec3(-m,      h+s+q,        0.0f), playerColor);
    const Vertex v20 = Vertex(glm::vec3(-h,      h+s+q,        0.0f), playerColor);
    const Vertex v21 = Vertex(glm::vec3(-h,        h+s,        0.0f), playerColor);
    const Vertex v22 = Vertex(glm::vec3(-h+s,  h+s+(q/2),        0.0f), playerColor);

    // Right Extension
    const Vertex v23 = Vertex(glm::vec3(-m+s,        -h,        0.0f), playerColor);
    const Vertex v24 = Vertex(glm::vec3(-m+s+q,      -h,        0.0f), playerColor);
    const Vertex v25 = Vertex(glm::vec3(-m+s,      -h-s,        0.0f), playerColor);
    const Vertex v26 = Vertex(glm::vec3(-m+s+q,    -h-s,        0.0f), playerColor);

    // Right Rocket
    const Vertex v27 = Vertex(glm::vec3(-m,        -h-s,        0.0f), playerColor);
    const Vertex v28 = Vertex(glm::vec3(-m,      -h-s-q,        0.0f), playerColor);
    const Vertex v29 = Vertex(glm::vec3(-h,      -h-s,        0.0f), playerColor);
    const Vertex v30 = Vertex(glm::vec3(-h,      -h-s-q,        0.0f), playerColor);
    const Vertex v31 = Vertex(glm::vec3(-h+s,  -h-s-(q/2),        0.0f), playerColor);


    // Main Body
    return {v1, v2, v3, // A
            v2, v3, v4, // B
            v3, v5, v9, // C
            v5, v6, v7, // D
            v8, v7, v4, // E
            v9, v5, v7, // F
            v9, v7, v8, // G
            v12, v1, v10, // H
            v12, v10, v13, // I
            v13, v10, v11, // J

            // Left Extension
            v13, v11, v2, // K
            v14, v17, v15, // L
            v14, v16, v17, // M

            // Left Rocket
            v18, v20, v21, // N
            v19, v20, v18, // O
            v20, v22, v21, // P

            // Right Extension
            v23, v24, v25, // Q
            v25, v24, v26, // R

            // Right Rocket
            v27, v29, v28, //
            v28, v29, v30, //
            v29, v31, v30, //

    };
}

void Player::powerThrusters(bool forward, float power)
{
    float magnitude = forward ? FORWARD_COEF : BACKWARD_COEF;
    glm::vec2 thrustVector = model->getDirection();
    thrustVector *= THRUSTER_POWER * magnitude * power;

    force += thrustVector;
}

void Player::engageLaser(bool engaged)
{
    laserEngaged = engaged;
}

Model *Player::getModel()
{
    return model;
}

void Player::setUniforms(GLint m_h)
{
    // Model matrix
    GameObject::setUniforms(m_h);

    // Light
    glUniform3f(lightPos_h, lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(lightColor_h, lightColor.r, lightColor.g, lightColor.b);
    glUniform3f(lightDirection_h, model->getDirection().x, model->getDirection().y, lightZAngle);
    glUniform1f(lightCutoffAngle_h, lightCutoffAngle);
}
