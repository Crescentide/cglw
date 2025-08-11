//
// Created by kirut on 8/6/2025.
//

#ifndef CGLW_LOADER_H
#define CGLW_LOADER_H

#include <string_view>
#include "Log.h"
#include "glad/gl.h"

namespace cglw {
    using getGLFunction = GLADloadfunc;

    struct Settings {
        getGLFunction loadFunc;
        std::function<void(Log::Type, std::string_view, std::string)> logCallback = nullptr; // providing enables logs
        Log::Flags enabledLogs; // must have provided log callback
    };

    bool load(Settings &pSettings);

}// namespace CGLW

#endif//CGLW_LOADER_H
