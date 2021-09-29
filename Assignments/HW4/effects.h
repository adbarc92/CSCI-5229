#pragma once

#include "lib.h"

void spark(double startX, double startY, double startZ, double endX, double endY, double endZ, int sparkCount, int steps);

void initSpark(std::vector<Vector4d> sparkPoints);

std::vector<Vector4d> selectSparkPoints(std::vector<Vector4d> sparkPoints);

void modulateSpark(std::vector<float> yCoords);
