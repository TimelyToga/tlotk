//
// Created by Timothy Blumberg on 26/02/17.
//

#include "Application.h"
#include "player/Player.h"
#include "state/GridGO.h"

Application::Application()
    : layers()
{
    window = std::make_shared<Window> (WIDTH, HEIGHT, "The Last of Their Kind");
    camera = std::make_shared<Camera> (WIDTH, HEIGHT, 0.0f, 0.0f, 0.8f);
    mPicker = new MousePicker(window, camera);

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

    bool verts[9] = {0};
    verts[1] = true;
    verts[3] = true;
    verts[4] = true;
    verts[5] = true;

//    GridSquare* gg = new GridSquare(0, 0, new GridGO(10.0));
//    gg->setModel(GridSquare::createSquareModel(glm::vec3(0, 0, 0), -10, 10.0f, glm::vec3(1, 0, 0)));

    GridGO* gg = GridGO::createFromArray(verts, 3, 3, 10.0f, glm::vec3(0, 0, 0));

    mainLayer->addGameObject(gg);
    mouseFollower = new GridSquare(0, 0, gg);
    mouseFollower->setModel(GridSquare::createSquareModel(glm::vec3(0), 1, 25.0f, glm::vec3(1, 0, 0)));

    Mesh* m = Mesh::createMesh(10, 10);


    GameObject *go = new GameObject(m);


    Player *player = new Player(0, 0, window);
    camera->setTrackingModel(player->getModel());

    mainLayer->addGameObject(player);
    mainLayer->addGameObject(go);
    mainLayer->addGameObject(mouseFollower);

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
        mPicker->update();
        mouseFollower->setPosition(mPicker->getMouseCoords());

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
