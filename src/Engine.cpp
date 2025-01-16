#include "../include/OpenGl.h"
#include "../include/Engine.h"


Engine::Engine()
    : m_window(nullptr)
    , m_camera(nullptr)
    , m_chunkManager(nullptr)
    , m_renderer(nullptr)
{}

Engine::~Engine() {
    // Clean up in shutdown() instead
}

bool Engine::init() {
    m_window = std::make_unique<Window>();
    if (!m_window->init(1280, 720, "Voxel Engine")) {
        return false;
    }
    m_camera = std::make_unique<Camera>();
    m_chunkManager = std::make_unique<ChunkManager>();
    m_renderer = std::make_unique<Renderer>();
    if (!m_renderer->init()) {
        return false;
    }
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE); // optional if you want to cull back faces

    return true;
}

void Engine::update() {
    // Calculate deltaTime
    float currentTime = (float)glfwGetTime();
    m_deltaTime = currentTime - m_lastFrameTime;
    m_lastFrameTime = currentTime;

    // Process input
    m_window->pollEvents();

    // Update camera, chunk manager, etc.
    m_camera->update(m_deltaTime, *m_window);
    m_chunkManager->update(m_camera->getPosition());
}

void Engine::render() {
    // Clear screen
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render the voxel world
    m_renderer->renderWorld(m_camera.get(), m_chunkManager.get());

    // Swap buffers
    m_window->swapBuffers();
}

void Engine::shutdown() {
    // Clean up in reverse order of creation
    m_renderer->shutdown();
    m_chunkManager.reset();
    m_camera.reset();
    m_window->shutdown();
    m_window.reset();
}

bool Engine::shouldClose() const {
    return m_window->shouldClose();
}
