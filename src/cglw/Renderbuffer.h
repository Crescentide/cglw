//
// Created by kirut on 8/3/2025.
//

#ifndef PROJECTTSUNAMIMOONLIGHT_RENDERBUFFER_H
#define PROJECTTSUNAMIMOONLIGHT_RENDERBUFFER_H

#include "Object.h"
#include "glm/fwd.hpp"
#include <glm/vec2.hpp>
#include <string_view>

namespace cglw {

    class Renderbuffer : public Object {
        static constexpr std::string_view LOG_TAG = "cglw::Renderbuffer";
        static constexpr int NUM_RBO = 1;

        unsigned int create() override;
        bool tryDestroy();

    public:
        Renderbuffer();
        ~Renderbuffer();
        // disable copy
        Renderbuffer(const Renderbuffer&) = delete;
        Renderbuffer& operator=(const Renderbuffer&) = delete;
        // moving
        Renderbuffer(Renderbuffer&& other) noexcept;
        Renderbuffer& operator=(Renderbuffer&& other) noexcept;

        void bind() const;
        void unbind() const;
        void setStorage(const glm::ivec2& pSize) const;
    };

} // namespace CE

#endif // PROJECTTSUNAMIMOONLIGHT_RENDERBUFFER_H
