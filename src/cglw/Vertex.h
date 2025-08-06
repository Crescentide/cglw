//
// Created by kirut on 8/5/2025.
//

#ifndef PROJECTTSUNAMIMOONLIGHT_VERTEX_H
#define PROJECTTSUNAMIMOONLIGHT_VERTEX_H

#include "glad/gl.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace cglw {

struct Vertex {
  glm::vec3 position;
  glm::vec2 texCoord;
  glm::vec4 color;
};

struct VertexAttribute {
  int numComponents = 0;
  GLenum type = 0;
  bool normalized = false;
  size_t offset = 0;
};

// Now we can safely define these
static constexpr std::array<VertexAttribute, 3> VertexAttributes = {{
    {3, GL_FLOAT, false, offsetof(Vertex, position)},
    {2, GL_FLOAT, false, offsetof(Vertex, texCoord)},
    {4, GL_FLOAT, false, offsetof(Vertex, color)}
}};

} // namespace CE

#endif // PROJECTTSUNAMIMOONLIGHT_VERTEX_H
