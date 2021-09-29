#include "lib.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <unordered_map>

namespace lib {
std::unordered_map<std::string, std::unique_ptr<Vector3d>> colors;
std::unordered_map<unsigned char, bool> keys;
Vector3d zeroVert(0, 0, 0);
}

using namespace lib;

void initColors() {
  colors["green"] = std::make_unique<Vector3d>(0, 1, 0);
  colors["darkgreen"] = std::make_unique<Vector3d>(0, 0.5, 0);
  colors["red"] = std::make_unique<Vector3d>(1, 0, 0);
  colors["darkred"] = std::make_unique<Vector3d>(0.5, 0, 0);
  colors["blue"] = std::make_unique<Vector3d>(0, 0, 1);
  colors["darkblue"] = std::make_unique<Vector3d>(0, 0, 0.5);
  colors["white"] = std::make_unique<Vector3d>(1, 1, 1);
  colors["darkwhite"] = std::make_unique<Vector3d>(0.95, 0.95, 0.95);
  colors["black"] = std::make_unique<Vector3d>(0.05, 0.05, 0.05);
  colors["darkblack"] = std::make_unique<Vector3d>(0, 0, 0);
  colors["orange"] = std::make_unique<Vector3d>(1, 0.5, 0);
  colors["darkorange"] = std::make_unique<Vector3d>(0.5, 0.25, 0);
  colors["yellow"] = std::make_unique<Vector3d>(1, 1, 0);
  colors["darkyellow"] = std::make_unique<Vector3d>(0.5, 0.5, 0);
  colors["purple"] = std::make_unique<Vector3d>(1, 0, 1);
  colors["darkpurple"] = std::make_unique<Vector3d>(0.5, 0, 0.5);
  colors["gray"] = std::make_unique<Vector3d>(0.3, 0.3, 0.3);
  colors["darkgray"] = std::make_unique<Vector3d>(0.15, 0.15, 0.15);
}

Vector3d::Vector3d() : x(0), y(0), z(0) {}

Vector3d::Vector3d(float xA, float yA, float zA) : x(xA), y(yA), z(zA) {}

float Vector3d::getLength() {
  return sqrt(x * x + y * y + z * z);
}

void Vector3d::getNormalized(Vector3d& out) {
  if (x == 0 && y == 0 && z == 0) {
    out.x = 0;
    out.y = 0;
    out.z = 0;
    return;
  }
  float len = getLength();
  out.x = x / len;
  out.y = y / len;
  out.z = z / len;
}

void Vector3d::getCrossProduct(Vector3d& other, Vector3d& out) {
  out.x = y * other.z - z * other.y;
  out.y = z * other.x - x * other.z;
  out.z = x * other.y - y * other.x;
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

Vector3d& getColor(const std::string& name) {
  if (colors.find(name) != colors.end()) {
    return *colors[name].get();
  } else {
    return *colors["white"].get();
  }
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

void rotateVec3d(Vector3d& vert, Vector3d& axis, double angleDeg) {
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
