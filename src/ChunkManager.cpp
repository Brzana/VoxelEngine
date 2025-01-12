#include "../include/ChunkManager.h"

ChunkManager::ChunkManager() {}

ChunkManager::~ChunkManager() {}

void ChunkManager::update(const glm::vec3& cameraPos) {
    // Determine which chunk the camera is in
    int currentChunkX = (int)floor(cameraPos.x / CHUNK_SIZE);
    int currentChunkZ = (int)floor(cameraPos.z / CHUNK_SIZE);

    // Load chunks around camera
    for (int z = currentChunkZ - m_loadDistance; z <= currentChunkZ + m_loadDistance; ++z) {
        for (int x = currentChunkX - m_loadDistance; x <= currentChunkX + m_loadDistance; ++x) {
            if (!getChunk(x, z)) {
                loadChunk(x, z);
            }
        }
    }

    // Optionally, unload chunks that are far away
    // (Implementation depends on your strategy)
}

Chunk* ChunkManager::getChunk(int x, int z) {
    auto it = m_chunks.find({ x, z });
    if (it != m_chunks.end()) {
        return it->second.get();
    }
    return nullptr;
}

void ChunkManager::loadChunk(int x, int z) {
    auto chunk = std::make_unique<Chunk>(x, z);
    chunk->generate();
    m_chunks[{x, z}] = std::move(chunk);
}

void ChunkManager::unloadChunk(int x, int z) {
    // If needed, remove from the map
    m_chunks.erase({ x, z });
}
