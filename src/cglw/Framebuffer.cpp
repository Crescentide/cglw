//
// Created by kirut on 7/22/2025.
//


#include "Framebuffer.h"
#include "Log.h"
#include "glad/gl.h"

namespace cglw {
  Framebuffer::Framebuffer() : Object(create(), Object::Type::Framebuffer) {

  }

  unsigned int Framebuffer::create() {
    unsigned int fbo = INVALID_ID; // 0 is the invalid id

    glCreateFramebuffers(NUM_FBO, &fbo);
    if (fbo == INVALID_ID) {
      Log::warn(LOG_TAG, "Failed to create a new Framebuffer");
    }

    return fbo;
  }

  Framebuffer::~Framebuffer() {
    tryDestroy();
  }

  Framebuffer::Framebuffer(Framebuffer &&other) noexcept
  : Object(std::move(other)), mTexture(std::move(other.mTexture)), mRenderbuffer(std::move(other.mRenderbuffer)) {
    other.mTexture = std::nullopt;
    other.mRenderbuffer = std::nullopt;
  }

  Framebuffer &Framebuffer::operator=(Framebuffer &&other) noexcept {
    if (this != &other) {
      tryDestroy();

      Object::operator=(std::move(other));
      mTexture = std::move(other.mTexture);
      mRenderbuffer = std::move(other.mRenderbuffer);

      other.mTexture = std::nullopt;
      other.mRenderbuffer = std::nullopt;
    }

    return *this;
  }

  bool Framebuffer::tryDestroy() {
    if (mID == INVALID_ID) return false;

    glDeleteFramebuffers(NUM_FBO, &mID);
    mTexture = std::nullopt;
    mRenderbuffer = std::nullopt;

    return true;
  }

  bool Framebuffer::isComplete() {
    bool value = false;

    if (!isValid()) {
      Log::warn(LOG_TAG, "Failed to check if Framebuffer is complete: \n"
                          "\tThis Framebuffer is invalid!");
      return false;
    }

    value = glCheckNamedFramebufferStatus(mID, GL_FRAMEBUFFER_COMPLETE);

    return value;
  }
  bool Framebuffer::tryAttachTexture(Texture& pNewTexture, std::optional<Texture> pOldTexture) {
    if (!isValid()) {
      Log::warn(LOG_TAG, "Failed to attach a Texture to a Framebuffer:\n"
                         "\tThis Framebuffer is invalid!");
      return false;
    }

    // TODO: is texture valid

    glNamedFramebufferTexture(mID, GL_COLOR_ATTACHMENT0, pNewTexture.getId(), 0);

    if (!isComplete()) {
      Log::warn(LOG_TAG, "Failed to attach a Texture to a Framebuffer:\n"
                         "\tThis Framebuffer is incomplete after trying to attach a Texture!");
      return false;
    }

    if (mTexture.has_value())
      pOldTexture = std::move(mTexture);
    mTexture = std::move(pNewTexture);

    return true;
  }
  bool Framebuffer::tryAttachRenderbuffer(
      Renderbuffer &pNewRenderbuffer,
      std::optional<Renderbuffer> pOldRenderbuffer) {
    if (!isValid()) {
      Log::warn(LOG_TAG, "Failed to attach a Renderbuffer to a Framebuffer:\n"
                         "\tThis Framebuffer is invalid!");
      return false;
    }


    glNamedFramebufferRenderbuffer(mID, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, pNewRenderbuffer.getID());

    if (!isComplete()) {
      Log::warn(LOG_TAG, "Failed to attach a Renderbuffer to a Framebuffer:\n"
                         "\tThis Framebuffer is incomplete after trying to attach a Renderbuffer!");
      return false;
    }

    if (mRenderbuffer.has_value())
      pOldRenderbuffer = std::move(mRenderbuffer);
    mRenderbuffer = std::move(pNewRenderbuffer);

    return true;
  }

  } // CE
