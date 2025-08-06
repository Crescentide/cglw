//
// Created by kirut on 7/19/2025.
//

#ifndef PROJECTTSUNAMIMOONLIGHT_PROGRAM_H
#define PROJECTTSUNAMIMOONLIGHT_PROGRAM_H

#include "Object.h"
#include "Shader.h"
#include "glm/fwd.hpp"
#include "glm/vec3.hpp"
#include <string>
#include <string_view>

namespace cglw {
    class Program : public Object {
      static constexpr std::string_view LOG_TAG = "cglw::Program";

      std::vector<Shader> shaders;
      mutable std::unordered_map<std::string_view, int> uniforms;

      unsigned int create() override;
      bool tryDestroy();
      virtual void invalidate() override;

    public:
        Program();
        ~Program();
        // disable copy
        Program(const Program&) = delete;
        Program& operator=(const Program&) = delete;
        // moving
        Program(Program&& other) noexcept;
        Program& operator=(Program&& other) noexcept;

        void attachShader(const Shader& shader);
        [[nodiscard]] bool link() const;


        void use() const;
        static void unUse();

        int getUniform(std::string_view name) const;
        void set(std::string_view name, float value) const;
        void set(std::string_view name, int value) const;
        void set(std::string_view name, const glm::vec3& vec) const;
        void set(std::string_view name, const glm::mat4& mat) const;
    };
} // CE

#endif //PROJECTTSUNAMIMOONLIGHT_PROGRAM_H