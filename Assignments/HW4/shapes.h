#pragma once

#include "lib.h"

void square(const std::string& texture="");
void circle(const std::string& texture="");
void cubeOld(const std::string& texture="");
void cube(const std::string& texture="");
void squareY(const std::string& texture="");
void squareZ(const std::string& texture="");
void tube(const std::string& texture = "", float explosionT = 0);
void tubeOld(const std::string& texture = "");
void cone(const std::string& texture = "");
void trapezoidalPyramid(const std::string& texture = "");
void sphere(const std::string& texture = "");
void halfSphere(const std::string& texture = "");
void wing(const std::string& texture = "");
void cylinder(const std::string& texture = "", float explosionT = 0);
void cylinderOld(const std::string& texture = "");
void initShapes();
