//
// Created by kirut on 7/19/2025.
//


#include "Program.h"
#include "Log.h"
#include <glm/gtc/type_ptr.hpp>

namespace cglw {
    Program::Program() : Object(create(), Object::Type::Program) {

    }

    Program::~Program() {
        tryDestroy();
    }

    Program::Program(Program &&other) noexcept
    : Object(std::move(other)), shaders(std::move(other.shaders)) {

    }

    Program &Program::operator=(Program &&other) noexcept {
        if (this != &other) {
            tryDestroy();

            Object::operator=(std::move(other));
            shaders = std::move(other.shaders);
            uniforms = std::move(other.uniforms);

            // TODO: clear shaders
        }

        return *this;
    }

    void Program::attachShader(const Shader &shader) {
        glAttachShader(mID, shader.getID());
//        shaders.emplace_back(shader); // TODO:
    }

    bool Program::link() const {
        glLinkProgram(mID);

        GLint success;
        glGetProgramiv(mID, GL_LINK_STATUS, &success);
        if (!success) {
            char log[1024];
            glGetProgramInfoLog(mID, sizeof(log), nullptr, log);

            Log::error(LOG_TAG, "Failed to link OpenGL Shader Program:\n"
                                "\t{}", log);

            return false;
        }

        return true;
    }

    void Program::use() const {
        glUseProgram(mID);
    }

    void Program::unUse() {
        glUseProgram(0);
    }

    void Program::set(std::string_view name, float value) const {
        glUniform1f(getUniform(name), value);
    }

    int Program::getUniform(std::string_view name) const {
        auto it = uniforms.find(name.data());
        if (it != uniforms.end()) return it->second;

        int location = glGetUniformLocation(mID, name.data());
        uniforms[name] = location;
        return location;
    }

    void Program::set(std::string_view name, int value) const {
        glUniform1i(getUniform(name), value);
    }

    void Program::set(std::string_view name, const glm::vec3 &vec) const {
        glUniform3fv(getUniform(name), 1, glm::value_ptr(vec));
    }

    void Program::set(std::string_view name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    unsigned int Program::create() {
        unsigned int program = INVALID_ID;

        program = glCreateProgram();
        if (program == INVALID_ID) {
            Log::warn(LOG_TAG, "Failed to create a new Shader Program");
        }

        return program;
    }
    bool Program::tryDestroy() {
        if (mID == INVALID_ID) return false;

        glDeleteProgram(mID);

        return true;
    }


} // CE