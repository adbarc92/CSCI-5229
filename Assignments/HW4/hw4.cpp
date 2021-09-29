#include "lib.h"
#include "objects.h"
#include "shapes.h"
#include "vector4d.h"
#include "scene.h"
#include "effects.h"
#include "particleSystem.h"
// #include "effects.h"
#include <cmath>
#include <ctime>
#include <cstdlib>

namespace display {

particleSystem p(NUMBER_OF_PARTICLES);
particleSystem s(2000, 3);
// Electricity Variables
int sparkCount = 160;
int steps = 32;
std::vector<Vector4d> sparkPoints;

// Explosion Variables
float explosionT = 0;
float explosionR = 0.0;

int disperseP = 0;
int gatheringP = 0;
int dispParticles = 1;
int background = 1;
int axes = 1;  //  Display axes
int ampMode=0; // Switch character for ampoule display
// fps timing
int fpstime = 0;
int timebase = 0;
int frame = 0;
int fps = 0;
// window size
int innerWidth = 800;
int innerHeight = 600;
// projection angles for non first person modes
int th = 0;
int ph = 30;
double dim = 5.0; // Size of world
int fov = 65; // Field-of-Vision for FP
double asp = 1; // Aspect Ratio
// speed camera rotates
double cameraSpeed = 1;
double cameraFirstPersonSpeedModifier = 0.9;
double cameraDistance = 5; // 11 by default
// camera mode
std::string projMode = "perspective";
// camera positioning and pointing vectors
Vector4d cameraPosition(0, 5, 25);
Vector4d cameraForward(0, 0, -1);
Vector4d cameraRight(1, 0, 0);
// mouse
int mouseLastX = 0;
int mouseLastY = 0;
// lighting
int zh = 45;
int emission = 0;  // Emission intensity (%)
int ambient = 30;  // Ambient intensity (%)
int diffuse = 50;  // Diffuse intensity (%)
int specular = 0;  // Specular intensity (%)
int shininess = 0; // Shininess (power of two)
float shiny = 1;   // Shininess (value)
int alpha=100;    //  Transparency
}
using namespace display;

//----------------------------------------------------------------------------------------

static void resetCamera() {
  th = 0;
  ph = 30;
  cameraPosition = Vector4d(0, 5, 25);
  cameraForward = Vector4d(0, 0, -1);
  cameraRight = Vector4d(1, 0, 0);
  cameraDistance = 2;
}

static void project() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projMode == "perspective" || projMode == "firstperson") {
    gluPerspective(fov, asp, 1.0, 1000);
  } else if (projMode == "ortho") {
    glOrtho(-asp * dim, +asp * dim, -dim, +dim, -500, +500);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

static void enableLighting() {
  glDisable(GL_LIGHTING);
  float Position[] = {100.0f * (float)Cos(zh), 100, 100.0f * (float)Sin(zh), 1};

  glColor3f(1, 1, 1);
  glPushMatrix();
  glTranslated(Position[0], Position[1], Position[2]);
  glScaled(1, 1, 1);
  sphere();
  glPopMatrix();

  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHT0);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);

  float Ambient[] = {0.01f * ambient, 0.01f * ambient, 0.01f * ambient, 1.0f};
  float Diffuse[] = {0.01f * diffuse, 0.01f * diffuse, 0.01f * diffuse, 1.0f};
  float Specular[] = {0.01f * specular, 0.01f * specular, 0.01f * specular, 1.0f};

  glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
  glLightfv(GL_LIGHT0, GL_POSITION, Position);
}

static void setCamera() {
  if (projMode == "ortho") {
    glRotated(ph, 1, 0, 0);
    glRotated(th, 0, 1, 0);
  } else if (projMode == "perspective") {
    double Ex = -cameraDistance * dim * Sin(th) * Cos(ph);
    double Ey = +cameraDistance * dim * Sin(ph);
    double Ez = +cameraDistance * dim * Cos(th) * Cos(ph);
    gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, Cos(ph), 0);
  } else if (projMode == "firstperson") {
    // cross the right vector with the forward vector to get the up vector
    Vector4d cameraUp;
    Vector4d::getCrossProduct(cameraRight, cameraForward, cameraUp);
    double Px = cameraPosition.x;
    double Py = cameraPosition.y;
    double Pz = cameraPosition.z;
    gluLookAt(Px, Py, Pz, Px + cameraForward.x, Py + cameraForward.y, Pz + cameraForward.z, cameraUp.x, cameraUp.y, cameraUp.z);
  }
}

