//
// Created by kirut on 1/18/2025.
//

#include "Shader.h"
#include "Log.h"
#include <fstream>
#include <iostream>
#include <sstream>


namespace cglw {
    Shader::Shader(Type pType, std::string_view pPath)
    : mType(pType), Object(create(), Object::Type::Shader) {
        std::ifstream file(pPath.data());
        if (!file.is_open()) {
            Log::error(LOG_TAG, "Failed to open file:\n"
                              "\t{}",
                       pPath);
        }

        std::stringstream sourceStream;
        sourceStream << file.rdbuf();
        std::string sourceStr = sourceStream.str();
        const char* source = sourceStr.c_str();

        glShaderSource(mID, 1, &source, nullptr);
        glCompileShader(mID);

        GLint success = 0;
        glGetShaderiv(mID, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            char infoLog[1024];
            glGetShaderInfoLog(mID, 1024, nullptr, infoLog);

            Log::error(LOG_TAG, "Failed to compile shader for file:\n"
                                "\t{}\n"
                                "\tGL Log: {}",
                       pPath, infoLog);
        }
    }

    Shader::~Shader() {
        tryDestroy();
    }

    Shader::Shader(Shader &&other) noexcept : mType(other.mType), Object(std::move(other)) {

    }

    Shader &Shader::operator=(Shader &&other) noexcept {
        if (this != &other) {
            tryDestroy();

            Object::operator=(std::move(other));
            mType = other.mType;

        }

        return *this;
    }


    unsigned int cglw::Shader::create() {
        unsigned int shader = INVALID_ID;

        shader = glCreateShader(static_cast<GLenum>(mType));
        if (shader == 0) {
            Log::error(LOG_TAG, "Failed to create a new Shader from file");
        }

        return shader;
    }
    bool Shader::tryDestroy() {
        if (mID == INVALID_ID) return false;

        glDeleteShader(mID);

        return true;
    }
} // Engine