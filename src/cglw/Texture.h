//
// Created by kirut on 1/18/2025.
//

#ifndef PROJECTTSUNAMIMOONLIGHT_TEXTUREGL_H
#define PROJECTTSUNAMIMOONLIGHT_TEXTUREGL_H

#include <glm/glm.hpp>
#include <iostream>
#include <glad/gl.h>


namespace cglw {
    class Texture {
        static constexpr std::string_view LOG_TAG = "cglw::Texture";
        unsigned int id = 0;
        glm::ivec2 size {0};
        GLenum format = GL_RGBA8;

    public:
        Texture(glm::ivec2 size, GLenum format);
        ~Texture();
        // disable copy
        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;
        // moving
        Texture(Texture&& other) noexcept;
        Texture& operator=(Texture&& other) noexcept;

        [[nodiscard]] unsigned int getId() const { return id; };
        [[nodiscard]] int getHeight() const { return size.x; };
        [[nodiscard]] int getWidth() const { return size.y; };

        void bind() const;
        static void unbind();

        void set(const void* pixels) const;

    };
} // Engine

#endif //PROJECTTSUNAMIMOONLIGHT_TEXTUREGL_H
