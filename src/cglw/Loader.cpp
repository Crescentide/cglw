//
// Created by kirut on 8/6/2025.
//

#include "cglw.h"

namespace cglw {
    static constexpr std::string_view LOG_TAG = "cglw";

    bool load(Settings &pSettings) {
        if (pSettings.logCallback)
            Log::enable(pSettings.logCallback, pSettings.enabledLogs);

        int version = gladLoadGL(pSettings.loadFunc);
        if (!version) {
            Log::critical(LOG_TAG, "Failed to initialize Crescentide OpenGL Wrapper:\n"
                                   "\tGLAD failed to load OpenGL functions!");
            return false;
        }

        Log::info(LOG_TAG,
                   "Loaded OpenGL {}.{}\n"
                   "\tVendor: {}\n"
                   "\tRenderer: {}\n"
                   "\tVersion: {}",
                   GLAD_VERSION_MAJOR(version),
                   GLAD_VERSION_MINOR(version),
                   reinterpret_cast<const char*>(glGetString(GL_VENDOR)),
                   reinterpret_cast<const char*>(glGetString(GL_RENDERER)),
                   reinterpret_cast<const char*>(glGetString(GL_VERSION)));

        // shit

        return true;
    }
}// namespace CGL