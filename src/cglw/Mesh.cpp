//
// Created by kirut on 2/27/2025.
//

#include "Mesh.h"
#include "glad/gl.h"

namespace cglw {
//    void MeshGL::update(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
//        glBindVertexArray(VAO);
//        indicesCount = indices.size();
//
//        glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        glBufferSubData(GL_ARRAY_BUFFER, 0, (GLsizeiptr) (vertices.size() * sizeof(Vertex)), vertices.data());
//
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, (GLsizeiptr) (indices.size() * sizeof(unsigned int)), indices.data());
//
//        glBindVertexArray(0);
//    }


    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
    : mVBO(Buffer::Type::Vertex), mEBO(Buffer::Type::Element),
      mVertices(std::move(vertices)), mIndices(std::move(indices)) {

        mVBO.setData(mVertices); // TODO: check if correct
        mVAO.addVertexAttributes(VertexAttributes);
        mEBO.setSubData(0, indices);

        mVAO.unbind();
    }

    Mesh::~Mesh() {

    }

    Mesh::Mesh(Mesh &&other) noexcept
    : mVAO(std::move(other.mVAO)), mVBO(std::move(other.mVBO)), mEBO(std::move(other.mEBO)),
          mVertices(std::move(other.mVertices)),
          mIndices(std::move(other.mIndices)) {

    }

    Mesh &Mesh::operator=(Mesh &&other) noexcept {
        if (this != &other) {
          mVAO = std::move(other.mVAO);
          mVBO = std::move(other.mVBO);
          mEBO = std::move(other.mEBO);
          mVertices = std::move(other.mVertices);
          mIndices = std::move(other.mIndices);

          // TODO: reset
        }

        return *this;
    }

    void Mesh::draw() {
        mVAO.bind();
        glDrawElements(GL_TRIANGLES, (GLsizei)mIndices.size(), GL_UNSIGNED_INT, nullptr);
        mVAO.unbind();
    }
} // Engine