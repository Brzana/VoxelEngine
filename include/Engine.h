#pragma once

#include <memory>
#include "Window.h"
#include "Camera.h"
#include "ChunkManager.h"
#include "Renderer.h"

class Engine {
public:
    Engine();
    ~Engine();

    bool init();
    void update();
    void render();
    void shutdown();

    bool shouldClose() const;

private:
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<ChunkManager> m_chunkManager;
    std::unique_ptr<Renderer> m_renderer;

    // Timing (deltaTime, etc.)
    float m_deltaTime = 0.0f;
    float m_lastFrameTime = 0.0f;
};
