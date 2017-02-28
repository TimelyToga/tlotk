#include <iostream>
#include "src/engine/Application.h"

int main()
{
    Application app;

    app.initialize();
    app.runMainGameLoop();
    app.terminate();

    return 0;
}