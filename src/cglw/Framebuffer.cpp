//
// Created by kirut on 7/22/2025.
//


#include "Framebuffer.h"
#include "Log.h"
#include "glad/gl.h"
#include <utility>

namespace cglw {
    Framebuffer::Framebuffer() {
        Log::trace(LOG_TAG, "Creating a new Framebuffer");

        glCreateFramebuffers(NUM_FBOS, &mID);
        if (mID == INVALID_ID) {
            throw std::runtime_error("Failed to create new Framebuffer!");
        }

        Log::debug(LOG_TAG, "Successfully created a Framebuffer, ID: {}", mID);
    }

    Framebuffer::~Framebuffer() {
        Log::trace(LOG_TAG, "Destroying a Framebuffer, ID: {}", mID);

        if (mID != INVALID_ID) glDeleteFramebuffers(NUM_FBOS, &mID);

        Log::debug(LOG_TAG, "Successfully destroyed a Framebuffer");
    }

    Framebuffer::Framebuffer(Framebuffer &&other) noexcept
        : mTexture(std::move(other.mTexture)),
          mRenderbuffer(std::move(other.mRenderbuffer)) {
        mID = std::exchange(other.mID, INVALID_ID);

        Log::trace(LOG_TAG, "Moving a Framebuffer, ID: {}", mID);
    }

    Framebuffer &Framebuffer::operator=(Framebuffer &&other) noexcept {
        if (this != &other) {
            Log::trace(LOG_TAG, "Moving a Framebuffer, ID: {} to Framebuffer, ID: {}",
                       mID, other.mID);

            if (mID != INVALID_ID)  {
                Log::trace(LOG_TAG, "Destroying a Framebuffer, ID: {}", mID);
                glDeleteFramebuffers(NUM_FBOS, &mID);
            }

            mTexture = std::move(other.mTexture);
            mRenderbuffer = std::move(other.mRenderbuffer);
            mID = std::exchange(other.mID, INVALID_ID);
        }

        return *this;
    }

    bool Framebuffer::isComplete() {
        return glCheckNamedFramebufferStatus(mID, GL_FRAMEBUFFER_COMPLETE);
    }

    bool Framebuffer::tryAttachTexture(Texture& pNewTexture, std::optional<Texture> pOldTexture) {
        glNamedFramebufferTexture(mID, GL_COLOR_ATTACHMENT0, pNewTexture.getID(), 0);

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

    bool Framebuffer::tryAttachRenderbuffer(Renderbuffer &pNewRenderbuffer,
                                            std::optional<Renderbuffer> pOldRenderbuffer) {
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
