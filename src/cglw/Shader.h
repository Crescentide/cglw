//
// Created by kirut on 1/18/2025.
//

#ifndef PROJECTTSUNAMIMOONLIGHT_SHADERGL_H
#define PROJECTTSUNAMIMOONLIGHT_SHADERGL_H


#include "Object.h"
#include <glad/gl.h>
#include <unordered_map>

namespace cglw {
    enum class ShaderType : GLenum {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
    };

    class Shader : public Object {
        static constexpr std::string_view LOG_TAG = "cglw::Shader";

        ShaderType mType;

        static constexpr std::string_view typeToStr(ShaderType pType);

    public:
        using Type = ShaderType;

        Shader(Type pType, std::string_view pPath);
        ~Shader() override;
        // moving
        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        [[nodiscard]] Type getType() const noexcept { return mType; };

    };
} // Engine

#endif //PROJECTTSUNAMIMOONLIGHT_SHADERGL_H