void keyUpdate() {
  if (isKeyDown(KEY_UP)) {
    if (projMode == "firstperson") {
      cameraPosition.x += cameraForward.x * cameraFirstPersonSpeedModifier;
      cameraPosition.y += cameraForward.y * cameraFirstPersonSpeedModifier;
      cameraPosition.z += cameraForward.z * cameraFirstPersonSpeedModifier;
    } else {
      ph += cameraSpeed;
    }
  }
  if (isKeyDown(KEY_DOWN)) {
    if (projMode == "firstperson") {
      cameraPosition.x -= cameraForward.x * cameraFirstPersonSpeedModifier;
      cameraPosition.y -= cameraForward.y * cameraFirstPersonSpeedModifier;
      cameraPosition.z -= cameraForward.z * cameraFirstPersonSpeedModifier;
    } else {
      ph -= cameraSpeed;
    }
  }
  if (isKeyDown(KEY_LEFT)) {

    if (projMode == "firstperson") {
      Vector4d cameraUp(0, 1, 0);
      rotateVector3d(cameraForward, cameraUp, cameraSpeed);
      rotateVector3d(cameraRight, cameraUp, cameraSpeed);
    } else {
      th += cameraSpeed;
    }
  }
  if (isKeyDown(KEY_RIGHT)) {
    if (projMode == "firstperson") {
      Vector4d cameraUp(0, 1, 0);
      rotateVector3d(cameraForward, cameraUp, -cameraSpeed);
      rotateVector3d(cameraRight, cameraUp, -cameraSpeed);
    } else {
      th -= cameraSpeed;
    }
  }
  if (isKeyDown('a')) {
    cameraPosition.x -= cameraRight.x * cameraFirstPersonSpeedModifier;
    // cameraPosition.y -= cameraRight.y * 0.3;
    cameraPosition.z -= cameraRight.z * cameraFirstPersonSpeedModifier;
  }
  if (isKeyDown('d')) {
    cameraPosition.x += cameraRight.x * cameraFirstPersonSpeedModifier;
    // cameraPosition.y += cameraRight.y * 0.3;
    cameraPosition.z += cameraRight.z * cameraFirstPersonSpeedModifier;
  }
  if (isKeyDown('w')) {
    cameraPosition.x += cameraForward.x * cameraFirstPersonSpeedModifier;
    cameraPosition.y += cameraForward.y * cameraFirstPersonSpeedModifier;
    cameraPosition.z += cameraForward.z * cameraFirstPersonSpeedModifier;
  }
  if (isKeyDown('s')) {
    cameraPosition.x -= cameraForward.x * cameraFirstPersonSpeedModifier;
    cameraPosition.y -= cameraForward.y * cameraFirstPersonSpeedModifier;
    cameraPosition.z -= cameraForward.z * cameraFirstPersonSpeedModifier;
  }
  if (isKeyDown('+')) {
    cameraDistance -= 0.1;
  }
  if (isKeyDown('-')) {
    cameraDistance += 0.1;
  }

  th %= 360;
  ph %= 360;
}

void keyUp(unsigned char ch, int x, int y) {
  unsetKeyDown(ch);
}

void keyDown(unsigned char ch, int x, int y) {
  setKeyDown(ch);
  switch (ch) {
  case 27:
    exit(0);
    break;
  case '0':
    resetCamera();
    break;
  case 'o':
  case '1':
    projMode = "ortho";
    project();
    break;
  case '2':
    projMode = "perspective";
    project();
    break;
  case 'f':
  case '3':
    projMode = "firstperson";
    project();
    break;
  case 'v':
    disperseP = 1 - disperseP;
  case 'g':
    gatheringP = 1 - gatheringP;
    break;
  case 'b':
    background = 1 - background;
    break;
  case 'e':
  case 'E':
    explosionR += 0.02;
    break;
  case 'P':
  case 'p':
    dispParticles = 1 - dispParticles;
    break;
  case 'q':
  case 'Q':
    ampMode = 2;
    explosionR -= 0.02;
    break;
  case 'x':
  case 'X':
    axes = 1-axes;
    break;
  case 'z':
  case 'Z':
    ampMode = 1-ampMode;
    break;
  case '\t':
    explosionR = 0.02;
    ampMode = 2;
    break;
  case 'r':
    explosionR = 0;
    explosionT = 0;
    ampMode = 0;
    break;
  default:
    break;
  }

  th %= 360;
  ph %= 360;
}

void specialUp(int key, int x, int y) {
  if (key == GLUT_KEY_UP) {
    key = KEY_UP;
  } else if (key == GLUT_KEY_DOWN) {
    key = KEY_DOWN;
  } else if (key == GLUT_KEY_LEFT) {
    key = KEY_LEFT;
  } else if (key == GLUT_KEY_RIGHT) {
    key = KEY_RIGHT;
  }
  keyUp(key, x, y);
}

void specialDown(int key, int x, int y) {
  if (key == GLUT_KEY_UP) {
    key = KEY_UP;
  } else if (key == GLUT_KEY_DOWN) {
    key = KEY_DOWN;
  } else if (key == GLUT_KEY_LEFT) {
    key = KEY_LEFT;
  } else if (key == GLUT_KEY_RIGHT) {
    key = KEY_RIGHT;
  }
  keyDown(key, x, y);
}

