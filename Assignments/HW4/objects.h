#pragma once

#include "lib.h"

void ground(const std::string& textureName);
void airplane(const std::string& color);
void turret(Vector4d& orientation);
void bunker(const std::string& color);
void ampoule(int ampMode = 1, float explosionT = 0.f, std::vector<Vector4d> sparkPoints = std::vector<Vector4d>());
void skybox();

void normalTest();
