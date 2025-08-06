//
// Created by kirut on 1/18/2025.
//


#include "Texture.h"
namespace cglw {


//    void TextureGL::update(void *pixels) {
//        bind();
//        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width(), height(), GL_BGRA, GL_UNSIGNED_BYTE, pixels);
//        unbind();
//    }
    Texture::Texture(glm::ivec2 size, GLenum format)
    : size(size), format(format) {
        glGenTextures(1, &id);

        bind();

        glTexImage2D(GL_TEXTURE_2D, 0, format, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        // TODO: make these user changeable
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glGenerateMipmap(GL_TEXTURE_2D);

        unbind();
    }

    Texture::~Texture() {
        if (id)
            glDeleteTextures(1, &id);
    }

    Texture::Texture(Texture &&other) noexcept
    : id(other.id), size(other.size), format(other.format) {
        other.id = 0;
    }

    Texture &Texture::operator=(Texture &&other) noexcept {
        if (this != &other) {
            if (id)
                glDeleteTextures(1, &id);
            id = other.id;
            size = other.size;
            format = other.format;

            other.id = 0;
        }
        return *this;
    }

    void Texture::bind() const {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, id);
    }

    void Texture::unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::set(const void *pixels) const {
        bind();
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size.x, size.y, format, GL_UNSIGNED_BYTE, pixels);
        unbind();
    }
} // Engine