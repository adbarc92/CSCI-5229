#include "vector4d.h"
#include "lib.h"

namespace vector4d {
Vector4d zeroVert(0, 0, 0);
}
using namespace vector4d;

Vector4d::Vector4d() : x(0), y(0), z(0), w(0) {}
Vector4d::Vector4d(const Vector4d& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
Vector4d::Vector4d(float xA, float yA, float zA, float wA) : x(xA), y(yA), z(zA), w(wA) {}

Vector4d Vector4d::operator=(const Vector4d& v) {
  if (this == &v)
    return *this;
  return Vector4d(v);
}
Vector4d operator+(const Vector4d& a, const Vector4d& b) {
  return Vector4d(b.x + a.x, b.y + a.y, b.z + a.z, b.w + a.w);
}
Vector4d operator-(const Vector4d& a, const Vector4d& b) {
  return Vector4d(b.x - a.x, b.y - a.y, b.z - a.z, b.w - a.w);
}
Vector4d operator*(float mat4[16], const Vector4d& b) {
  Vector4d ret;
  Vector4d::multMat4(b, mat4, ret);
  return ret;
}

float Vector4d::getLength() const {
  return sqrt(x * x + y * y + z * z);
}

void Vector4d::negate() {
  x = -x;
  y = -y;
  z = -z;
}

void Vector4d::norm3() {
  Vector4d::getNormalized3(*this, *this);
}

void Vector4d::rotateByAxis(double angleDeg, const Vector4d& axis) {

  double ca = Cos(angleDeg);
  double sa = Sin(angleDeg);
  Vector4d cross;
  Vector4d::getCrossProduct(*this, axis, cross);
  double dot = Vector4d::getDotProduct(*this, axis);
  double rx = x * ca + cross.x * sa + dot * axis.x * (1 - ca);
  double ry = y * ca + cross.y * sa + dot * axis.y * (1 - ca);
  double rz = z * ca + cross.z * sa + dot * axis.z * (1 - ca);
  x = rx;
  y = ry;
  z = rz;
}

void Vector4d::getNormalized3(const Vector4d& vec, Vector4d& out) {
  if (vec.x == 0 && vec.y == 0 && vec.z == 0) {
    out.x = 0;
    out.y = 0;
    out.z = 0;
    return;
  }
  float len = vec.getLength();
  out.x = vec.x / len;
  out.y = vec.y / len;
  out.z = vec.z / len;
}

void Vector4d::getCrossProduct(const Vector4d& vec, const Vector4d& other, Vector4d& out) {
  out.x = vec.y * other.z - vec.z * other.y;
  out.y = vec.z * other.x - vec.x * other.z;
  out.z = vec.x * other.y - vec.y * other.x;
}
void Vector4d::getCrossProductNormalized(const Vector4d& vec, const Vector4d& other, Vector4d& out) {
  Vector4d::getCrossProduct(vec, other, out);
  out.norm3();
}
double Vector4d::getDotProduct(const Vector4d& vec, const Vector4d& other) {
  Vector4d normThis;
  Vector4d normOther;

  Vector4d::getNormalized3(vec, normThis);
  Vector4d::getNormalized3(other, normOther);
  return normThis.x * normOther.x + normThis.y * normOther.y + normThis.z * normOther.z;
}
void Vector4d::multMat4(const Vector4d& vec, float mat4[16], Vector4d& out) {
  double x[4] = {vec.x, vec.y, vec.z, vec.w};
  double b[4];
  int i, j;
  for (i = 0; i < 4; i++) {
    b[i] = 0;

    for (j = 0; j < 4; j++) {
      b[i] += x[j] * mat4[(j * 4) + i];
    }
  }
  out.x = b[0];
  out.y = b[1];
  out.z = b[2];
  out.w = b[3];
}

void Vector4d::calcNormal(const Vector4d& v1, const Vector4d& v2, const Vector4d& v3, Vector4d& out) {
  Vector4d v1ToV2 = v2 - v1;
  Vector4d v2ToV3 = v3 - v2;
  Vector4d::getCrossProductNormalized(v1ToV2, v2ToV3, out);
}
void Vector4d::orthoNormalize(Vector4d& normal, Vector4d& tangent) {
	normal.norm3();
	tangent.norm3();
	Vector4d::getCrossProduct(tangent, normal, tangent);
}
