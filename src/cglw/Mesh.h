//
// Created by kirut on 2/27/2025.
//

#ifndef PROJECTTSUNAMIMOONLIGHT_MESHGL_H
#define PROJECTTSUNAMIMOONLIGHT_MESHGL_H

#include "Buffer.h"
#include "VertexArray.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include <glad/gl.h>
#include <string_view>
#include <vector>

namespace cglw {


  class Mesh {
    static constexpr std::string_view LOG_TAG = "cglw::Mesh";

    VertexArray mVAO;
    Buffer mVBO;
    Buffer mEBO;
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;

  public:
      Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
      ~Mesh();
      // disable copy
      Mesh(const Mesh&) = delete;
      Mesh& operator=(const Mesh&) = delete;
      // moving
      Mesh(Mesh&& other) noexcept;
      Mesh& operator=(Mesh&& other) noexcept;


      void draw();
  //        void update(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
  };
} // Engine

#endif //PROJECTTSUNAMIMOONLIGHT_MESHGL_H
