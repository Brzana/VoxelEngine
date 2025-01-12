#pragma once

#include <unordered_map>
#include <memory>
#include "Chunk.h"
#include "../include/OpenGl.h"

// A utility struct to index chunks by (x,z)
struct ChunkCoords {
    int x, z;
    bool operator==(const ChunkCoords& other) const {
        return x == other.x && z == other.z;
    }
};

// A hash function for ChunkCoords
struct ChunkCoordsHash {
    std::size_t operator()(const ChunkCoords& coords) const {
        // Combine x,z into a single hash
        auto h1 = std::hash<int>()(coords.x);
        auto h2 = std::hash<int>()(coords.z);
        // Simple XOR + shift
        return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
    }
};

class ChunkManager {
public:
    ChunkManager();
    ~ChunkManager();

    void update(const glm::vec3& cameraPos);
    Chunk* getChunk(int x, int z);

    // For rendering
    const std::unordered_map<ChunkCoords, std::unique_ptr<Chunk>, ChunkCoordsHash>& getChunks() const {
        return m_chunks;
    }

private:
    // Key: (chunkX, chunkZ)
    std::unordered_map<ChunkCoords, std::unique_ptr<Chunk>, ChunkCoordsHash> m_chunks;

    // Load/unload settings
    int m_loadDistance = 2; // in chunks

    void loadChunk(int x, int z);
    void unloadChunk(int x, int z); // or handle differently
};
