#include "./../include/ChunkMesh.h"
#include "./../include/OpenGl.h"

ChunkMesh::ChunkMesh()
    : m_vao(0)
    , m_vbo(0)
    , m_vertexCount(0)
{}

ChunkMesh::~ChunkMesh() {
    clear();
}

void ChunkMesh::createMesh(const std::vector<Vertex>& vertex) {
    clear();

    m_vertexCount = (GLsizei)vertex.size();

    // generate and bind vao
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // generate and bind vbo
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertexCount, m_vertices.data(), GL_STATIC_DRAW);

    // atribute pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, nx));

    glBindVertexArray(0);
}

void ChunkMesh::render() const {
    if (m_vao == 0) return;

    // bind VAO and draw
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
    glBindVertexArray(0);
}

void ChunkMesh::clear() {
    if (m_vbo) {
        glDeleteBuffers(1, &m_vbo);
        m_vbo = 0;
    }

    if (m_vao) {
        glDeleteBuffers(1, &m_vao);
        m_vao = 0;
    }
    m_vertexCount = 0;
}