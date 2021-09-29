#pragma once

#include <vector>
#include "particle.h"

class particleSystem
{
	

public:
    vector<particle> particles;
	Vector3d gravity_point;

	//construct system given n number of particles
	particleSystem(int);
	particleSystem(int, int);

	//Function to advance state of particle system by time t in ms
	void advance(float);

	//Function to set gravity point
	void set_gravity(Vector3d = Vector3d(0, 0, 0));

	//Function to add particles
	bool add_particles(int);

	//Function to delete particles
	bool delete_particles(int);

	//Function to draw particles
	void draw();

	void gather();

	void disperse();

	~particleSystem(void);
};

