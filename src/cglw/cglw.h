//
// Created by kirut on 8/6/2025.
//

#ifndef CGL_LOADER_H
#define CGL_LOADER_H

#include <string_view>
#include "Log.h"

namespace cglw {
    struct CGLWSettings {
        bool useDSA; // enables Direct State Access instead of binds
        std::function<void(Log::Type, std::string_view, std::string)> logCallback = nullptr; // providing enables logs
        bool enableDebugLogs;
        bool enableOpenGLLogs; // must have logs enabled
    };

    using getGLFunction = GLADloadfunc;
    static bool load(getGLFunction pLoadFunc, CGLWSettings &pSettings);

}// namespace CGL

#endif//CGL_LOADER_H
