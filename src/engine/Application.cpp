//
// Created by Timothy Blumberg on 26/02/17.
//

#include "Application.h"

Application::Application()
    : layers()
{
    window = std::make_shared<Window> (WIDTH, HEIGHT, "The Last of Their Kind");
    camera = std::make_shared<Camera> (WIDTH, HEIGHT, 0.0f, 0.0f, 0.8f);
    gameState = GameState::create(window);

    window->setCamera(camera);
}

Application::~Application()
{

}

void Application::initialize()
{
    std::cout << "Initializing..." << std::endl;

    // Create main layer
    AbLayer *mainLayer = new AbLayer("../src/engine/graphics/shader/simple.vert",
                                     "../src/engine/graphics/shader/simple.frag",
                                     camera);
    layers.push_back(mainLayer);

    Mesh *m = Mesh::createMesh(10, 10);

    float xPos = 5.0f;
    float yPos = 5.0f;
    float zCoord = 10.1f;
    float size = 20.0f;

    const Vertex v1 = Vertex(glm::vec3(xPos,        yPos,        zCoord), glm::vec3(0.8f, 0.3f, 0.2f));
    const Vertex v2 = Vertex(glm::vec3(xPos,        yPos + size, zCoord), glm::vec3(0.55f, 0.0f, 1.0f));
    const Vertex v3 = Vertex(glm::vec3(xPos + size, yPos + size, zCoord), glm::vec3(0.0f, 0.41f, 0.76f));
    const Vertex v4 = Vertex(glm::vec3(xPos + size, yPos,        zCoord), glm::vec3(0.2f, 1.0f, 0.8f));

//    Model *m = new Model({v1, v2, v3, v3, v4, v1}, {1, 2, 3, 2, 3, 4}, glm::vec3(0, 0, 0));

    GameObject *go = new GameObject();
    go->setModel(m);
    mainLayer->addGameObject(go);
}

void Application::runMainGameLoop()
{
    std::cout << "Game Looping..." << std::endl;

    // Global
    while(!window->close())
    {
        window->clear();

        // Update
        camera->update();
        for(AbLayer* aLayer: layers)
        {
            aLayer->update();
        }


        // Render code
        for(AbLayer* aLayer: layers)
        {
            aLayer->bind();
            aLayer->render();
            aLayer->unbind();
        }

        // Swap buffers
        window->update();
    }
}

void Application::terminate()
{
    std::cout << "Terminate..." << std::endl;
}
