#include "shapes.h"
#include "vector4d.h"
#include <cstdlib>

namespace shapes {
double th = 0;
int granularity = 12;
std::vector<float> randomOffsets;
double outwardFactor = 10;
double rotationSpeed = 240;
}
using namespace shapes;

void square(const std::string& texture) {
  Texture& tex = getTexture(texture);
  tex.bind();

  glPushMatrix();

  glBegin(GL_QUADS);

  glNormal3f(0, 0, 1);
  glTexCoord2f(1, 1);
  glVertex3f(+1, +1, +0);
  glTexCoord2f(1, 0);
  glVertex3f(+1, -1, +0);
  glTexCoord2f(0, 0);
  glVertex3f(-1, -1, +0);
  glTexCoord2f(0, 1);
  glVertex3f(-1, +1, +0);

  glEnd();

  glPopMatrix();

  tex.unbind();
}

void circle(const std::string& texture) {
  Texture& tex = getTexture(texture);
  tex.bind();

  glPushMatrix();

  double angle = normalize(1, 0, granularity, 0, 360);
  glBegin(GL_TRIANGLE_STRIP);
  glNormal3f(0, 1, 0);
  for (double i = 0; i <= granularity; i++) {
    double x = Cos(angle * i);
    double z = Sin(angle * i);
    glTexCoord2f(normalize(x, -1, 1, 0, 1), 1 - normalize(z, -1, 1, 0, 1));
    glVertex3f(x, +0, z);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(+0, +0, +0);
  }
  glEnd();

  glPopMatrix();

  tex.unbind();
}

void cube(const std::string& texture) {
  Texture& tex = getTexture(texture);
  tex.bind();

  for (int i = 0; i < 4; i++) {

    glPushMatrix();
    glRotated(90 * i, 0, 1, 0);

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0, 0);
    glVertex3f(-1.0, -1.0, +1.0);
    glTexCoord2f(1, 0);
    glVertex3f(+1.0, -1.0, +1.0);
    glTexCoord2f(1, 1);
    glVertex3f(+1.0, +1.0, +1.0);
    glTexCoord2f(0, 1);
    glVertex3f(-1.0, +1.0, +1.0);
    glEnd();

    glPopMatrix();
  }

  glPushMatrix();

  glBegin(GL_QUADS);
  glNormal3f(0.0, -1.0, 0.0);
  glTexCoord2f(0, 1);
  glVertex3f(-1.0, -1.0, +1.0);
  glTexCoord2f(1, 1);
  glVertex3f(+1.0, -1.0, +1.0);
  glTexCoord2f(1, 0);
  glVertex3f(+1.0, -1.0, -1.0);
  glTexCoord2f(0, 0);
  glVertex3f(-1.0, -1.0, -1.0);

  glNormal3f(0.0, +1.0, 0.0);
  glTexCoord2f(0, 1);
  glVertex3f(-1.0, +1.0, +1.0);
  glTexCoord2f(1, 1);
  glVertex3f(+1.0, +1.0, +1.0);
  glTexCoord2f(1, 0);
  glVertex3f(+1.0, +1.0, -1.0);
  glTexCoord2f(0, 0);
  glVertex3f(-1.0, +1.0, -1.0);
  glEnd();

  glPopMatrix();

  tex.unbind();
}

void squareY(const std::string& textureName) {
  Texture& tex = getTexture(textureName);
  tex.bind();
  glBegin(GL_QUADS);
  glNormal3f(0, 0, 1);
  glTexCoord2f(0, 0);
  glVertex3f(-1.0, -1.0, +0.0);
  glTexCoord2f(0, 1);
  glVertex3f(-1.0, +1.0, +0.0);
  glTexCoord2f(1, 1);
  glVertex3f(+1.0, +1.0, +0.0);
  glTexCoord2f(1, 0);
  glVertex3f(+1.0, -1.0, +0.0);
  glEnd();
  tex.unbind();
}

