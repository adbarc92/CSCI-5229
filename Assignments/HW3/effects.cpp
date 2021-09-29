#include "lib.h"
#include "vector4d.h"
#include "effects.h"
#include <ctime>
#include <cstdlib>
#include <vector>

// void initSpark(std::vector<Vector4d> sparkPoints){}

// void selectSparkPoints(std::vector<Vector4d> sparkPoints){}

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

void spark(double startX, double startY, double startZ, double endX, double endY, double endZ, int sparkCount, int steps)
{
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glColor3f(0.4, 0.3, 0.8);
    float dx = startX - endX;
    float dy = startY - endY;
    float dz = startZ - endZ;
    for (int i = 0; i < sparkCount; i++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j < steps; j++)
        {
            float rand1 = ((rand() % 100)/100-0.5)*0.04; // Random number between zero and one, subtract 0.5, multiply by 0.04
            float rand2 = (rand() % 100)/100-0.5*0.04;
            float rand3 = (rand() % 100)/100-0.5*0.04;
            glVertex3f(1 * (startX - dx * j / steps) + rand1, -0.01 + 1 * (startY - dy * j / steps) + rand2, 1 * (startZ - dz * j / steps) + rand3);
            glVertex3f(1 * (startX - dx * j / steps) + rand1, 0.01 + 1 * (startY - dy * j / steps) + rand2, 1 * (startZ - dz * j / steps) + rand3);
        }
    }
    glEnd();
    glDisable(GL_BLEND);
}

// void vibrate(){}
// void shatter(){}
// void explode(){}
