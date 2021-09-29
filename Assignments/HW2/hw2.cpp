#include "lib.h"
#include "objects.h"

#define KEY_RIGHT 230
#define KEY_LEFT 231
#define KEY_UP 232
#define KEY_DOWN 233

namespace mainGlobals {
// fps timing
int fpsTime = 0;
int timebase = 0;
int frame = 0;
int fps = 0;
// window size
int innerWidth = 800;
int innerHeight = 600;
// projection angles for non first person modes
int th = 45;
int ph = 30;
double dim = 25.0;
int fov = 65;
double asp = 1;
// speed camera rotates
double cameraSpeed = 1;
// camera mode
std::string projMode = "ortho";
// camera positioning and pointing vectors
Vector3d cameraPosition(0, 5, 25);
Vector3d cameraForward(0, 0, -1);
Vector3d cameraRight(1, 0, 0);
}
using namespace mainGlobals;

//----------------------------------------------------------------------------------------

static void project() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projMode == "perspective" || projMode == "firstperson") {
    gluPerspective(fov, asp, 0.1, 1000);
  } else if (projMode == "ortho") {
    glOrtho(-asp * dim, +asp * dim, -dim, +dim, -dim, +dim);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyUpdate() {
  if (isKeyDown(KEY_UP)) {
    if (projMode == "firstperson") {
      cameraPosition.x += cameraForward.x * 0.3;
      cameraPosition.y += cameraForward.y * 0.3;
      cameraPosition.z += cameraForward.z * 0.3;
    } else {
      ph += cameraSpeed;
    }
  }
  if (isKeyDown(KEY_DOWN)) {
    if (projMode == "firstperson") {
      cameraPosition.x -= cameraForward.x * 0.3;
      cameraPosition.y -= cameraForward.y * 0.3;
      cameraPosition.z -= cameraForward.z * 0.3;
    } else {
      ph -= cameraSpeed;
    }
  }
  if (isKeyDown(KEY_LEFT)) {

    if (projMode == "firstperson") {
      Vector3d cameraUp;
      cameraRight.getCrossProduct(cameraForward, cameraUp);
      rotateVec3d(cameraForward, cameraUp, cameraSpeed);
      rotateVec3d(cameraRight, cameraUp, cameraSpeed);
    } else {
      th += cameraSpeed;
    }
  }
  if (isKeyDown(KEY_RIGHT)) {
    if (projMode == "firstperson") {
      Vector3d cameraUp;
      cameraRight.getCrossProduct(cameraForward, cameraUp);
      rotateVec3d(cameraForward, cameraUp, -cameraSpeed);
      rotateVec3d(cameraRight, cameraUp, -cameraSpeed);
    } else {
      th -= cameraSpeed;
    }
  }
  if (isKeyDown('q')) {
    Vector3d cameraUp;
    cameraRight.getCrossProduct(cameraForward, cameraUp);
    rotateVec3d(cameraForward, cameraUp, cameraSpeed);
    rotateVec3d(cameraRight, cameraUp, cameraSpeed);
  }
  if (isKeyDown('e')) {
    Vector3d cameraUp;
    cameraRight.getCrossProduct(cameraForward, cameraUp);
    rotateVec3d(cameraForward, cameraUp, -cameraSpeed);
    rotateVec3d(cameraRight, cameraUp, -cameraSpeed);
  }
  if (isKeyDown('a')) {
    cameraPosition.x -= cameraRight.x * 0.3;
    cameraPosition.y -= cameraRight.y * 0.3;
    cameraPosition.z -= cameraRight.z * 0.3;
  }
  if (isKeyDown('d')) {
    cameraPosition.x += cameraRight.x * 0.3;
    cameraPosition.y += cameraRight.y * 0.3;
    cameraPosition.z += cameraRight.z * 0.3;
  }
  if (isKeyDown('w')) {
    cameraPosition.x += cameraForward.x * 0.3;
    cameraPosition.y += cameraForward.y * 0.3;
    cameraPosition.z += cameraForward.z * 0.3;
  }
  if (isKeyDown('s')) {
    cameraPosition.x -= cameraForward.x * 0.3;
    cameraPosition.y -= cameraForward.y * 0.3;
    cameraPosition.z -= cameraForward.z * 0.3;
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
    th = 45;
    ph = 30;
    cameraPosition = Vector3d(0, 5, 25);
    cameraForward = Vector3d(0, 0, -1);
    cameraRight = Vector3d(1, 0, 0);
    break;
  case 'o':
  case '1':
    projMode = "ortho";
    break;
  case 'p':
  case '2':
    projMode = "perspective";
    break;
  case 'f':
  case '3':
    projMode = "firstperson";
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

void display() {
  keyUpdate();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  project();
  glLoadIdentity();

  if (projMode == "ortho") {
    glRotated(ph, 1, 0, 0);
    glRotated(th, 0, 1, 0);
  } else if (projMode == "perspective") {
    double Ex = -2 * dim * Sin(th) * Cos(ph);
    double Ey = +2 * dim * Sin(ph);
    double Ez = +2 * dim * Cos(th) * Cos(ph);
    gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, Cos(ph), 0);
  } else if (projMode == "firstperson") {
    // cross the right vector with the forward vector to get the up vector
    Vector3d cameraUp;
    cameraRight.getCrossProduct(cameraForward, cameraUp);
    double Px = cameraPosition.x;
    double Py = cameraPosition.y;
    double Pz = cameraPosition.z;
    gluLookAt(Px, Py, Pz, Px + cameraForward.x, Py + cameraForward.y, Pz + cameraForward.z, cameraUp.x, cameraUp.y, cameraUp.z);
  }

  drawScene();

  frame++;
  fpsTime = glutGet(GLUT_ELAPSED_TIME);
  if (fpsTime - timebase > 1000) {
    fps = frame * 1000.0 / (fpsTime - timebase);
    timebase = fpsTime;
    frame = 0;
  }

  glColor3f(VEC3DARGS(getColor("white")));
  glWindowPos2i(5, 5);
  print("FPS=%d Angle=%d,%d FOV=%d Projection=%s", fps, th, ph, fov, projMode.c_str());
  if (projMode == "firstperson") {
    glWindowPos2i(5, innerHeight - 25);
    print("Camera Position: %.1f,%.1f,%.1f Camera orientation: %.1f,%.1f,%.1f", VEC3DARGS(cameraPosition), VEC3DARGS(cameraForward));
  }

  glFlush();
  glutSwapBuffers();
}

// force max 60fps
void loop(int) {
  glutPostRedisplay();
  glutTimerFunc(1000 / 60, loop, 0);
}

int main(int argc, char* argv[]) {
  initColors();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(innerWidth, innerHeight);
  glutCreateWindow("HW2");

  // if you dont do this after glutCreateWindow on Mingw64, GLEW functions segfault
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    fprintf(stderr, "Error init GLEW: %s\n", glewGetErrorString(err));
    return 1;
  }

  glutIgnoreKeyRepeat(1);
  glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(specialDown);
  glutSpecialUpFunc(specialUp);
  glutKeyboardFunc(keyDown);
  glutKeyboardUpFunc(keyUp);

  loop(0);

  glutMainLoop();
  return 0;
}
