#include "objects.h"
#include "lib.h"

namespace objects {
double th = 0;
int granularity = 12;
}
using namespace objects;

void floor() {
  glPushMatrix();

  glBegin(GL_QUADS);
  glVertex3f(-1, +0, -1);
  glVertex3f(-1, +0, +1);
  glVertex3f(+1, +0, +1);
  glVertex3f(+1, +0, -1);
  glEnd();

  glPopMatrix();
}

void cube() {
  for (int i = 0; i < 4; i++) {
    glPushMatrix();
    glRotated(90 * i, 0, 1, 0);

    glBegin(GL_QUADS);
    glVertex3f(-1.0, -1.0, +1.0);
    glVertex3f(+1.0, -1.0, +1.0);
    glVertex3f(+1.0, +1.0, +1.0);
    glVertex3f(-1.0, +1.0, +1.0);
    glEnd();

    glPopMatrix();
  }

  glPushMatrix();

  glBegin(GL_QUADS);
  glVertex3f(-1.0, -1.0, +1.0);
  glVertex3f(+1.0, -1.0, +1.0);
  glVertex3f(+1.0, -1.0, -1.0);
  glVertex3f(-1.0, -1.0, -1.0);

  glVertex3f(-1.0, 1.0, +1.0);
  glVertex3f(+1.0, 1.0, +1.0);
  glVertex3f(+1.0, 1.0, -1.0);
  glVertex3f(-1.0, 1.0, -1.0);
  glEnd();

  glPopMatrix();
}

void circle() {
  double angle = normalize(1, 0, granularity, 0, 360);
  glBegin(GL_TRIANGLE_STRIP);
  for (double i = 0; i <= granularity; i++) {
    double x = Cos(angle * i);
    double z = Sin(angle * i);
    glVertex3f(x, +0, z);
    glVertex3f(+0, +0, +0);
  }
  glEnd();
}

void cylinder() {
  double angle = normalize(1, 0, granularity, 0, 360);
  glBegin(GL_QUAD_STRIP);
  for (int i = 0; i <= granularity; i++) {
    double x = Cos(angle * i);
    double z = Sin(angle * i);
    glVertex3f(x, -1, z);
    glVertex3f(x, +1, z);
  }
  glEnd();
}

void cone() {
  double angle = normalize(1, 0, granularity, 0, 360);
  glBegin(GL_TRIANGLE_STRIP);
  for (int i = 0; i <= granularity; i++) {
    double x = Cos(angle * i);
    double z = Sin(angle * i);
    glVertex3f(x, +0, z);
    glVertex3f(+0, +1, +0);
  }
  glEnd();
}

void trapezoidalPyramid() {
  for (int i = 0; i < 4; i++) {
    glPushMatrix();
    glRotated(90 * i, 0, 1, 0);

    glBegin(GL_QUADS);
    glVertex3f(-1.0, -1.0, +1.0);
    glVertex3f(+1.0, -1.0, +1.0);
    glVertex3f(+0.5, +1.0, +0.5);
    glVertex3f(-0.5, +1.0, +0.5);
    glEnd();

    glPopMatrix();
  }

  glPushMatrix();

  glBegin(GL_QUADS);
  glVertex3f(-1.0, -1.0, +1.0);
  glVertex3f(+1.0, -1.0, +1.0);
  glVertex3f(+1.0, -1.0, -1.0);
  glVertex3f(-1.0, -1.0, -1.0);

  glVertex3f(-0.5, 1.0, +0.5);
  glVertex3f(+0.5, 1.0, +0.5);
  glVertex3f(+0.5, 1.0, -0.5);
  glVertex3f(-0.5, 1.0, -0.5);
  glEnd();

  glPopMatrix();
}

