#include "lib.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "vector4d.h"

// private globals in namespace to prevent collisions
namespace lib {
std::unordered_map<std::string, std::unique_ptr<Vector4d>> colors;
std::unordered_map<unsigned char, bool> keys;
std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
Texture zeroTex = Texture();
void loadTextureFromPixels32(GLuint* pixels, int width, int height);
}

using namespace lib;

void initLib() {

  colors["green"] = std::make_unique<Vector4d>(0, 1, 0);
  colors["darkgreen"] = std::make_unique<Vector4d>(0, 0.5, 0);
  colors["red"] = std::make_unique<Vector4d>(1, 0, 0);
  colors["darkred"] = std::make_unique<Vector4d>(0.5, 0, 0);
  colors["blue"] = std::make_unique<Vector4d>(0, 0, 1);
  colors["darkblue"] = std::make_unique<Vector4d>(0, 0, 0.5);
  colors["white"] = std::make_unique<Vector4d>(1, 1, 1);
  colors["darkwhite"] = std::make_unique<Vector4d>(0.95, 0.95, 0.95);
  colors["black"] = std::make_unique<Vector4d>(0.05, 0.05, 0.05);
  colors["darkblack"] = std::make_unique<Vector4d>(0, 0, 0);
  colors["orange"] = std::make_unique<Vector4d>(1, 0.5, 0);
  colors["darkorange"] = std::make_unique<Vector4d>(0.5, 0.25, 0);
  colors["yellow"] = std::make_unique<Vector4d>(1, 1, 0);
  colors["darkyellow"] = std::make_unique<Vector4d>(0.5, 0.5, 0);
  colors["purple"] = std::make_unique<Vector4d>(1, 0, 1);
  colors["darkpurple"] = std::make_unique<Vector4d>(0.5, 0, 0.5);
  colors["gray"] = std::make_unique<Vector4d>(0.3, 0.3, 0.3);
  colors["darkgray"] = std::make_unique<Vector4d>(0.15, 0.15, 0.15);
  colors["gold"] = std::make_unique<Vector4d>(0.8, 0.498039, 0.196078);
}

Texture::Texture() : textureId(0) {}

Texture::~Texture() {
  if (textureId != 0) {
    // glDeleteTextures(1, &textureId);
    textureId = 0;
  }
}

void Texture::load(const std::string& path) {
  bool textureLoaded = true;
  ILuint imgId = 0;
  ilGenImages(1, &imgId);
  ilBindImage(imgId);
  ILboolean success = ilLoadImage(path.c_str());
  if (success == IL_TRUE) {
    success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    if (success == IL_TRUE) {
      GLuint* pixels = (GLuint*)ilGetData();
      width = ilGetInteger(IL_IMAGE_WIDTH);
      height = ilGetInteger(IL_IMAGE_HEIGHT);
      glGenTextures(1, &textureId);
      glBindTexture(GL_TEXTURE_2D, textureId);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
      glBindTexture(GL_TEXTURE_2D, 0);
      GLenum error = glGetError();
      if (error != GL_NO_ERROR) {
        textureLoaded = false;
        std::cout << "Error? " << error << std::endl;
      }
    }
    ilDeleteImages(1, &imgId);
  }

  if (!textureLoaded) {
    std::cout << "Could not load texture: " << path << std::endl;
  }
}

void Texture::bind() {
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unbind() {
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}

void print(const char* format, ...) {
  char buf[8192];
  char* ch = buf;
  va_list args;
  va_start(args, format);
  vsnprintf(buf, 8192, format, args);
  va_end(args);
  while (*ch)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *ch++);
}

Vector4d& getColor(const std::string& name) {
  if (colors.find(name) != colors.end()) {
    return *colors[name].get();
  } else {
    return *colors["white"].get();
  }
}

Texture& getTexture(const std::string& name) {
  if (textures.find(name) != textures.end()) {
    return *textures[name].get();
  } else {
    return zeroTex;
  }
}

void loadTexture(const std::string& name, const std::string& path) {
  Texture* t = new Texture();
  t->load(path);
  textures[name] = std::unique_ptr<Texture>(t);

  std::cout << "[lib] Loaded texture: " << name << ":" << path << std::endl;
}

void setKeyDown(unsigned char ch) {
  keys[ch] = true;
}

void unsetKeyDown(unsigned char ch) {
  keys[ch] = false;
}

bool isKeyDown(unsigned char ch) {
  if (keys.find(ch) != keys.end()) {
    return keys[ch];
  } else {
    return false;
  }
}

void rotateVector3d(Vector4d& vert, Vector4d& axis, double angleDeg) {
  double vx = vert.x;
  double vy = vert.y;
  double vz = vert.z;
  double ax = axis.x;
  double ay = axis.y;
  double az = axis.z;
  double ca = Cos(angleDeg);
  double sa = Sin(angleDeg);
  double crossx = -vy * az + vz * ay;
  double crossy = -vz * ax + vx * az;
  double crossz = -vx * ay + vy * ax;
  double dot = ax * vx + ay * vy + az * vz;
  double rx = vx * ca + crossx * sa + dot * ax * (1 - ca);
  double ry = vy * ca + crossy * sa + dot * ay * (1 - ca);
  double rz = vz * ca + crossz * sa + dot * az * (1 - ca);
  vert.x = rx;
  vert.y = ry;
  vert.z = rz;
}
