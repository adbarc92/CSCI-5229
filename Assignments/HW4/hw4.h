#pragma once
#include <string>

class Vector4d;

namespace display {
extern int fpstime;
extern int timebase;
extern int frame;
extern int fps;
extern int innerWidth;
extern int innerHeight;
extern int th;
extern int ph;
extern double dim;
extern int fov;
extern double asp;
extern double cameraSpeed;
extern std::string projMode;
extern Vector4d cameraPosition;
extern Vector4d cameraForward;
extern Vector4d cameraRight;
extern int mouseLastX;
extern int mouseLastY;
}