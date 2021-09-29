#pragma once

struct Vector4d {
  float x;
  float y;
  float z;
  float w;
  Vector4d();
  Vector4d(const Vector4d& v);
  Vector4d(float xA, float yA, float zA, float wA = 0.0);

  Vector4d operator= (const Vector4d& v);
  friend Vector4d operator+ (const Vector4d& a, const Vector4d& b);
  friend Vector4d operator- (const Vector4d& a, const Vector4d& b);
  friend Vector4d operator* (float mat4[16], const Vector4d& b);

  float getLength() const;
  void negate();
	void norm3();
	void rotateByAxis(double angleDeg, const Vector4d& axis);

  static void getNormalized3(const Vector4d& vec, Vector4d& out);
  static void getCrossProduct(const Vector4d& vec, const Vector4d& other, Vector4d& out);
  static void getCrossProductNormalized(const Vector4d& vec, const Vector4d& other, Vector4d& out);
  static double getDotProduct(const Vector4d& vec, const Vector4d& other);
  static void multMat4(const Vector4d& vec, float mat4[16], Vector4d& out);
	static void calcNormal(const Vector4d& v1, const Vector4d& v2, const Vector4d& v3, Vector4d& out);
	static void orthoNormalize(Vector4d& normal, Vector4d& tangent);
};
