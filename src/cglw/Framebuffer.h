//
// Created by kirut on 7/22/2025.
//

#ifndef PROJECTTSUNAMIMOONLIGHT_FRAMEBUFFER_H
#define PROJECTTSUNAMIMOONLIGHT_FRAMEBUFFER_H

#include "Object.h"
#include "Renderbuffer.h"
#include "Texture.h"
#include <optional>

namespace cglw {
  class Framebuffer : public Object {
      static constexpr std::string_view LOG_TAG = "cglw::Framebuffer";
      static constexpr int NUM_FBO = 1; // Currently not setup for an array of FBO names

      std::optional<Texture> mTexture = std::nullopt;
      std::optional<Renderbuffer> mRenderbuffer = std::nullopt;

      unsigned int create() override;
      bool tryDestroy();

    public:
      Framebuffer();
      ~Framebuffer();
      // disable copy
      Framebuffer(const Framebuffer&) = delete;
      Framebuffer& operator=(const Framebuffer&) = delete;
      // moving
      Framebuffer(Framebuffer&& other) noexcept;
      Framebuffer& operator=(Framebuffer&& other) noexcept;

      bool isComplete();
      bool tryAttachTexture(Texture& pNewTexture, std::optional<Texture> pOldTexture = std::nullopt);
      bool tryAttachRenderbuffer(Renderbuffer& pNewRenderbuffer, std::optional<Renderbuffer> pOldRenderbuffer = std::nullopt);
  };
} // CE

#endif //PROJECTTSUNAMIMOONLIGHT_FRAMEBUFFER_H
