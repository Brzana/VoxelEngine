#include "../include/OpenGl.h"
#include "../include/Renderer.h"


Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

bool Renderer::init()
{
    // Load your shader files
    // Make sure these paths match your real folder structure
    if (!m_shader.load("assets/shaders/voxel.vert", "assets/shaders/voxel.frag")) {
        std::cerr << "Failed to load voxel shaders." << std::endl;
        return false;
    }

    // (Optional) Set up your VAOs/VBOs here, or in a separate function
    // ...

    return true;
}

void Renderer::renderWorld(Camera* camera, ChunkManager* chunkManager)
{
    // Use your shader program
    m_shader.use();

    // Set up matrices
    float aspectRatio = 1280.0f / 720.0f; // replace with actual window size
    glm::mat4 proj = camera->getProjectionMatrix(aspectRatio);
    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 model = glm::mat4(1.0f); // identity, or transform to chunk position

    // Send uniforms to the shader
    m_shader.setUniform("uProj", proj);
    m_shader.setUniform("uView", view);
    m_shader.setUniform("uModel", model);

    // If using a texture, ensure you bind it:
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, yourTextureID);
    // m_shader.setUniform("uTexture", 0);

    // Draw your chunks
    // ...
    // glBindVertexArray(chunkVAO);
    // glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

    // Unbind
    glBindVertexArray(0);
    m_shader.unuse();
}

void Renderer::shutdown()
{
    // Cleanup any buffers/objects if needed
}