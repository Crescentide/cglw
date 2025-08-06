//
// Created by kirut on 8/5/2025.
//

#ifndef PROJECTTSUNAMIMOONLIGHT_BUFFER_H
#define PROJECTTSUNAMIMOONLIGHT_BUFFER_H

#include "Object.h"
#include "glad/gl.h"
#include <string_view>
#include <vector>

namespace cglw {

enum class BufferType : GLenum {
  Vertex = GL_ARRAY_BUFFER,
  Element = GL_ELEMENT_ARRAY_BUFFER,
  Uniform = GL_UNIFORM_BUFFER,
  ShaderStorage = GL_SHADER_STORAGE_BUFFER,
  Invalid,
};

class Buffer : protected Object {
  static constexpr std::string_view LOG_TAG = "cglw::Buffer";
  static constexpr int NUM_BUFFER = 1; // Currently not setup for an array of FBO names

  BufferType mType = BufferType::Invalid;

  unsigned int create() override;
  bool tryDestroy();
  static std::string_view typeToStr(BufferType type);

public:
  using Type = BufferType;

  explicit Buffer(Type pType);
  ~Buffer();
  // disable copy
  Buffer(const Buffer&) = delete;
  Buffer& operator=(const Buffer&) = delete;
  // moving
  Buffer(Buffer&& other) noexcept;
  Buffer& operator=(Buffer&& other) noexcept;

  void invalidate() override;

  template <typename T>
  void setData(const std::vector<T>& data); // TOOD: static/dynamic draw
  template <typename T>
  void setSubData(int offset, const std::vector<T>& data);
};

} // namespace CE

#endif // PROJECTTSUNAMIMOONLIGHT_BUFFER_H
