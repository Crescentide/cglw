//
// Created by kirut on 8/5/2025.
//

#ifndef PROJECTTSUNAMIMOONLIGHT_VERTEXARRAY_H
#define PROJECTTSUNAMIMOONLIGHT_VERTEXARRAY_H

#include "Object.h"
#include "Vertex.h"
#include <array>
#include <string_view>

namespace cglw {

class VertexArray : public Object {
  static constexpr std::string_view LOG_TAG = "cglw::VertexArray";
  static constexpr int NUM_VAOS = 1;

public:
  VertexArray();
  ~VertexArray() override;
  // moving
  VertexArray(VertexArray&& other) noexcept;
  VertexArray& operator=(VertexArray&& other) noexcept;

  void
  addVertexAttributes(Object::ID pVBO, const std::array<VertexAttribute, 3>& pAttributes) const;
};

} // namespace CE

#endif // PROJECTTSUNAMIMOONLIGHT_VERTEXARRAY_H
