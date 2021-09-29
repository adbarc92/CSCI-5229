#include "objects.h"
#include "shapes.h"
#include "vector4d.h"
#include "effects.h"

namespace objects
{
double th = 0;
int granularity = 12;
// std::vector<Vector4d> sparkPoints;
} // namespace objects
using namespace objects;

void ground(const std::string &texture)
{
  glPushMatrix();
  Texture &tex = getTexture(texture);
  tex.bind();

  glBegin(GL_QUADS);
  glVertex3f(-1, +0, -1);
  glVertex3f(-1, +0, +1);
  glVertex3f(+1, +0, +1);
  glVertex3f(+1, +0, -1);
  glEnd();

  glPopMatrix();
  tex.unbind();
}

void airplane(const std::string &color)
{
  glPushMatrix();

  glPushMatrix();
  glScaled(0.75, 0.75, 3);
  glRotated(90, 1, 0, 0);
  glColor3f(VEC3DARGS(getColor("dark" + color)));
  tube("fuselage");
  glPopMatrix();

  glPushMatrix();
  glTranslated(-0.75, 0, 0);
  glColor3f(VEC3DARGS(getColor(color)));
  wing("wing");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0.75, 0, 0);
  glRotated(180, 0, 1, 0);
  glRotated(180, 1, 0, 0);
  glColor3f(VEC3DARGS(getColor(color)));
  wing("wing");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 0, -3);
  glRotated(270, 1, 0, 0);
  glScaled(0.75, 1.75, 0.75);
  glColor3f(VEC3DARGS(getColor(color)));
  cone("wing");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 0, 3);
  glRotated(270, 1, 0, 0);
  glScaled(0.75, 1.75, 0.75);
  glColor3f(VEC3DARGS(getColor("gray")));
  cone("wing");
  glPopMatrix();

  glPopMatrix();
}

void turret(Vector4d &orientation)
{
  glPushMatrix();

  glPushMatrix();
  glScaled(2.0, 1.0, 2.0);
  glTranslated(0, 1, 0);
  glRotated(0, 0, 0, 0);
  glColor3f(VEC3DARGS(getColor("darkred")));
  trapezoidalPyramid("metal");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 3.0, 0);
  glScaled(1, 1, 1);
  glColor3f(VEC3DARGS(getColor("red")));
  cube("metal");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 3.5, 0);
  glScaled(1.2, 0.1, 1.2);
  glColor3f(VEC3DARGS(getColor("darkred")));
  cube("wing");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 3.0, 0);
  glScaled(1.2, 0.1, 1.2);
  glColor3f(VEC3DARGS(getColor("darkred")));
  cube("wing");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 2.5, 0);
  glScaled(1.2, 0.1, 1.2);
  glColor3f(VEC3DARGS(getColor("darkred")));
  cube("wing");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 5, 0);
  glScaled(1, 1, 1);
  glRotated(0, 0, 1, 0);
  glColor3f(VEC3DARGS(getColor("darkred")));
  sphere("wing");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 5, 0);
  Vector4d norm;
  Vector4d::getNormalized3(orientation, norm);
  glTranslated(norm.x, norm.y, norm.z);
  glScaled(0.3, 0.3, 0.3);
  glColor3f(VEC3DARGS(getColor("red")));
  sphere("wing");
  glPopMatrix();

  glPopMatrix();
}

void bunker(const std::string &color)
{
  glPushMatrix();

  glPushMatrix();
  glTranslated(0, 0.5, 0);
  glScaled(2.0, 0.5, 2.0);
  glColor3f(VEC3DARGS(getColor("dark" + color)));
  tube("wing");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 1.0, 0);
  glScaled(2.0, 1.0, 2.0);
  glColor3f(VEC3DARGS(getColor("" + color)));
  circle("wing");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 1.0, 0);
  glScaled(1.8, 1.8, 1.8);
  glColor3f(VEC3DARGS(getColor("dark" + color)));
  halfSphere("wing");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 2.0, 1.0);
  glRotated(45, 1, 0, 0);
  glScaled(0.5, 2.0, 0.5);
  glColor3f(VEC3DARGS(getColor("" + color)));
  cone("wing");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, 2.0, -1.0);
  glRotated(-45, 1, 0, 0);
  glScaled(0.5, 2.0, 0.5);
  glColor3f(VEC3DARGS(getColor("" + color)));
  cone("wing");
  glPopMatrix();

  glPushMatrix();
  glTranslated(1.0, 2.0, 0);
  glRotated(-45, 0, 0, 1);
  glScaled(0.5, 2.0, 0.5);
  glColor3f(VEC3DARGS(getColor("" + color)));
  cone("wing");
  glPopMatrix();

  glPushMatrix();
  glTranslated(-1.0, 2.0, 0);
  glRotated(45, 0, 0, 1);
  glScaled(0.5, 2.0, 0.5);
  glColor3f(VEC3DARGS(getColor("" + color)));
  cone("wing");
  glPopMatrix();

  glPopMatrix();
}

