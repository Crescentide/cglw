//
// Created by kirut on 8/3/2025.
//

#include "Renderbuffer.h"
#include "Log.h"
#include <glad/gl.h>
#include <utility>

namespace cglw {
Renderbuffer::Renderbuffer() {
    Log::trace(LOG_TAG, "Creating a new Renderbuffer");

    glCreateRenderbuffers(NUM_RBOS, &mID);
    if (mID == INVALID_ID) {
        throw std::runtime_error("Failed to create a new Renderbuffer ID");
    }

    Log::debug(LOG_TAG, "Successfully created a new Renderbuffer, ID: {}", mID);
}

Renderbuffer::~Renderbuffer() {
    Log::trace(LOG_TAG, "Destroying a Renderbuffer, ID: {}", mID);

    if (mID != INVALID_ID) glDeleteRenderbuffers(NUM_RBOS, &mID);

    Log::debug(LOG_TAG, "Successfully destroyed a Renderbuffer");
}

Renderbuffer::Renderbuffer(Renderbuffer &&other) noexcept {
    mID = std::exchange(other.mID, INVALID_ID);

    Log::trace(LOG_TAG, "Moving a Renderbuffer ID: {}", mID);
}
Renderbuffer &Renderbuffer::operator=(Renderbuffer &&other) noexcept {
  if (this != &other) {
    Log::trace(LOG_TAG, "Moving a Renderbuffer, ID: {} to Renderbuffer, ID: {}", mID, other.mID);

    if (mID != INVALID_ID) {
        Log::trace(LOG_TAG, "Destroying a Renderbuffer, ID: {}", mID);
        glDeleteBuffers(NUM_RBOS, &mID);
    }

    mID = std::exchange(other.mID, INVALID_ID);
  }

  return *this;
}

void Renderbuffer::setStorage(const glm::ivec2 &pSize) const {
  // Future: add more checking and custom format
  glNamedRenderbufferStorage(mID, GL_DEPTH24_STENCIL8, pSize.x, pSize.y);
}

} // namespace CE