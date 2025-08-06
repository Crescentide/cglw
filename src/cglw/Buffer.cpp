//
// Created by kirut on 8/5/2025.
//

#include "Buffer.h"
#include "Log.h"
#include "glad/gl.h"

namespace cglw {
Buffer::Buffer(Buffer::Type pType)
    : Object(create() , Object::Type::Buffer), mType(pType) {

}
Buffer::~Buffer() {
  tryDestroy();
}
Buffer::Buffer(Buffer &&other) noexcept : Object(std::move(other)), mType(other.mType) {
  other.mType = Type::Invalid;
}
Buffer &Buffer::operator=(Buffer &&other) noexcept {
  if (this != &other) {
    tryDestroy();

    Object::operator=(std::move(other));
    mType = other.mType;

    other.mType = Type::Invalid;
  }

  return *this;
}
unsigned int Buffer::create() {
  unsigned int buffer = INVALID_ID;

  glCreateBuffers(NUM_BUFFER, &buffer);

  if (buffer == INVALID_ID) {
    Log::warn(LOG_TAG, "Failed to generate a new Buffer ID!");
  }

  return buffer;
}
bool Buffer::tryDestroy() {
    if (mID == INVALID_ID) return false;

    glDeleteBuffers(NUM_BUFFER, &mID);

    return true;
}
void Buffer::invalidate() {
  tryDestroy();
}
std::string_view Buffer::typeToStr(BufferType type) {
    switch (type) {
        case BufferType::Vertex: return "Vertex";
        case BufferType::Element: return "Element";
        case BufferType::Uniform: return "Uniform";
        case BufferType::ShaderStorage: return "Shader Storage";
        case BufferType::Invalid: return "Invalid";
    }
}
template <typename T>
void Buffer::setData(const std::vector<T> &data) {
    if (!isValid()) {
        Log::warn(LOG_TAG, "Failed to set the data for a Buffer:\n"
                           "\tThis Buffer is invalid!");
        return;
    }

    glNamedBufferData(mID, static_cast<GLsizeiptr>(data.size() * sizeof(T)), data.data(), GL_STATIC_DRAW);
}
template <typename T>
void Buffer::setSubData(int offset, const std::vector<T> &data) {
    if (!isValid()) {
        Log::warn(LOG_TAG, "Failed to set the sub data for a Buffer:\n"
                           "\tThis Buffer is invalid!");
        return;
    }

  glNamedBufferSubData(mID, offset, static_cast<GLsizeiptr>(data.size() * sizeof(T)), data.data());
}
} // namespace CE