void normalTest()
{
  glPushMatrix();
  glScaled(10, 10, 10);

  Vector4d v1 = Vector4d(-1, -1, 0);
  Vector4d v2 = Vector4d(1, -1, 0.1);
  Vector4d v3 = Vector4d(1, 1, 0.3);

  Vector4d normal;
  Vector4d::calcNormal(v1, v2, v3, normal);

  glBegin(GL_TRIANGLES);

  glColor3f(1.0f, 1.0f, 0.0f);
  glNormal3f(normal.x, normal.y, normal.z);
  glTexCoord2f(0, 0);
  glVertex3f(VEC3DARGS(v1));
  glTexCoord2f(1, 0);
  glVertex3f(VEC3DARGS(v2));
  glTexCoord2f(1, 1);
  glVertex3f(VEC3DARGS(v3));
  glEnd();

  glLineWidth(0.1);
  glBegin(GL_LINES);
  glColor3f(1.0f, 0.5f, 0.5f);
  glVertex3f(VEC3DARGS(v1));
  glVertex3f(v1.x + normal.x, v1.y + normal.y, v1.z + normal.z);

  glVertex3f(VEC3DARGS(v2));
  glVertex3f(v2.x + normal.x, v2.y + normal.y, v2.z + normal.z);

  glVertex3f(VEC3DARGS(v3));
  glVertex3f(v3.x + normal.x, v3.y + normal.y, v3.z + normal.z);
  glEnd();

  glColor3f(1.0f, 1.0f, 1.0f);
  glPopMatrix();
}

