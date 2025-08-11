//
// Created by kirut on 8/5/2025.
//

#include "VertexArray.h"
#include "Log.h"
#include "glad/gl.h"
#include <utility>

namespace cglw {
    VertexArray::VertexArray() {
        Log::trace(LOG_TAG, "Creating a new Vertex Array");

        glCreateVertexArrays(NUM_VAOS, &mID);
        if (mID == INVALID_ID) {
            throw std::runtime_error("Failed to create a new Vertex Array ID");
        }

        Log::debug(LOG_TAG, "Successfully created a new Vertex Array, ID: {}", mID);
    }
    VertexArray::~VertexArray() {
        Log::trace(LOG_TAG, "Destroying a Vertex Array, ID: {}", mID);

        if (mID != INVALID_ID) glDeleteVertexArrays(NUM_VAOS, &mID);

        Log::debug(LOG_TAG, "Successfully destroyed a Vertex Array");
    }
    VertexArray::VertexArray(VertexArray &&other) noexcept {
        mID = std::exchange(other.mID, INVALID_ID);

        Log::trace(LOG_TAG, "Moving a Vertex Array, ID: {}", mID);
    }
    VertexArray &VertexArray::operator=(VertexArray &&other) noexcept {
      if (this != &other) {
          Log::trace(LOG_TAG, "Moving a Vertex Array, ID: {} to Vertex Array, ID: {}", mID, other.mID);

          if (mID != INVALID_ID) {
              Log::trace(LOG_TAG, "Destroying a Vertex Array, ID: {}", mID);
              glDeleteVertexArrays(NUM_VAOS, &mID);
          }

          mID = std::exchange(other.mID, INVALID_ID);
      }

      return *this;
    }

    void VertexArray::addVertexAttributes(Object::ID pVBO,
        const std::array<VertexAttribute, 3> &pAttributes) const {

      for (int i = 0; i < pAttributes.size(); ++i) {
        const auto& attr = pAttributes[i];

        glVertexArrayAttribFormat(
                mID,                           // VAO ID
                i,                             // Attribute index
                attr.numComponents,            // Components (e.g., 3 for vec3)
                attr.type,                     // Data type (e.g., GL_FLOAT)
                attr.normalized ? GL_TRUE : GL_FALSE,
                attr.offset                     // Offset in the vertex struct
        );

        glVertexArrayAttribBinding(mID, i, i);

        glEnableVertexArrayAttrib(mID, i);

        glVertexArrayVertexBuffer(
                mID,
                i,                              // Binding index
                pVBO,                // Vertex buffer object ID
                0,                              // Offset in buffer
                sizeof(Vertex)                  // Stride between vertices
        );
      }
    }
} // namespace CE