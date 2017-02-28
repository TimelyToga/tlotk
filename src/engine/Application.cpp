//
// Created by Timothy Blumberg on 26/02/17.
//

#include "Application.h"

Application::Application()
{
    gameState = new GameState();
    window = new Window(WIDTH, HEIGHT, "The Last of Their Kind");
    camera = std::make_shared<Camera> (WIDTH, HEIGHT, 0.0f, 0.0f, 0.8f);

    window->setCamera(camera);
}

Application::~Application()
{

}

void Application::initialize()
{
    std::cout << "Initializing..." << std::endl;
}

void Application::runMainGameLoop()
{
    Vertex v1 = Vertex(0.5f,  0.5f, 0.0f, 1, 1, 0);
    Vertex v2 = Vertex(0.5f, -0.5f, 0.0f, 1, 0, 1);
    Vertex v3 = Vertex(-0.5f,-0.5f, 0.0f, 0, 0, 1);
    Vertex v4 = Vertex(-0.5f,  0.5f, 0.0f, 0, 1, 0);

    std::vector<Vertex> vertices = {v1, v2, v3, v4};

    std::vector<unsigned int> indices = {  // Note that we start from 0!
            0, 1, 3,   // First Triangle
            1, 2, 3    // Second Triangle
    };

    Model* model = new Model(vertices, indices, glm::vec3(1, 0, 0));

    Shader shader("../src/engine/graphics/shader/simple.vert", "../src/engine/graphics/shader/simple.frag");

    std::cout << "Game Looping..." << std::endl;

    GLint m_handle = glGetUniformLocation(shader.getShaderProgram(), "M");
    GLint vp_handle = glGetUniformLocation(shader.getShaderProgram(), "VP");

    glm::mat4 vpMatrix = camera->getVPMatrix();
    glm::mat4 mMatrix = model->getModelMatrix();

    while(!window->close())
    {
        window->clear();

        camera->update();
        vpMatrix = camera->getVPMatrix();

        // Render code
        shader.bind();
        glUniformMatrix4fv(m_handle, 1, GL_FALSE, &mMatrix[0][0]);
        glUniformMatrix4fv(vp_handle, 1, GL_FALSE, &vpMatrix[0][0]);
        model->easyDraw();
        shader.unbind();

        window->update();
    }
}

void Application::terminate()
{
    std::cout << "Terminate..." << std::endl;
}
