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
        static constexpr int NUM_RBOS = 1;

    public:
        Renderbuffer();
        ~Renderbuffer() override;
        // moving
        Renderbuffer(Renderbuffer&& other) noexcept;
        Renderbuffer& operator=(Renderbuffer&& other) noexcept;

        void setStorage(const glm::ivec2& pSize) const;
    };

} // namespace CE

#endif // PROJECTTSUNAMIMOONLIGHT_RENDERBUFFER_H
