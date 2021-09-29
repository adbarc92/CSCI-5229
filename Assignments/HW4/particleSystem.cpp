#include "particleSystem.h"
#include "vector3d.h"
#include <vector>
#include <GL/glut.h>
#include <math.h>

particleSystem::particleSystem(int n)
{
	if(n > MAX_PARTICLES)
		n = MAX_PARTICLES;

	for(int i = 0; i < n; i++)
	{
        particle temp;
        particles.push_back(temp);
	}
}

particleSystem::particleSystem(int n, int radius)
{
	if(n > MAX_PARTICLES)
		n = MAX_PARTICLES;

	for(int i = 0; i < n; i++)
	{
        particle temp = particle(8,Vector3d(0,0,0), Vector3d((float) (rand()*100%radius)/100,0,(float) (rand()*100%radius)/100));
        particles.push_back(temp);
	}
}

	
//Function to advance state of particle system by time t in ms
void particleSystem::advance(float time)
{
	vector<particle>::iterator it;
	for(it = particles.begin(); it != particles.end(); it++)
	{
		Vector3d force = Vector3d((it->get_pos()).unit(), FORCE_MAG);
		it->advance(time, force);
	}
}

//Function to set gravity point
void particleSystem::set_gravity(Vector3d gravity){
	gravity_point = gravity;
}

//Function to add particles
bool particleSystem :: add_particles(int num)
{
	int i;
	for(i = 0; i < num && particles.size() < MAX_PARTICLES; i++)
	{
		particle p;
		particles.push_back(p);
	}
	return (i >= num);
}

//Function to delete particles(least is 0)
bool particleSystem :: delete_particles(int num)
{
	int i;
	for(i = 0; i < num && particles.size() > 0; i++)
	{
		particles.pop_back();
	}

	return (i >= num);
}

//Function to draw a particle
void particleSystem::draw()
{
	vector<particle>::iterator it;
	for(it = particles.begin(); it != particles.end(); it++){
		Vector3d pos = it->get_pos();
		float k = (gravity_point-pos).mag()/(1.5*LENGTH);
		glColor4f(0.4, 0.3, 0.8, 1);
		glBegin(GL_POINTS);
			glVertex3f(pos.x, pos.y, pos.z);
		glEnd();
	}
}

void particleSystem::gather(){
	for (unsigned int i = 0; i < particles.size(); i++){
		if(particles[i].velocity.mag() != 0){
			particles[i].velocity.x = particles[i].position.x * -1;
			particles[i].velocity.y = particles[i].position.y * -1;
			particles[i].velocity.z = particles[i].position.z * -1;
			}
	}
}

void particleSystem::disperse(){
	for (unsigned int i = 0; i < particles.size(); i++){
		if(particles[i].velocity.mag() != 0){
			particles[i].velocity.x = particles[i].velocity.x * -1;
			particles[i].velocity.y = particles[i].velocity.y * -1;
			particles[i].velocity.z = particles[i].velocity.z * -1;
			}
	}
}

particleSystem::~particleSystem(void)
{
}
