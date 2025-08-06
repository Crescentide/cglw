//
// Created by kirut on 8/6/2025.
//

#include "cglw.h"

namespace cglw {
    static constexpr std::string_view LOG_TAG = "cglw";

    bool load(getGLFunction pLoadFunc, CGLWSettings &pSettings) {
        if (pSettings.logCallback)
            Log::enable(pSettings.logCallback);

        int version = gladLoadGL(pLoadFunc);
        if (!version) {
            Log::critical(LOG_TAG, "Failed to initialize Crescentide OpenGL Wrapper:\n"
                                   "\tGLAD failed to load OpenGL functions!");
            return false;
        }

        Log::debug(LOG_TAG,
                   "Loaded OpenGL {}.{}\n"
                   "\tVendor: {}\n"
                   "\tRenderer: {}\n"
                   "\tVersion: {}",
                   GLAD_VERSION_MAJOR(version),
                   GLAD_VERSION_MINOR(version),
                   reinterpret_cast<const char*>(glGetString(GL_VENDOR)),
                   reinterpret_cast<const char*>(glGetString(GL_RENDERER)),
                   reinterpret_cast<const char*>(glGetString(GL_VERSION)));



        return true;
    }
}// namespace CGL