#pragma once

#include "lib.h"

void ground(const std::string& textureName);
void airplane(const std::string& color);
void turret(Vector4d& orientation);
void bunker(const std::string& color);
void ampoule(int amp, int sparkCount, int steps);

void normalTest();
