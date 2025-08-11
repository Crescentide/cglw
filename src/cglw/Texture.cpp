//
// Created by kirut on 1/18/2025.
//


#include "Texture.h"
#include "Log.h"
#include <utility>
namespace cglw {


//    void TextureGL::update(void *pixels) {
//        bind();
//        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width(), height(), GL_BGRA, GL_UNSIGNED_BYTE, pixels);
//        unbind();
//    }
    Texture::Texture(glm::ivec2 size, GLenum format): size(size), format(format) {
        Log::trace(LOG_TAG, "Creating a new Texture");

        glGenTextures(NUM_TEXTURES, &mID);
        if (mID == INVALID_ID) {
            throw std::runtime_error("Failed to create a new Texture ID");
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        // TODO: make named texture
        // TODO: make these user changeable
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glGenerateMipmap(GL_TEXTURE_2D);

        Log::debug(LOG_TAG, "Successfully created a Texture, ID: {}", mID);
    }

    Texture::~Texture() {
        Log::trace(LOG_TAG, "Destroying a Texture, ID: {}", mID);

        if (mID == INVALID_ID) glDeleteTextures(1, &mID);

        Log::debug(LOG_TAG, "Successfully destroyed a Texture");
    }

    Texture::Texture(Texture &&other) noexcept
    : size(other.size), format(other.format) {
        mID = std::exchange(other.mID, INVALID_ID);

        Log::trace(LOG_TAG, "Moving a Texture, ID: {}", mID);
    }

    Texture &Texture::operator=(Texture &&other) noexcept {
        if (this != &other) {
            Log::trace(LOG_TAG, "Moving a Texture, ID: {} to Texture, ID: {}", mID, other.mID);

            if (mID != INVALID_ID) {
                Log::trace(LOG_TAG, "Destroying a Texture, ID: {}", mID);
                glDeleteTextures(1, &mID);
            }

            size = other.size;
            format = other.format;
            mID = std::exchange(other.mID, INVALID_ID);
        }
        return *this;
    }

    void Texture::set(const void *pixels) const {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size.x, size.y, format, GL_UNSIGNED_BYTE, pixels);
    }
} // Engine