void sphere() {
  double x, y, z, alpha, beta;
  double radius = 1.0;

  for (alpha = 0.0; alpha < M_PI; alpha += M_PI / granularity) {
    glBegin(GL_TRIANGLE_STRIP);
    for (beta = 0.0; beta < 2.01 * M_PI; beta += M_PI / granularity) {
      x = radius * cos(beta) * sin(alpha);
      y = radius * sin(beta) * sin(alpha);
      z = radius * cos(alpha);
      glVertex3f(x, y, z);
      x = radius * cos(beta) * sin(alpha + M_PI / granularity);
      y = radius * sin(beta) * sin(alpha + M_PI / granularity);
      z = radius * cos(alpha + M_PI / granularity);
      glVertex3f(x, y, z);
    }
    glEnd();
  }
}

void halfSphere() {
  double x, y, z, alpha, beta;
  double radius = 1.0;

  for (alpha = 0.0; alpha < M_PI; alpha += M_PI / granularity) {
    glBegin(GL_TRIANGLE_STRIP);
    for (beta = 0.0; beta < 2.01 * M_PI / 2; beta += M_PI / granularity) {
      x = radius * cos(beta) * sin(alpha);
      y = radius * sin(beta) * sin(alpha);
      z = radius * cos(alpha);
      glVertex3f(x, y, z);
      x = radius * cos(beta) * sin(alpha + M_PI / granularity);
      y = radius * sin(beta) * sin(alpha + M_PI / granularity);
      z = radius * cos(alpha + M_PI / granularity);
      glVertex3f(x, y, z);
    }
    glEnd();
  }
}

void wing() {
  double wingThickness = 0.2;
  double wingSize = 3.0;
  glPushMatrix();

  glBegin(GL_TRIANGLES);
  glVertex3f(-wingSize, +wingThickness, +1);
  glVertex3f(+0, +wingThickness, +1);
  glVertex3f(+0, +wingThickness, -1);

  glVertex3f(-wingSize, -wingThickness, +1);
  glVertex3f(+0, -wingThickness, +1);
  glVertex3f(+0, -wingThickness, -1);
  glEnd();

  glBegin(GL_QUADS);
  // bottom of wing
  glVertex3f(-wingSize, +wingThickness, +1);
  glVertex3f(+0, +wingThickness, +1);
  glVertex3f(+0, -wingThickness, +1);
  glVertex3f(-wingSize, -wingThickness, +1);
  // hypot of wing
  glVertex3f(-wingSize, +wingThickness, +1);
  glVertex3f(+0, +wingThickness, -1);
  glVertex3f(+0, -wingThickness, -1);
  glVertex3f(-wingSize, -wingThickness, +1);
  glEnd();

  glPopMatrix();
}

void airplane(const std::string& color) {
  glPushMatrix();

  glPushMatrix();
  glScaled(0.75, 0.75, 3);
  glRotated(90, 1, 0, 0);
  glColor3f(VEC3DARGS(getColor("dark" + color)));
  cylinder();
  glPopMatrix();

  glPushMatrix();
  glTranslated(-0.75, 0, 0);
  glColor3f(VEC3DARGS(getColor(color)));
  wing();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0.75, 0, 0);
  glRotated(180, 0, 1, 0);
  glRotated(180, 1, 0, 0);
  glColor3f(VEC3DARGS(getColor(color)));
  wing();
  glPopMatrix();

  glPushMatrix();
  glScaled(0.5, 0.5, 0.5);
  glTranslated(0, 1.5, 5);
  glRotated(270, 0, 0, 1);
  glColor3f(VEC3DARGS(getColor(color)));
  wing();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 0, -3);
  glRotated(270, 1, 0, 0);
  glScaled(0.75, 1.75, 0.75);
  glColor3f(VEC3DARGS(getColor(color)));
  cone();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 0, 3);
  glRotated(270, 1, 0, 0);
  glScaled(0.75, 1.75, 0.75);
  glColor3f(VEC3DARGS(getColor("gray")));
  cone();
  glPopMatrix();

  glPopMatrix();
}