void reshape(int width, int height) {
  asp = (height > 0) ? (double)width / height : 1;
  glViewport(0, 0, width, height);
  innerWidth = width;
  innerHeight = height;
  project();
}

void drawAxes(double length){
  if (axes)
   {
      glColor3f(1.0, 1.0, 1.0);
      glBegin(GL_LINES);
      glVertex3d(0.0, 0.0, 0.0);
      glVertex3d(length, 0.0, 0.0);
      glVertex3d(0.0, 0.0, 0.0);
      glVertex3d(0.0,length, 0.0);
      glVertex3d(0.0, 0.0, 0.0);
      glVertex3d(0.0, 0.0,length);
      glEnd();
      //  Label axes
      glRasterPos3d(length,0.0,0.0);
      print("X");
      glRasterPos3d(0.0,length,0.0);
      print("Y");
      glRasterPos3d(0.0,0.0,length);
      print("Z");
   }
}

void draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glLoadIdentity();

  setCamera();
  drawAxes(5);
  drawSceneWithoutLighting();
  enableLighting();
  if (background){
    skybox();
  }
  
  glPushMatrix();
  
  if(dispParticles){
    glColor3f(0, 0, 1);
    p.draw();
    glColor3f(0.4, 0.3, 0.8);
    s.draw();
  }

  if(disperseP){
    p.disperse();
    p.advance(150.0);
  }

  if(gatheringP){
    p.gather();
    p.advance(150.0);
  }

  glPopMatrix();
  glColor3f(1, 1, 1);
  explosionT += explosionR;
  if(explosionR < 0 && explosionT == 0){
    explosionR = 0;
    ampMode = 0;
  }
  if (explosionT >= 4)
  {
    explosionT *= 0.2;
    ampMode = 2;
    explosionT = 0;
    explosionR = 0;
  }
  if(p.particles.size() < MAX_PARTICLES){
    p.add_particles(5);
  }
  ampoule(ampMode, explosionT, sparkPoints); // Add sparkCount, steps
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);

  

  glColor3f(1.0, 1.0, 1.0);
  glWindowPos2i(5, 5);
  print("FPS=%d Angle=%d,%d FOV=%d Projection=%s Camera dist %.1f Explosion Time=%.1f", fps, th, ph, fov, projMode.c_str(), cameraDistance, explosionT);
  if (projMode == "firstperson") {
    glColor3f(1.0, 1.0, 1.0);
    glWindowPos2i(5, innerHeight - 25);
    print("Camera Position: %.1f,%.1f,%.1f Camera orientation: %.1f,%.1f,%.1f", Vector3dARGS(cameraPosition), Vector3dARGS(cameraForward));
  }

  glFlush();
  glutSwapBuffers();
}

// force max 60fps
void loop(int v) {
  keyUpdate();
  glutPostRedisplay();
  glutTimerFunc(1000 / 60, loop, v);

  double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
  
  zh = fmod(90 * t, 360.0);

  updateScene();
}

int main(int argc, char* argv[]) {
  srand(time(NULL));
  p.set_gravity();

  initLib();
  initShapes();
  initSpark(sparkPoints);
  resetCamera();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(innerWidth, innerHeight);
  glutCreateWindow("Alex Barclay");

  // if you dont do this after glutCreateWindow on Mingw64, GLEW functions segfault
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    fprintf(stderr, "Error init GLEW: %s\n", glewGetErrorString(err));
    return 1;
  }

  glutDisplayFunc(draw);
  glutReshapeFunc(reshape);
  glutSpecialFunc(specialDown);
  glutSpecialUpFunc(specialUp);
  glutKeyboardFunc(keyDown);
  glutKeyboardUpFunc(keyUp);

  glutIgnoreKeyRepeat(1);
  glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
  glEnable(GL_TEXTURE_2D);

  ilInit();
  ilClearColour(255, 255, 255, 000);

  // images are flipped upside down without this
  ilEnable(IL_ORIGIN_SET);
  ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

  loadTexture("metal","images/metal.png");
  loadTexture("gold1","images/Gold1.png");
  loadTexture("gold2","images/Gold2.png");

  loadTexture("sky-front","images/skybox/sky-front.png");
  loadTexture("sky-right","images/skybox/sky-right.png");
  loadTexture("sky-back","images/skybox/sky-back.png");
  loadTexture("sky-left","images/skybox/sky-left.png");
  loadTexture("sky-bottom","images/skybox/sky-bottom.png");
  loadTexture("sky-top","images/skybox/sky-top.png");
  
  loop(0);

  glutMainLoop();
  return 0;
}
