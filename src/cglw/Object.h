//
// Created by kirut on 8/6/2025.
//

#ifndef PROJECTTSUNAMIMOONLIGHT_OBJECT_H
#define PROJECTTSUNAMIMOONLIGHT_OBJECT_H

#include <unordered_map>
#include <string>

namespace cglw {

enum class ObjectType {
  Invalid,
  Buffer,
  Framebuffer,
  Program,
  Renderbuffer,
  Shader,
  Texture,
  VertexArray
};

class Object {
  static constexpr std::string_view LOG_TAG = "cglw::Object";
//  static std::unordered_map<ObjectType, unsigned int> bounded;

  bool tryDestroy();
  static std::string typeToStr(ObjectType pType);

protected:
  static constexpr unsigned int INVALID_ID = 0;

  unsigned int mID;
  ObjectType mGLType;

  virtual unsigned int create() = 0;
  virtual void invalidate();

public:
  using Type = ObjectType;

  Object();
  explicit Object(unsigned int pID, ObjectType pType);
  ~Object();
  // disable copy
  Object(const Object&) = delete;
  Object& operator=(const Object&) = delete;
  // moving
  Object(Object&& other) noexcept;
  Object& operator=(Object&& other) noexcept;

  [[nodiscard]] unsigned int getID() const { return mID; };
  [[nodiscard]] bool isValid() const { return mID != INVALID_ID; };


};

} // namespace CE

#endif // PROJECTTSUNAMIMOONLIGHT_OBJECT_H