void squareZ(const std::string& textureName) {
  Texture& tex = getTexture(textureName);

  glPushMatrix();
  glRotated(180, 0, 1, 0);
  glRotated(180, 0, 0, 1);

  tex.bind();
  glBegin(GL_QUADS);
  glNormal3f(0, -1, 0);
  glTexCoord2f(0, 0);
  glVertex3f(-1.0, 0, -1.0);
  glTexCoord2f(1, 0);
  glVertex3f(+1.0, 0, -1.0);
  glTexCoord2f(1, 1);
  glVertex3f(+1.0, 0, +1.0);
  glTexCoord2f(0, 1);
  glVertex3f(-1.0, 0, +1.0);
  glEnd();

  glPopMatrix();

  tex.unbind();
}

void tubeOld(const std::string& texture) {
  Texture& tex = getTexture(texture);
  tex.bind();
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

void tube(const std::string& texture, float explosionT) {
  Texture& tex = getTexture(texture);
  tex.bind();

  double angle = normalize(1, 0, granularity, 0, 360);

  for (int i = 0; i < granularity; i++) {
    double x = Cos(angle * i);
    double z = Sin(angle * i);
    double xNext = Cos(angle * (i + 1));
    double zNext = Sin(angle * (i + 1));

    float offset1 = randomOffsets[i];
    float offset2 = randomOffsets[i * 2];

    glPushMatrix();
    glTranslated(x * explosionT * outwardFactor, 5 * explosionT - explosionT * offset1, z * explosionT * outwardFactor);
    glTranslated(x, 0, z);
    glRotated(explosionT * rotationSpeed * normalize(offset1, 0, 10, 0, 1), 0, 1, 0);
    glRotated(explosionT * rotationSpeed * normalize(offset1, 0, 10, 0, 1), 0, 0, 1);
    glTranslated(-x, 0, -z);

    glBegin(GL_TRIANGLES);
    glNormal3f(x, 0, z);
    glTexCoord2f((float)i / (float)granularity, 0);
    glVertex3f(x, -1, z);
    glTexCoord2f((float)i / (float)granularity, 1);
    glVertex3f(x, +1, z);
    glNormal3f(xNext, 0, zNext);
    glTexCoord2f((float)(i + 1) / (float)granularity, 0);
    glVertex3f(xNext, -1, zNext);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(x * explosionT * outwardFactor, 5 * explosionT - explosionT * offset2, z * explosionT * outwardFactor);
    glTranslated(x, 0, z);
    glRotated(explosionT * rotationSpeed * normalize(offset2, 0, 10, 0, 1), 0, 1, 0);
    glRotated(explosionT * rotationSpeed * normalize(offset2, 0, 10, 0, 1), 0, 0, 1);
    glTranslated(-x, 0, -z);

    glBegin(GL_TRIANGLES);
    glNormal3f(xNext, 0, zNext);
    glTexCoord2f((float)(i + 1) / (float)granularity, 0);
    glVertex3f(xNext, -1, zNext);
    glTexCoord2f((float)(i + 1) / (float)granularity, 1);
    glVertex3f(xNext, 1, zNext);
    glNormal3f(x, 0, z);
    glTexCoord2f((float)i / (float)granularity, 0);
    glVertex3f(x, 1, z);
    glEnd();
    glPopMatrix();
  }

  tex.unbind();
}

void cone(const std::string& texture) {
  Texture& tex = getTexture(texture);
  tex.bind();

  double angle = normalize(1, 0, granularity, 0, 360);
  glBegin(GL_TRIANGLE_STRIP);
  for (int i = 0; i <= granularity; i++) {
    double x = Cos(angle * i);
    double z = Sin(angle * i);
    glNormal3f(x, 1, z);
    glTexCoord2f(normalize(x, -1, 1, 0, 1), 1 - normalize(z, -1, 1, 0, 1));
    glVertex3f(x, +0, z);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(+0, +1, +0);
  }
  glEnd();

  tex.bind();
}

void trapezoidalPyramid(const std::string& texture) {
  Texture& tex = getTexture(texture);
  tex.bind();

  for (int i = 0; i < 4; i++) {
    glPushMatrix();
    glRotated(90 * i, 0, 1, 0);

    glBegin(GL_QUADS);
    glNormal3f(0, 0.5, 1);
    glTexCoord2f(0, 0);
    glVertex3f(-1.0, -1.0, +1.0);
    glTexCoord2f(0, 1);
    glVertex3f(-0.5, +1.0, +0.5);
    glTexCoord2f(0.75, 0.85);
    glVertex3f(+0.5, +1.0, +0.5);
    glTexCoord2f(1, 0);
    glVertex3f(+1.0, -1.0, +1.0);
    glEnd();

    glPopMatrix();
  }

  glPushMatrix();

  glBegin(GL_QUADS);
  glNormal3f(0, -1, 0);
  glTexCoord2f(0, 1);
  glVertex3f(-1.0, -1.0, +1.0);
  glTexCoord2f(1, 1);
  glVertex3f(+1.0, -1.0, +1.0);
  glTexCoord2f(1, 0);
  glVertex3f(+1.0, -1.0, -1.0);
  glTexCoord2f(0, 0);
  glVertex3f(-1.0, -1.0, -1.0);

  glNormal3f(0, 1, 0);
  glTexCoord2f(0, 1);
  glVertex3f(-0.5, 1.0, +0.5);
  glTexCoord2f(1, 1);
  glVertex3f(+0.5, 1.0, +0.5);
  glTexCoord2f(1, 0);
  glVertex3f(+0.5, 1.0, -0.5);
  glTexCoord2f(0, 0);
  glVertex3f(-0.5, 1.0, -0.5);
  glEnd();

  glPopMatrix();

  tex.unbind();
}

void _vertex(int th, int ph) {
  double x = -Sin(th) * Cos(ph);
  double y = Cos(th) * Cos(ph);
  double z = Sin(ph);
  glNormal3d(x, y, z);
  glTexCoord2d(th / 360.0, ph / 180.0 + 0.5);
  glVertex3d(x, y, z);
}

void sphere(const std::string& texture) {
  Texture& tex = getTexture(texture);
  tex.bind();

  int th, ph;
  for (ph = -90; ph < 90; ph += 5) {
    glBegin(GL_QUAD_STRIP);
    for (th = 0; th <= 360; th += 5) {
      _vertex(th, ph);
      _vertex(th, ph + 5);
    }
    glEnd();
  }

  tex.unbind();
}

void halfSphere(const std::string& texture) {
  Texture& tex = getTexture(texture);
  tex.bind();

  glPushMatrix();
  glRotated(-90, 0, 0, 1);

  int th, ph;
  for (ph = -90; ph < 90; ph += 5) {
    glBegin(GL_QUAD_STRIP);
    for (th = 0; th <= 180; th += 5) {
      _vertex(th, ph);
      _vertex(th, ph + 5);
    }
    glEnd();
  }

  glPopMatrix();

  tex.unbind();
}

void wing(const std::string& texture) {
  if (texture.size()) {
    Texture& tex = getTexture(texture);
    tex.bind();
  }

  double wingThickness = 0.2;
  double wingSize = 3.0;
  glPushMatrix();

  glBegin(GL_TRIANGLES);
  glNormal3f(0, 1, 0);
  glTexCoord2f(0, 0);
  glVertex3f(-wingSize, +wingThickness, +1);
  glTexCoord2f(1, 1);
  glVertex3f(+0, +wingThickness, -1);
  glTexCoord2f(1, 0);
  glVertex3f(+0, +wingThickness, +1);

  glNormal3f(0, -1, 0);
  glTexCoord2f(0, 0);
  glVertex3f(-wingSize, -wingThickness, +1);
  glTexCoord2f(1, 0);
  glVertex3f(+0, -wingThickness, +1);
  glTexCoord2f(1, 1);
  glVertex3f(+0, -wingThickness, -1);
  glEnd();

  glBegin(GL_QUADS);
  // bottom of wing
  glNormal3f(0, 0, 1);
  glTexCoord2f(0, 1);
  glVertex3f(-wingSize, +wingThickness, +1);
  glTexCoord2f(1, 1);
  glVertex3f(+0, +wingThickness, +1);
  glTexCoord2f(1, 0);
  glVertex3f(+0, -wingThickness, +1);
  glTexCoord2f(0, 0);
  glVertex3f(-wingSize, -wingThickness, +1);
  // hypot of wing
  glNormal3f(-3, 0, -1.04);
  glTexCoord2f(0, 1);
  glVertex3f(-wingSize, +wingThickness, +1);
  glTexCoord2f(1, 1);
  glVertex3f(+0, +wingThickness, -1);
  glTexCoord2f(1, 0);
  glVertex3f(+0, -wingThickness, -1);
  glTexCoord2f(0, 0);
  glVertex3f(-wingSize, -wingThickness, +1);
  glEnd();

  glPopMatrix();

  if (texture.size()) {
    Texture& tex = getTexture(texture);
    tex.bind();
  }
}

void cylinder(const std::string& texture, float explosionT){
  
  glPushMatrix();
  glTranslated(0, 1, 0);
  circle(texture);
  glPopMatrix();
  
  glPushMatrix();
  glTranslated(0, -1, 0);
  circle(texture);
  glPopMatrix();

  Texture& tex = getTexture(texture);
  tex.bind();

  double angle = normalize(1, 0, granularity, 0, 360);

  for (int i = 0; i < granularity; i++) {
    double x = Cos(angle * i);
    double z = Sin(angle * i);
    double xNext = Cos(angle * (i + 1));
    double zNext = Sin(angle * (i + 1));

    float offset1 = randomOffsets[i];
    float offset2 = randomOffsets[i * 2];

    glPushMatrix();
    glTranslated(x * explosionT * outwardFactor, 5 * explosionT - explosionT * offset1, z * explosionT * outwardFactor);
    glTranslated(x, 0, z);
    glRotated(explosionT * rotationSpeed * normalize(offset1, 0, 10, 0, 1), 0, 1, 0);
    glRotated(explosionT * rotationSpeed * normalize(offset1, 0, 10, 0, 1), 0, 0, 1);
    glTranslated(-x, 0, -z);

    glBegin(GL_TRIANGLES);
    glNormal3f(x, 0, z);
    glTexCoord2f((float)i / (float)granularity, 0);
    glVertex3f(x, -1, z);
    glTexCoord2f((float)i / (float)granularity, 1);
    glVertex3f(x, +1, z);
    glNormal3f(xNext, 0, zNext);
    glTexCoord2f((float)(i + 1) / (float)granularity, 0);
    glVertex3f(xNext, -1, zNext);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(x * explosionT * outwardFactor, 5 * explosionT - explosionT * offset2, z * explosionT * outwardFactor);
    glTranslated(x, 0, z);
    glRotated(explosionT * rotationSpeed * normalize(offset2, 0, 10, 0, 1), 0, 1, 0);
    glRotated(explosionT * rotationSpeed * normalize(offset2, 0, 10, 0, 1), 0, 0, 1);
    glTranslated(-x, 0, -z);

    glBegin(GL_TRIANGLES);
    glNormal3f(xNext, 0, zNext);
    glTexCoord2f((float)(i + 1) / (float)granularity, 0);
    glVertex3f(xNext, -1, zNext);
    glTexCoord2f((float)(i + 1) / (float)granularity, 1);
    glVertex3f(xNext, 1, zNext);
    glNormal3f(x, 0, z);
    glTexCoord2f((float)i / (float)granularity, 0);
    glVertex3f(x, 1, z);
    glEnd();
    glPopMatrix();
  }

  tex.unbind();
}

void initShapes() {
  for (int i = 0; i < granularity * 2; i++) {
    shapes::randomOffsets.push_back(rand() % 10);
  }
}
