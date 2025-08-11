//
// Created by kirut on 8/5/2025.
//

#include "Buffer.h"
#include "Log.h"
#include "glad/gl.h"
#include <utility>

namespace cglw {
    Buffer::Buffer(Buffer::Type pType): mType(pType) {
        Log::trace(LOG_TAG, "Creating a new {} Buffer", typeToStr(mType.value()));

        glCreateBuffers(NUM_BUFFERS, &mID);
        if (mID == INVALID_ID) {
            throw std::runtime_error(std::format("Failed to create new Buffer of type {}\n"
                                                 "\tNew OpenGL Object returned invalid ID!",typeToStr(mType.value())));
        }

        Log::debug(LOG_TAG, "Successfully created a {} Buffer, ID: ", typeToStr(mType.value()), mID);
    }

    Buffer::~Buffer() {
        Log::trace(LOG_TAG, "Destroying a {} Buffer, ID: {}", typeToStr(mType.value()), mID);

        if (mID != INVALID_ID) glDeleteBuffers(NUM_BUFFERS, &mID);

        Log::debug(LOG_TAG, "Successfully destroyed a {} Buffer", typeToStr(mType.value()));
        // Invalid ID should not be possible. assert?
    }

    Buffer::Buffer(Buffer &&other) noexcept
        : mType(std::exchange(other.mType, std::nullopt)) {
        mID = std::exchange(other.mID, INVALID_ID);

        Log::trace(LOG_TAG, "Moving a {} Buffer, ID: {}", typeToStr(mType.value()), mID);
    }

    Buffer &Buffer::operator=(Buffer &&other) noexcept {
      if (this != &other) {
        Log::trace(LOG_TAG, "Moving a {} Buffer, ID: to {} Buffer, ID: {}",
                     typeToStr(mType.value()), mID, typeToStr(other.mType.value()), other.mID);

        if (mID != INVALID_ID) {
            Log::trace(LOG_TAG, "Destroying a {} Buffer, ID: {}", typeToStr(mType.value()), mID);
            glDeleteBuffers(NUM_BUFFERS, &mID);
        }

        mType = std::exchange(other.mType, std::nullopt);
        mID = std::exchange(other.mID, INVALID_ID);
      }

      return *this;
    }

    constexpr std::string_view Buffer::typeToStr(BufferType type) {
        switch (type) {
            case BufferType::Vertex: return "Vertex";
            case BufferType::Element: return "Element";
            case BufferType::Uniform: return "Uniform";
            case BufferType::ShaderStorage: return "Shader Storage";
//            case BufferType::Invalid: return "Invalid";
        }
    }

    template <typename T>
    void Buffer::setData(const std::vector<T> &data) {
        glNamedBufferData(mID, static_cast<GLsizeiptr>(data.size() * sizeof(T)), data.data(), GL_STATIC_DRAW);
    }

    template <typename T>
    void Buffer::setSubData(int offset, const std::vector<T> &data) {
        glNamedBufferSubData(mID, offset, static_cast<GLsizeiptr>(data.size() * sizeof(T)), data.data());
    }
} // namespace CE