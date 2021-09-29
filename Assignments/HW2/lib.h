#pragma once

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <cstdarg>
#include <cmath>

#ifndef Cos
#define Cos(th) cos(3.1415926 / 180 * (th))
#define Sin(th) sin(3.1415926 / 180 * (th))
#define VEC3DARGS(v) v.x, v.y, v.z
#endif
struct Vector3d {
  float x;
  float y;
  float z;
  Vector3d();
  Vector3d(float xA, float yA, float zA);
  float getLength();
  void getNormalized(Vector3d& out);
  void getCrossProduct(Vector3d& other, Vector3d& out);
};

void print(const char* format, ...);

static inline double normalize(double x, double a, double b, double c, double d) {
  return c + (x - a) * (d - c) / (b - a);
};

void initColors();
Vector3d& getColor(const std::string& name);
void setKeyDown(unsigned char ch);
void unsetKeyDown(unsigned char ch);
bool isKeyDown(unsigned char ch);
void setKeyDown(unsigned char ch);
void rotateVec3d(Vector3d& vert, Vector3d& axis, double angleDeg);