void turret(Vector3d& orientation) {
  glPushMatrix();

  glPushMatrix();
  glScaled(2.0, 1.0, 2.0);
  glTranslated(0, 1, 0);
  glRotated(0, 0, 0, 0);
  glColor3f(VEC3DARGS(getColor("darkred")));
  trapezoidalPyramid();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 3.0, 0);
  glScaled(1, 1, 1);
  glColor3f(VEC3DARGS(getColor("red")));
  cube();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 3.5, 0);
  glScaled(1.2, 0.1, 1.2);
  glColor3f(VEC3DARGS(getColor("darkred")));
  cube();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 3.0, 0);
  glScaled(1.2, 0.1, 1.2);
  glColor3f(VEC3DARGS(getColor("darkred")));
  cube();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 2.5, 0);
  glScaled(1.2, 0.1, 1.2);
  glColor3f(VEC3DARGS(getColor("darkred")));
  cube();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 5, 0);
  glScaled(1, 1, 1);
  glRotated(0, 0, 1, 0);
  glColor3f(VEC3DARGS(getColor("darkred")));
  sphere();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 5, 0);
  Vector3d norm;
  orientation.getNormalized(norm);
  glTranslated(norm.x, norm.y, norm.z);
  glScaled(0.3, 0.3, 0.3);
  glColor3f(VEC3DARGS(getColor("red")));
  sphere();
  glPopMatrix();

  glPopMatrix();
}

void bunker(const std::string& color) {
  glPushMatrix();

  glPushMatrix();
  glTranslated(0, 0.5, 0);
  glScaled(2.0, 0.5, 2.0);
  glColor3f(VEC3DARGS(getColor("dark" + color)));
  cylinder();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 1.0, 0);
  glScaled(2.0, 1.0, 2.0);
  glColor3f(VEC3DARGS(getColor("" + color)));
  circle();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 1.0, 0);
  glScaled(1.8, 1.8, 1.8);
  glColor3f(VEC3DARGS(getColor("dark" + color)));
  halfSphere();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 2.0, 1.0);
  glRotated(45, 1, 0, 0);
  glScaled(0.5, 2.0, 0.5);
  glColor3f(VEC3DARGS(getColor("" + color)));
  cone();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 2.0, -1.0);
  glRotated(-45, 1, 0, 0);
  glScaled(0.5, 2.0, 0.5);
  glColor3f(VEC3DARGS(getColor("" + color)));
  cone();
  glPopMatrix();

  glPushMatrix();
  glTranslated(1.0, 2.0, 0);
  glRotated(-45, 0, 0, 1);
  glScaled(0.5, 2.0, 0.5);
  glColor3f(VEC3DARGS(getColor("" + color)));
  cone();
  glPopMatrix();

  glPushMatrix();
  glTranslated(-1.0, 2.0, 0);
  glRotated(45, 0, 0, 1);
  glScaled(0.5, 2.0, 0.5);
  glColor3f(VEC3DARGS(getColor("" + color)));
  cone();
  glPopMatrix();

  glPopMatrix();
}

void drawScene() {
  glPushMatrix();
  glScaled(100, 100, 100);
  glColor3f(VEC3DARGS(getColor("darkgray")));
  floor();
  glPopMatrix();

  glPushMatrix();
  glScaled(2, 2, 2);
  glTranslated(5, 1, 0);
  glRotated(-45, 0, 1, 0);
  airplane("orange");
  glPopMatrix();

  glPushMatrix();
  glScaled(2, 2, 2);
  glTranslated(-5, 1, 0);
  glRotated(45, 0, 1, 0);
  airplane("green");
  glPopMatrix();

  glPushMatrix();
  glScaled(2, 2, 2);
  glTranslated(0, 0, 5);
  Vector3d orientationTurret(0, 0, -1);
  Vector3d axis(0, 1, 0);
  rotateVec3d(orientationTurret, axis, th);
  turret(orientationTurret);
  glPopMatrix();
  th = int(th + 1) % 360;

  glPushMatrix();
  glScaled(2, 2, 2);
  glTranslated(0, 0, -5);
  glColor3f(VEC3DARGS(getColor("purple")));
  bunker("purple");
  glPopMatrix();
}
