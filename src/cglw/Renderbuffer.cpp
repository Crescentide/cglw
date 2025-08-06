//
// Created by kirut on 8/3/2025.
//

#include "Renderbuffer.h"
#include "Log.h"
#include <glad/gl.h>

namespace cglw {
Renderbuffer::Renderbuffer() : Object(create(), Object::Type::Renderbuffer) {

}

Renderbuffer::~Renderbuffer() { tryDestroy(); }

Renderbuffer::Renderbuffer(Renderbuffer &&other) noexcept : Object(std::move(other)) {
}
Renderbuffer &Renderbuffer::operator=(Renderbuffer &&other) noexcept {
  if (this != &other) {
    tryDestroy();

    Object::operator=(std::move(other));
  }

  return *this;
}

unsigned int Renderbuffer::create() {
  unsigned int rbo = INVALID_ID; // 0 is invalid id

  glCreateRenderbuffers(NUM_RBO, &rbo);
  if (rbo == INVALID_ID) {
    Log::warn(LOG_TAG, "Failed to generate a new Renderbuffer!");
  }

  return rbo;
}
bool Renderbuffer::tryDestroy() {
  if (mID == INVALID_ID) return false;

  glDeleteRenderbuffers(NUM_RBO, &mID);

  return true;
}

void Renderbuffer::setStorage(const glm::ivec2 &pSize) const {
  if (!isValid()) return;

  // TODO: add more checking and custom format
  glNamedRenderbufferStorage(mID, GL_DEPTH24_STENCIL8, pSize.x, pSize.y);
}

} // namespace CE