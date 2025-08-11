//
// Created by kirut on 8/5/2025.
//

#ifndef CGLW_BUFFER_H
#define CGLW_BUFFER_H

#include "Object.h"
#include "glad/gl.h"
#include <string_view>
#include <vector>
#include <optional>

namespace cglw {
    enum class BufferType : GLenum {
        Vertex = GL_ARRAY_BUFFER,
        Element = GL_ELEMENT_ARRAY_BUFFER,
        Uniform = GL_UNIFORM_BUFFER,
        ShaderStorage = GL_SHADER_STORAGE_BUFFER,
//        Invalid
    };

    class Buffer : public Object {
      static constexpr std::string_view LOG_TAG = "cglw::Buffer";
      static constexpr int NUM_BUFFERS = 1;

      std::optional<BufferType> mType; // nullopt for invalid state
//      BufferType mType;

      static constexpr std::string_view typeToStr(BufferType type);

    public:
      using Type = BufferType;

      explicit Buffer(Type pType);
      ~Buffer() override;
      // moving
      Buffer(Buffer&& other) noexcept;
      Buffer& operator=(Buffer&& other) noexcept;

      template <typename T>
      void setData(const std::vector<T>& data); // TOOD: static/dynamic draw
      template <typename T>
      void setSubData(int offset, const std::vector<T>& data);
    };
} // namespace CE

#endif // CGLW_BUFFER_H
