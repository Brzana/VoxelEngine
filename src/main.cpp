#include "../include/Engine.h"

int main(int argc, char** argv) {
    Engine engine;

    if (!engine.init()) {
        return -1;
    }

    // Main loop
    while (!engine.shouldClose()) {
        engine.update();

        engine.render();
    }

    engine.shutdown();
    return 0;
}
