#pragma once

#include <vector>
#include "Voxel.h"

static const int CHUNK_SIZE = 16;
static const int CHUNK_HEIGHT = 256;

class Chunk {
public:
    Chunk(int x, int z);
    ~Chunk() = default;

    void generate(); // e.g. terrain generation using noise
    Voxel getVoxel(int x, int y, int z) const;
    void setVoxel(int x, int y, int z, Voxel voxel);

    // Returns chunk world-space position
    int getX() const { return m_chunkX; }
    int getZ() const { return m_chunkZ; }

private:
    int m_chunkX;
    int m_chunkZ;
    std::vector<Voxel> m_data; // store chunk data, size = CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE
};
