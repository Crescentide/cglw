//
// Created by kirut on 1/18/2025.
//

#ifndef PROJECTTSUNAMIMOONLIGHT_TEXTUREGL_H
#define PROJECTTSUNAMIMOONLIGHT_TEXTUREGL_H

#include "Object.h"
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <iostream>


namespace cglw {
    class Texture : public Object {
        static constexpr std::string_view LOG_TAG = "cglw::Texture";
        static constexpr int NUM_TEXTURES = 1;

        glm::ivec2 size {0};
        GLenum format = GL_RGBA8;

    public:
        Texture(glm::ivec2 size, GLenum format);
        ~Texture() override;
        // moving
        Texture(Texture&& other) noexcept;
        Texture& operator=(Texture&& other) noexcept;

        [[nodiscard]] int getHeight() const { return size.x; };
        [[nodiscard]] int getWidth() const { return size.y; };

        void set(const void* pixels) const;

    };
} // Engine

#endif //PROJECTTSUNAMIMOONLIGHT_TEXTUREGL_H
