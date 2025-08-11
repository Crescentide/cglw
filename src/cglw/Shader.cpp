//
// Created by kirut on 1/18/2025.
//

#include "Shader.h"
#include "Log.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>


namespace cglw {
    Shader::Shader(Type pType, std::string_view pPath) : mType(pType) {
        Log::trace(LOG_TAG, "Creating a new {} Shader from path: {}", typeToStr(mType), pPath);

        std::ifstream file(pPath.data());
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        std::stringstream sourceStream;
        sourceStream << file.rdbuf();
        std::string sourceStr = sourceStream.str();
        const char* source = sourceStr.c_str();

        glShaderSource(mID, 1, &source, nullptr);

        glCompileShader(mID);
        {
            GLint success = 0;
            glGetShaderiv(mID, GL_COMPILE_STATUS, &success);
            if (success == GL_FALSE) {
                char infoLog[1024];
                glGetShaderInfoLog(mID, 1024, nullptr, infoLog);

                throw std::runtime_error(std::format("Failed to compile Shader:\n"
                                                     "\t{}", infoLog));
            }
        }

        Log::debug(LOG_TAG, "Successfully created a {} Shader, ID: {}", typeToStr(mType), mID);
    }

    Shader::~Shader() {
        Log::trace(LOG_TAG, "Destroying a {} Shader, ID: {}", typeToStr(mType), mID);

        if (mID != INVALID_ID) glDeleteShader(mID);

        Log::debug(LOG_TAG, "Successfully destroyed a Shader");
    }

    Shader::Shader(Shader &&other) noexcept : mType(other.mType) {
        mID = std::exchange(other.mID, INVALID_ID);

        Log::trace(LOG_TAG, "Moving a {} Shader, ID: {}", typeToStr(mType), mID);
    }

    Shader &Shader::operator=(Shader &&other) noexcept {
        if (this != &other) {
            Log::trace(LOG_TAG, "Moving a {} Shader, ID: {} to a {} Shader, ID: {}", typeToStr(mType), mID, typeToStr(other.mType), other.mID);

            if (mID != INVALID_ID) {
                Log::trace(LOG_TAG, "Destroying a {} Shader, ID: {}", typeToStr(mType), mID);
                glDeleteShader(mID);
            }

            mType = other.mType;
            mID = std::exchange(other.mID, INVALID_ID);
        }

        return *this;
    }
    constexpr std::string_view Shader::typeToStr(ShaderType pType) {
        switch (pType) {
            case ShaderType::Vertex: return "Vertex";
            case ShaderType::Fragment: return "Fragment";
            case ShaderType::Geometry: return "Geometry";
        }
    }
} // Engine