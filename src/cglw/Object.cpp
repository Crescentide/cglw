//
// Created by kirut on 8/6/2025.
//

#include "Object.h"
#include "Log.h"

namespace cglw {
Object::Object() : mID(INVALID_ID), mGLType(ObjectType::Invalid) {
//  Log::debug(LOG_TAG, "Created {} with ID: ", typeToStr(mGLType), mID);
}

Object::Object(unsigned int pID, ObjectType pType) : mID(pID), mGLType(pType) {
  Log::debug(LOG_TAG, "Created {} with ID: ", typeToStr(mGLType), mID);
}
Object::~Object() {
  tryDestroy();
}
Object::Object(Object &&other) noexcept : mID(other.mID), mGLType(other.mGLType) {
  other.mID = INVALID_ID;
  other.mGLType = ObjectType::Invalid;
}
Object &Object::operator=(Object &&other) noexcept {
  if (this != &other) {
    mID = other.mID;
    mGLType = other.mGLType;

    other.mID = INVALID_ID;
    other.mGLType = ObjectType::Invalid;
  }

  return *this;
}
bool Object::tryDestroy() {
  if (mID == INVALID_ID) return false;

  Log::debug(LOG_TAG, "Destroying {} with ID: {}", typeToStr(mGLType), mID);

  mID = INVALID_ID;
  mGLType = ObjectType::Invalid;

  return true;
}

void Object::invalidate() {
  if (!isValid()) {
    Log::error(LOG_TAG,
              "User misapplication:\n"
              "\tDouble invalidation or already invalid {}",
              typeToStr(mGLType));
    return;
  }

  tryDestroy();
}

std::string Object::typeToStr(ObjectType pType) {
  switch (pType) {
  case ObjectType::Invalid:
    return "Invalid OpenGL Object";
  case ObjectType::Buffer:
      return "cglw::Buffer";
  case ObjectType::Framebuffer:
    return "cglw::Framebuffer";
  case ObjectType::Program:
    return "cglw::Program";
  case ObjectType::Renderbuffer:
    return "cglw::Renderbuffer";
  case ObjectType::Shader:
    return "cglw::Shader";
  case ObjectType::Texture:
    return "cglw::Texture";
  case ObjectType::VertexArray:
    return "cglw::VertexArray";
  default:
    return "Invalid";
  }
}

} // namespace CE