//
// Created by kirut on 8/5/2025.
//

#include "VertexArray.h"
#include "Log.h"
#include "glad/gl.h"

namespace cglw {
VertexArray::VertexArray() : mID(createVAO()) {

}
VertexArray::~VertexArray() {
  tryDestroy();
}
VertexArray::VertexArray(VertexArray &&other) noexcept : mID(other.mID) {
  other.mID = INVALID_ID;
}
VertexArray &VertexArray::operator=(VertexArray &&other) noexcept {
  if (this != &other) {
    tryDestroy();

    mID = other.mID;

    other.mID = INVALID_ID;
  }

  return *this;
}
unsigned int VertexArray::createVAO() {
  unsigned int vao = INVALID_ID;

  glGenVertexArrays(NUM_VAO, &vao);
  if (vao == INVALID_ID) {
    Log::warn(LOG_TAG, "Failed to create a new Vertex Array ID!");
  }

  return vao;
}
bool VertexArray::tryDestroy() {
  if (mID == INVALID_ID) return false;

  glDeleteVertexArrays(NUM_VAO, &mID);

  mID = INVALID_ID;

  return true;
}
void VertexArray::bind() const {
  glBindVertexArray(mID);
}
void VertexArray::unbind() const {
  glBindVertexArray(0);
}
unsigned int VertexArray::getID() const {
  return mID;
}
void VertexArray::addVertexAttributes(
    const std::array<VertexAttribute, 3> &pAttributes) const {
  bind();

  for (int i = 0; i < pAttributes.size(); ++i) {
    auto& attr = pAttributes[i];
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, attr.numComponents, attr.numComponents, attr.normalized, sizeof(Vertex), (void*) attr.offset);
  }
}
bool VertexArray::isValid() const {
  return mID != INVALID_ID;
}
void VertexArray::invalidate() {
  tryDestroy();
}
} // namespace CE