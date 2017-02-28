//
// Created by Timothy Blumberg on 26/02/17.
//

#include "Application.h"

Application::Application()
{
    gameState = new GameState();
    window = new Window(WIDTH, HEIGHT, "The Last of Their Kind");
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

    GLint mvp_handle = glGetUniformLocation(shader.getShaderProgram(), "MVP");

    glm::mat4 mvp = glm::mat4();
    glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, &mvp[0][0]);

    while(!window->close())
    {
        window->clear();

        // Render code
        shader.bind();
        glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, &mvp[0][0]);
        model->easyDraw();
        shader.unbind();

        window->update();
    }
}

void Application::terminate()
{
    std::cout << "Terminate..." << std::endl;
}