void ampoule(int amp, int sparkCount, int steps)
{

  glDisable(GL_BLEND);
  // Cylinder Cap - Gold
  glPushMatrix();
  glTranslated(0, 1.5, 0);
  glScaled(0.78, 0.20, 0.78);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("metal"); // case 1 end
  glPopMatrix();

  // Cylinder Bottom - Gold
  glPushMatrix();
  glTranslated(0, -1.5, 0);
  glScaled(0.78, 0.20, 0.78);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("metal"); // case 2 end
  glPopMatrix();

  // Cylinder Bottom
  glPushMatrix();
  glTranslated(0, -1.8, 0);
  glScaled(0.6, 0.20, 0.6);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("metal"); // case 2 end
  glPopMatrix();

  // Handle, Large Prong
  glPushMatrix();
  glTranslated(0, 2, 0);
  glScaled(0.18, 0.25, 0.12);
  glColor3f(VEC3DARGS(getColor("gold")));
  cube("metal");
  glPopMatrix();

  // Handle, Small Prong, Right
  glPushMatrix();
  glTranslated(0.5, 2, 0);
  glScaled(0.09, 0.3, 0.09);
  glColor3f(VEC3DARGS(getColor("gold")));
  cube("metal");
  glPopMatrix();

  // Handle, Small Prong, Left
  glPushMatrix();
  glTranslated(-0.5, 2, 0);
  glScaled(0.09, 0.28, 0.09);
  glColor3f(VEC3DARGS(getColor("gold")));
  cube("metal");
  glPopMatrix();

  // Handle, Sphere
  glPushMatrix();
  glTranslated(0, 2.3, 0);
  glScaled(0.15, 0.15, 0.15);
  glColor3f(VEC3DARGS(getColor("gold")));
  sphere("metal");
  glPopMatrix();

  // Handle, Top Cylinder
  glPushMatrix();
  glTranslated(0, 2.95, 0);
  glScaled(0.15, 0.5, 0.15);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("metal");
  glPopMatrix();

  // Handle, Small Prong, Right, Connector
  glPushMatrix();
  glTranslated(-0.3, 2.1, 0);
  glRotated(90, 0, 0, 1);
  glScaled(0.05, 0.15, 0.05);
  glColor3f(VEC3DARGS(getColor("gold")));
  cube("metal");
  glPopMatrix();

  // Handle, Small Prong, Left, Connector
  glPushMatrix();
  glTranslated(0.3, 2.1, 0);
  glRotated(90, 0, 0, 1);
  glScaled(0.05, 0.15, 0.05);
  glColor3f(VEC3DARGS(getColor("gold")));
  cube("metal");
  glPopMatrix();

  // Apply texture for inner

  // Inner Cylinder, Top
  glPushMatrix();
  glTranslated(0, 1.3, 0);
  glScaled(0.1, 0.6, 0.1);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("metal");
  glPopMatrix();

  // Inner Cone
  glPushMatrix();
  glTranslated(0, 0.5, 0);
  glScaled(0.4, 0.4, 0.4);
  glColor3f(VEC3DARGS(getColor("gold")));
  cone("metal");
  glPopMatrix();

  // Inner Cylinder, Bottom
  glPushMatrix();
  glTranslated(0, -1.3, 0);
  glScaled(0.1, 0.4, 0.1);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("metal");
  glPopMatrix();

  // Inner Cylinder, Bottom, Wide
  glPushMatrix();
  glTranslated(0, -0.9, 0);
  glScaled(0.4, 0.05, 0.4);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("metal");
  glPopMatrix();

  // Inner Cylinder, 2nd Bottom, Wide
  glPushMatrix();
  glTranslated(0, -0.7, 0);
  glScaled(0.4, 0.05, 0.4);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("metal");
  glPopMatrix();

  // Inner Prongs, 1-4
  glPushMatrix();
  glTranslated(0, -0.65, 0.3);
  glScaled(0.05, 0.2, 0.05);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("metal");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, -0.65, -0.3);
  glScaled(0.05, 0.2, 0.05);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("metal");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0.3, -0.65, 0);
  glScaled(0.05, 0.2, 0.05);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("metal");
  glPopMatrix();

  glPushMatrix();
  glTranslated(-0.3, -0.65, 0);
  glScaled(0.05, 0.2, 0.05);
  glColor3f(VEC3DARGS(getColor("gold")));
  cylinder("metal");
  glPopMatrix();

  // Inner Prong Spheres
  glPushMatrix();
  glTranslated(0, -0.4, 0.3);
  glScaled(0.06, 0.06, 0.06);
  glColor3f(VEC3DARGS(getColor("gold")));
  sphere("metal");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, -0.4, -0.3);
  glScaled(0.06, 0.06, 0.06);
  glColor3f(VEC3DARGS(getColor("gold")));
  sphere("metal");
  glPopMatrix();

  glPushMatrix();
  glTranslated(0.3, -0.4, 0);
  glScaled(0.06, 0.06, 0.06);
  glColor3f(VEC3DARGS(getColor("gold")));
  sphere("metal");
  glPopMatrix();

  glPushMatrix();
  glTranslated(-0.3, -0.4, 0);
  glScaled(0.06, 0.06, 0.06);
  glColor3f(VEC3DARGS(getColor("gold")));
  sphere("metal");
  glPopMatrix();

  // Inner Sphere
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glPushMatrix();
  glTranslated(0, 0, 0);
  glScaled(0.06 * 3, 0.06 * 3, 0.06 * 3);
  glColor3f(VEC3DARGS(getColor("darkblue")));
  sphere("");
  glPopMatrix();
  glDisable(GL_BLEND);

  glPushMatrix();
  spark(0, 0, 0,    1,   -1,    1, sparkCount, steps);
  spark(0, 0, 0,    0.8,   -0.8,    0.8, sparkCount, steps);
  spark(0, 0, 0, -0.5, -0.5, -0.5, sparkCount, steps);
  spark(0, 0, 0,  0.5, -0.5, -0.5, sparkCount, steps);
  spark(0, 0, 0, -0.5, -0.5,  0.5, sparkCount, steps);
  spark(0, 0, 0, -0.5,  0.5, -0.5, sparkCount, steps);
  glPopMatrix();

  // Socket Prong 1: Left
  glPushMatrix();
  glTranslated(0.3, -2, 0);
  glRotated(90, 0, 0, 1);
  glScaled(0.15, 0.15, 0.15);
  glColor3f(VEC3DARGS(getColor("gold")));
  wing("metal");
  glPopMatrix();

  // Socket Prong 2: Right
  glPushMatrix();
  glTranslated(-0.3, -2, 0);
  glRotated(90, 0, 0, 1);
  glScaled(0.15, 0.15, 0.15);
  glColor3f(VEC3DARGS(getColor("gold")));
  wing("metal");
  glPopMatrix();

  // Socket Prong 3: Center
  glPushMatrix();
  glTranslated(0, -2, 0);
  glRotated(90, 0, 0, 1);
  glScaled(0.2, 0.2, 0.2);
  glColor3f(VEC3DARGS(getColor("gold")));
  wing("metal");
  glPopMatrix();

  // Rectangular Cover, Top
  glPushMatrix();
  glTranslated(0,1,0);
  glScaled(0.85,0.13,0.85);
  glColor3f(VEC3DARGS(getColor("gold")));
  tube("metal");
  glPopMatrix();

  // Rectangular Cover, Bottom
  // glPushMatrix();
  // glPopMatrix();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  if (amp)
  {
    // Cylinder, Main
    glPushMatrix();
    glScaled(0.8, 1.35, 0.8);
    glColor4f(0, 0, 1, 0.01 * 100); // Blue
    cylinder("");
    glPopMatrix();
  }

  glDisable(GL_BLEND);
}
