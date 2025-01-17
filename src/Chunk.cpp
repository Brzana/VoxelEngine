#include "../include/Chunk.h"
#include <cmath>

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

// naive way, if air is neighbour generate all 6 faces
void Chunk::buildMesh() {
    std::vector<Vertex> vertices;
    vertices.reserve(CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE * 6 * 6);
    for (int y = 0; y < CHUNK_HEIGHT; ++y) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            for (int x = 0; x < CHUNK_SIZE; ++x) {
                int index = x + z * CHUNK_SIZE + y * CHUNK_SIZE * CHUNK_SIZE;
                if (m_data[index].type == 0) {
                    // air -> skip
                    continue;
                }

                // For each of the 6 directions, check if that neighbor is air
                // If neighbor is out of bounds or air, add face
                if (x == CHUNK_SIZE - 1 || m_data[index].type == 0) {
                    float fx = (float)x;
                    float fy = (float)y;
                    float fz = (float)z;
                    Vertex v1{ fx + 1, fy,   fz,   0.0f, 0.0f };
                    Vertex v2{ fx + 1, fy,   fz + 1, 0.0f, 1.0f };
                    Vertex v3{ fx + 1, fy + 1, fz,   1.0f, 0.0f };
                    Vertex v4{ fx + 1, fy + 1, fz,   1.0f, 0.0f };
                    Vertex v5{ fx + 1, fy,   fz + 1, 0.0f, 1.0f };
                    Vertex v6{ fx + 1, fy + 1, fz + 1, 1.0f, 1.0f };

                    vertices.push_back(v1);
                    vertices.push_back(v2);
                    vertices.push_back(v3);
                    vertices.push_back(v4);
                    vertices.push_back(v5);
                    vertices.push_back(v6);
                }
                // To Do: other faces (-x, +-z, +-y)
            }
        }
    }
    m_mesh.createMesh(vertices);
}

void Chunk::render() {
    // We might want to apply a model matrix offset based on chunkX, chunkZ,
    // so you’d set the uniform in the shader before calling m_mesh.render().
    // That might look like:
    //
    // glm::mat4 model = glm::translate(glm::mat4(1.0f),
    //     glm::vec3(m_chunkX * CHUNK_SIZE, 0.0f, m_chunkZ * CHUNK_SIZE));
    // shader.setUniform("uModel", model);

    m_mesh.render();
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
