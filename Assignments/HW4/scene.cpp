#include "scene.h"
#include "lib.h"
#include "objects.h"
#include "shapes.h"
#include "hw4.h"
#include "vector4d.h"

namespace scene {
std::vector<std::string> shapes = {"circle", "cube", "squareY", "squareZ", "tube", "cone", "trapezoidalPyramid", "sphere", "halfSphere", "wing"};
int shapeIndex = shapes.size() - 1;
int th;
}
using namespace scene;

void updateScene() {
  th = (th + 1) % 360;
}

void drawSceneWithoutLighting() {
  glPushMatrix();
  glTranslated(Vector3dARGS(display::cameraPosition));
  glPopMatrix();
}
void drawSceneWithLighting() {

  ground("ground");

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
  Vector4d orientationTurret(0, 0, -1);
  Vector4d axis(0, 1, 0);
  rotateVector3d(orientationTurret, axis, th);
  turret(orientationTurret);
  glPopMatrix();

  glPushMatrix();
  glScaled(2, 2, 2);
  glTranslated(0, 0, -5);
  glColor3f(Vector3dARGS(getColor("purple")));
  bunker("purple");
  glPopMatrix();

}
