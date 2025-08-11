//
// Created by kirut on 7/19/2025.
//


#include "Program.h"
#include "Log.h"
#include <glm/gtc/type_ptr.hpp>
#include <utility>

namespace cglw {
    Program::Program(std::vector<Shader>& pShaders) {
        Log::trace(LOG_TAG, "Creating a new Shader Program");

        if (pShaders.empty()) throw std::invalid_argument("List of Shaders for Shader Program is empty");

        // create
        mID = glCreateProgram();
        if (mID == INVALID_ID) {
            throw std::runtime_error("Failed to create a new Shader Program ID");
        }

        // attach
        for (Shader& shader : pShaders) {
            // Future: check for if one of each is already in
            glAttachShader(mID, shader.getID());
            mShaders.emplace_back(std::move(shader));
        }

        // link
        glLinkProgram(mID);
        { // check
            GLint success;
            glGetProgramiv(mID, GL_LINK_STATUS, &success);
            if (!success) {
                char log[1024];
                glGetProgramInfoLog(mID, sizeof(log), nullptr, log);

                throw std::runtime_error(std::format("Failed to link Shader Program ID: {}\n"
                                                     "\t{}", mID, log));
            }
        }

        Log::debug(LOG_TAG, "Successfully created a new Shader Program, ID: {}", mID);
    }

    Program::~Program() {
        Log::trace(LOG_TAG, "Destroying a Shader Program, ID: {}", mID);

        if (mID != INVALID_ID) glDeleteProgram(mID);

        Log::debug(LOG_TAG, "Successfully destroyed a Shader Program");
    }

    Program::Program(Program &&other) noexcept
    : mShaders(std::move(other.mShaders)), mUniforms(std::move(other.mUniforms)) {
        mID = std::exchange(other.mID, INVALID_ID);

        Log::trace(LOG_TAG, "Moving a Shader Program, ID: {}", mID);
    }

    Program &Program::operator=(Program &&other) noexcept {
        if (this != &other) {
            Log::trace(LOG_TAG, "Moving a Shader Program, ID: {} to Shader Program, ID: {}",
                       mID, other.mID);

            if (mID != INVALID_ID) {
                Log::trace(LOG_TAG, "Destroying a Shader Program, ID: {}", mID);
                glDeleteProgram(mID);
            }

            mShaders = std::move(other.mShaders);
            mUniforms = std::move(other.mUniforms);
            mID = std::exchange(other.mID, INVALID_ID);
        }

        return *this;
    }

    void Program::use() const {
        if (mID == INVALID_ID) {
            Log::warn(LOG_TAG, "Failed to use Shader Program:\n"
                               "\tThis Shader Program is invalid!");
            return;
        }

        glUseProgram(mID);
    }

    void Program::unUse() {
        glUseProgram(0);
    }


    int Program::getUniform(std::string_view name) const {
        auto it = mUniforms.find(name.data());
        if (it != mUniforms.end()) return it->second;

        int location = glGetUniformLocation(mID, name.data());
        mUniforms[name] = location;
        return location;
    }

    void Program::set(std::string_view name, float value) const {
        if (mID == INVALID_ID) {
            Log::warn(LOG_TAG, "Failed to set float uniform for Shader Program:\n"
                               "\tThis Shader Program is invalid!");
            return;
        }

        glUniform1f(getUniform(name), value);
    }

    void Program::set(std::string_view name, int value) const {
        if (mID == INVALID_ID) {
            Log::warn(LOG_TAG, "Failed to set int uniform for Shader Program:\n"
                               "\tThis Shader Program is invalid!");
            return;
        }

        glUniform1i(getUniform(name), value);
    }

    void Program::set(std::string_view name, const glm::vec3 &vec) const {
        if (mID == INVALID_ID) {
            Log::warn(LOG_TAG, "Failed to set Vector3 uniform for Shader Program:\n"
                               "\tThis Shader Program is invalid!");
            return;
        }

        glUniform3fv(getUniform(name), 1, glm::value_ptr(vec));
    }

    void Program::set(std::string_view name, const glm::mat4 &mat) const {
        if (mID == INVALID_ID) {
            Log::warn(LOG_TAG, "Failed to set Matrix uniform for Shader Program:\n"
                               "\tThis Shader Program is invalid!");
            return;
        }

        glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(mat));
    }
} // CE