//
// Created by kirut on 8/5/2025.
//

#ifndef PROJECTTSUNAMIMOONLIGHT_VERTEXARRAY_H
#define PROJECTTSUNAMIMOONLIGHT_VERTEXARRAY_H

#include <string_view>
#include "Vertex.h"
#include <array>

namespace cglw {

class VertexArray {
  static constexpr std::string_view LOG_TAG = "cglw::VertexArray";
  static constexpr int NUM_VAO = 1;
  static constexpr unsigned int INVALID_ID = 0;

  unsigned int mID;

  static unsigned int createVAO();
  bool tryDestroy();

public:
  VertexArray();
  ~VertexArray();
  // disable copy
  VertexArray(const VertexArray&) = delete;
  VertexArray& operator=(const VertexArray&) = delete;
  // moving
  VertexArray(VertexArray&& other) noexcept;
  VertexArray& operator=(VertexArray&& other) noexcept;

  void bind() const;
  void unbind() const;
  [[nodiscard]] unsigned int getID() const;
  [[nodiscard]] bool isValid() const;
  void invalidate();

  void
  addVertexAttributes(const std::array<VertexAttribute, 3>& pAttributes) const;
};

} // namespace CE

#endif // PROJECTTSUNAMIMOONLIGHT_VERTEXARRAY_H
