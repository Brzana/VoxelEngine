#pragma once

#include <vector>
#include "Voxel.h"
#include "OpenGl.h"

struct Vertex {
	float x, y, z;
	float u, v;
	float nx, ny, nz;
};

class ChunkMesh {
public:
	ChunkMesh();
	~ChunkMesh();

	void createMesh(const std::vector<Vertex>& vertices);

	// for VAO/VBO
	void uploadToGPU();

	void render() const;

	void clear();

private:
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indicies;

	unsigned int m_vao;
	unsigned int m_vbo;

	GLsizei m_vertexCount;
};
