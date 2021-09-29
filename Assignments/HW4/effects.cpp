#include "lib.h"
#include "vector4d.h"
#include "effects.h"
#include <ctime>
#include <cstdlib>
#include <vector>

namespace effects{
    int granularity = 6;
    std::vector<float> yCoords;
}
using namespace effects;

void printSparkPoints(std::vector<Vector4d> sparkPoints){
    for(unsigned int i = 0; i < sparkPoints.size(); i++){
        std::cout << "x: " << sparkPoints[i].x << std::endl;
        std::cout << "y: " << sparkPoints[i].y << std::endl;
        std::cout << "z: " << sparkPoints[i].z << std::endl;
    }
}

void initSpark(std::vector<Vector4d> sparkPoints){
    double angle = normalize(1, 0, granularity, 0, 360);
    
    for(float y = -0.68; y < 0.68; y+=0.1){
        for (int i = 0; i < granularity; i++){
            double x = Cos(angle * i);
            double z = Sin(angle * i);
            sparkPoints.push_back(Vector4d(x, y, z, 1));
        }
    }
    // printSparkPoints(sparkPoints);
}

std::vector<Vector4d> selectSparkPoints(std::vector<Vector4d> sparkPoints){
    std::vector<Vector4d> selectedPoints;
    for(unsigned int i = 0; i < sparkPoints.size(); i++){
        selectedPoints.push_back(sparkPoints[rand() % sparkPoints.size()]);
    }
    return selectedPoints;
}

// void modulateSpark(std::vector<float> yCoords){
//     for(int i = 1; i<yCoords.size+1; i++){
//         yCoords[i] += 0.1*((rand()*100%100)-0.5);
//         if (yCoords[i] > yCoords[i-1] + 0.075) yCoords[i] = y[i-1]+0.075;
//         if (yCoords[i] > yCoords[i-1] - 0.075) yCoords[i] = y[i-1]-0.075;
//         if (yCoords[i] > yCoords[i+1] + 0.075) yCoords[i] = y[i-1]+0.075;
//         if (yCoords[i] > yCoords[i+1] - 0.075) yCoords[i] = y[i-1]-0.075;
//         if (yCoords[i] > 0.5) yCoords[i] = 0.5;
//         if (yCoords[i] < -0.5) yCoords[i] = -0.5;
//     }
// }

void spark(Vector4d start, Vector4d end, int sparkCount, int steps)
{
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glColor3f(0.4, 0.3, 0.8);
    float dx = start.x - end.x;
    float dy = start.y - end.y;
    float dz = start.z - end.z;
    for (int i = 0; i < sparkCount; i++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j < steps; j++)
        {
            float rand1 = ((rand() % 100)/100-0.5)*0.04; // Random number between zero and one, subtract 0.5, multiply by 0.04
            float rand2 = (rand() % 100)/100-0.5*0.04;
            float rand3 = (rand() % 100)/100-0.5*0.04;
            glVertex3f(1 * (start.x - dx * j / steps) + rand1, -0.01 + 1 * (start.y - dy * j / steps) + rand2, 1 * (start.z - dz * j / steps) + rand3);
            glVertex3f(1 * (start.x - dx * j / steps) + rand1, 0.01 + 1 * (start.y - dy * j / steps) + rand2, 1 * (start.z - dz * j / steps) + rand3);
        }
    }
    glEnd();
    glDisable(GL_BLEND);
}