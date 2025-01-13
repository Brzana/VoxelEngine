#include "../include/Chunk.h"
#include <algorithm> // etc.

static const int FLAT_GROUND_HEIGHT = 50;

Chunk::Chunk(int x, int z)
    : m_chunkX(x)
    , m_chunkZ(z)
    , m_data(CHUNK_SIZE* CHUNK_HEIGHT* CHUNK_SIZE)
{}

void Chunk::generate() {
    for (int y = 0; y < CHUNK_HEIGHT; ++y) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            for (int x = 0; x < CHUNK_SIZE; ++x) {
                Voxel voxel;
                if (y < FLAT_GROUND_HEIGHT) {
                    voxel.type = 1;
                }
                else {
                    voxel.type = 0;
                }
                setVoxel(x, y, z, voxel);
            }
        }
    }
}

Voxel Chunk::getVoxel(int x, int y, int z) const {
    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_HEIGHT || z < 0 || z >= CHUNK_SIZE) {
        return Voxel();
    }
    return m_data[x + (z * CHUNK_SIZE) + (y * CHUNK_SIZE * CHUNK_SIZE)];
}

void Chunk::setVoxel(int x, int y, int z, Voxel voxel) {
    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_HEIGHT || z < 0 || z >= CHUNK_SIZE) {
        return;
    }
    m_data[x + (z * CHUNK_SIZE) + (y * CHUNK_SIZE * CHUNK_SIZE)] = voxel;
}
