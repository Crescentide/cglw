//
// Created by kirut on 7/22/2025.
//

#ifndef PROJECTTSUNAMIMOONLIGHT_UNIFORMBUFFER_H
#define PROJECTTSUNAMIMOONLIGHT_UNIFORMBUFFER_H

#include <glad/gl.h>

namespace cglw {
    struct UBOBindingAllocator {
        static unsigned int next() {
            static unsigned int index = 0;
            return index++;
        }
    };

    template<typename T>
    class UniformBuffer {
        unsigned int binding = 0;
        unsigned int id = 0;
        size_t size;

    public:
        UniformBuffer();
        ~UniformBuffer();
        // disable copy
        UniformBuffer(const UniformBuffer&) = delete;
        UniformBuffer& operator=(const UniformBuffer&) = delete;
        // moving
        UniformBuffer(UniformBuffer&& other) noexcept;
        UniformBuffer& operator=(UniformBuffer&& other) noexcept;

        void update(const T& data);
        void bind() const;
        void unbind();

    };

    template<typename T>
    void UniformBuffer<T>::unbind() {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    template<typename T>
    void UniformBuffer<T>::bind() const {
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, id);
    }

    template<typename T>
    void UniformBuffer<T>::update(const T &data) {
        glBindBuffer(GL_UNIFORM_BUFFER, id);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, size, &data);
    }

    template<typename T>
    UniformBuffer<T> &UniformBuffer<T>::operator=(UniformBuffer<T> &&other) noexcept {
        if (this != &other) {
            glDeleteBuffers(1, &id);

            id = other.id;
            size = other.size;
            binding = other.binding;

            other.id = 0;
            other.binding = 0;
        }

        return *this;
    }

    template<typename T>
    UniformBuffer<T>::UniformBuffer(UniformBuffer<T> &&other) noexcept
    : id(other.id), size(other.size), binding(other.binding) {
        other.id = 0;
        other.binding = 0;
    }

    template<typename T>
    UniformBuffer<T>::~UniformBuffer() {
        glDeleteBuffers(1, &id);
    }

    template<typename T>
    UniformBuffer<T>::UniformBuffer() : binding(UBOBindingAllocator::next()), size(sizeof(T)) {

        glGenBuffers(1, &id);
        glBindBuffer(GL_UNIFORM_BUFFER, id);
        glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
        glBindBufferRange(GL_UNIFORM_BUFFER, binding, id, 0, size);
    }
} // CE

#endif //PROJECTTSUNAMIMOONLIGHT_UNIFORMBUFFER_H
