#pragma once

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <IL/il.h>
#include <IL/ilu.h>

#include <cmath>
#include <cstdarg>
#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#ifndef Cos
#define Cos(th) cos(3.1415926 / 180 * (th))
#define Sin(th) sin(3.1415926 / 180 * (th))
#define Vector3dARGS(v) v.x, v.y, v.z

#define KEY_RIGHT 230
#define KEY_LEFT 231
#define KEY_UP 232
#define KEY_DOWN 233
#define KEY_MOUSE_LEFT 234
#define KEY_MOUSE_RIGHT 235

#endif

class Vector4d;

struct Texture {
  GLuint textureId;
  int width;
  int height;
  Texture();
  ~Texture();

  void load(const std::string& filename);
  void bind();
  void unbind();
};

void print(const char* format, ...);

static inline double normalize(double x, double a, double b, double c, double d) {
  return c + (x - a) * (d - c) / (b - a);
};

void initLib();
Vector4d& getColor(const std::string& name);
Texture& getTexture(const std::string& name);
void loadTexture(const std::string& name, const std::string& path);
void setKeyDown(unsigned char ch);
void unsetKeyDown(unsigned char ch);
bool isKeyDown(unsigned char ch);
void setKeyDown(unsigned char ch);
void rotateVector3d(Vector4d& vert, Vector4d& axis, double angleDeg);