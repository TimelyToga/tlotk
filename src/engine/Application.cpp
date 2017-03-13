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

    glm::vec3 red(1, 1, 0);
    bool objectDesign[100] = {0};

    objectDesign[1] = true;
    objectDesign[3] = true;
    objectDesign[4] = true;
    objectDesign[5] = true;
    objectDesign[7] = true;
    Mesh *m = Mesh::createMeshFromArray(objectDesign, 10.0f, 3, 3, 0.0f, 0.0f, red);

    GameObject *go = new GameObject(m);
    mainLayer->addGameObject(go);

#ifdef WIREFRAME
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
#endif
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
