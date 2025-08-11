//
// Created by kirut on 8/6/2025.
//

#ifndef CGLW_OBJECT_H
#define CGLW_OBJECT_H

#include <string>

namespace cglw {
    // This really just reduces boilerplate for the rest of OpenGL objects and provides info on the types of methods to implement
    class Object {
        static constexpr std::string_view LOG_TAG = "cglw::Object";

    protected:
        using ID = unsigned int;
        static constexpr ID INVALID_ID = 0;

        ID mID = INVALID_ID;

    public:
        Object() = default;
        virtual ~Object() = default;
        // moving
        Object(Object&& other) noexcept = default;
        Object& operator=(Object&& other) noexcept = default;

        [[nodiscard]] unsigned int getID() const { return mID; };
    };
} // namespace CE

#endif // CGLW_OBJECT_H
