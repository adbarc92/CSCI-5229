#pragma once

#include <vector>
#include <string>

void updateScene();
void drawSceneWithoutLighting();
void drawSceneWithLighting();

namespace scene {
extern std::vector<std::string> shapes;
extern int shapeIndex;
}
