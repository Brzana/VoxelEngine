#pragma once

#include "Camera.h"
#include "ChunkManager.h"
#include "ShaderProgram.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init();
    void renderWorld(Camera* camera, ChunkManager* chunkManager);
    void shutdown();

private:
    ShaderProgram m_shader;

    // Example: storing chunk VBOs in a map
    // But you might generate mesh data in chunk itself,
    // or have a separate "Mesh" object, etc.
    // Key = (x, z)
    // Some data structure to store your VAOs, VBOs, etc.
};
