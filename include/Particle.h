#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <ngl/Vec3.h>

//defining components of particle struct
struct Particle
{
	ngl::Vec3 pos;
	ngl::Vec3 dir;
	ngl::Vec3 colour;
	unsigned life = 0;
	unsigned int maxLife = 0;
};

#endif