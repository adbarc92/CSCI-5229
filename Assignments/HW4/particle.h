#pragma once

#include "vector3d.h"

namespace particles{
    const float DELTA = 1;
    const int NUMBER_OF_PARTICLES = 3000;
    const float LENGTH = 100.0;

    const int MIN_INIT_VELOCITY = 10;
    const int MAX_INIT_VELOCITY = 100;
    const int MAX_VELOCITY = 200;

    const int MIN_MASS = 2;
    const int MAX_MASS = 8;

    const int FORCE_MAG = 2000;

    const int MAX_PARTICLES = 10000;
}
using namespace particles;

class particle
{	


public:
	float mass;
	Vector3d velocity;
	Vector3d position;

	particle(float = rand() % (MAX_MASS-MIN_MASS) + MIN_MASS,
			Vector3d = Vector3d(Vector3d(rand()/float(RAND_MAX), rand()/float(RAND_MAX), rand()/float(RAND_MAX)), MIN_INIT_VELOCITY + rand() % (MAX_INIT_VELOCITY - MIN_INIT_VELOCITY)),
			Vector3d = Vector3d((1-2*rand()/float(RAND_MAX))*LENGTH, (1-2*rand()/float(RAND_MAX))*LENGTH, (1-2*rand()/float(RAND_MAX))*LENGTH));

	//Function to advance state of particle by time t in ms and force in given direction
	void advance(float, Vector3d = Vector3d(0.0,0.0,0.0));
	Vector3d get_pos(); // Get position
	void draw(int); // Draw a particle

	~particle(void);
};

