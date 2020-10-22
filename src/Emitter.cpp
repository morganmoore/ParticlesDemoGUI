#include "Emitter.h"
#include <iostream>
#include <ngl/Random.h>
#include <ngl/NGLStream.h>
#include <ngl/SimpleVAO.h>
#include <ngl/VAOFactory.h>
#include <ngl/VAOPrimitives.h>

//this function is the entry point into the emitter system
//default paramters are set and particles are created
Emitter::Emitter(size_t _numParticles, ngl::Vec3 _pos, float _spread, ngl::Vec3 _emitDir, ngl::Vec3 _colour)
{
	m_pos = _pos;
	m_spread = _spread;
	m_emitDir = _emitDir;
	m_colour = _colour;
	m_numParticles = _numParticles;

	//setting the size of the particle class vector to the default value
	m_particles.resize(_numParticles);
	for (auto& p : m_particles)
	{
		resetParticle(p);

	}
	//m_vao is a pointer to AbstractVAO
	m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_POINTS);
}

//function for the GUI button press restart 
//
void Emitter::restartParticles()
{
	m_particles.resize(m_numParticles);
	for (auto& p : m_particles)
	{
		resetParticle(p);

	}
}

//creates new instances of particles
void Emitter::resetParticle(Particle& io_p)
{
	// creating a 'random' instance 
	auto rng = ngl::Random::instance();
	//setting the data of a new particles 
	io_p.pos = m_pos;
	//creating particle vector 
	io_p.dir = m_emitDir * rng->randomPositiveNumber(1.0f) + randomVectorOnSphere() * m_spread;
	io_p.dir.m_y = io_p.dir.m_y;
	io_p.colour = m_colour;
	//setting the lifespan of each particle 
	io_p.maxLife = static_cast<int> (rng->randomPositiveNumber(m_maxLife)+m_minLife);
	io_p.life = 0;
}
void Emitter::update(float _deltaT)
{
	auto rng = ngl::Random::instance();
	ngl::Vec3 gravity(0.0f, m_gravity, 0.0f);
	//check whether user has selected collisions
	if (m_groundCollide)
	{
		for (auto& p : m_particles)
		{
			p.dir += gravity * _deltaT * 0.5;
			if (++p.life >= p.maxLife )
			{
				resetParticle(p);
			}
			if (p.pos.m_y > 0.3)
			{
				p.pos += p.dir * _deltaT;
				
			}
			else 
			{
				collision(p, _deltaT);	
			}
		}
	}
	//no collisions
	else
	{
		for (auto& p : m_particles)
		{
			p.pos += p.dir * _deltaT;
			p.dir += gravity * _deltaT * 0.5;
			if (++p.life >= p.maxLife || p.pos.m_y <= 0.0f)
			{
				resetParticle(p);
			}
		}
	}
}


//function to create bounce vectors when particle hits gorund level
//since the ground is a flat plane the new bounce vector is simply the current p.dir.m_y value * -1;
//using m_dampener as defined by the user to reduce the speed of the particle after each bounce.
//m_dampener used to approximate the loss of kinetic energy and the affect of friction. 
void Emitter::collision(Particle& _p, float _deltaT)
{
	_p.pos.m_y = 0.3;
	_p.dir.m_y *= -1;
	_p.dir *= m_dampener;
	_p.pos += _p.dir * _deltaT;
}


//function for drawing particles
void Emitter::draw() const
{
	m_vao->bind();
	//setting data for vao
	//when draw is called vao is reset the current frame particle data;
	//passing in the size of the structure: 'number of particles * size of particle class', and a pointer to the first element of the vector
	m_vao->setData(ngl::SimpleVAO::VertexData(m_particles.size() * sizeof(Particle),
		m_particles[0].pos.m_x));
	//defining the format of data so that each element can be accessed for drawing e.g. the ParticleVertex shader
	m_vao->setVertexAttributePointer(0, 3, GL_FLOAT, sizeof(Particle), 0);
	m_vao->setVertexAttributePointer(1, 3, GL_FLOAT, sizeof(Particle), 6);
	//the number of particles
	m_vao->setNumIndices(m_particles.size());

	m_vao->draw();
	
	//for every bind there needs to be an unbind
	m_vao->unbind();

}

//function to set X,Y,Z location of particles
void Emitter::emitLocX(double _lx)
{
	m_pos.m_x = _lx;
}
void Emitter::emitLocY(double _ly)
{
	m_pos.m_y = _ly + 0.3f;
}
void Emitter::emitLocZ(double _lz)
{
	m_pos.m_z = _lz;
}

void Emitter::addParticle()
{
	Particle p;
	//creating new particle
	resetParticle(p);
	//adding the new particle to the end of the m_particles vector
	m_particles.push_back(p);
}

void Emitter::groundCollide(int _groundCollide)
{
	//bool value to switch on in the update funcion if the user has selected collisions
	m_groundCollide = _groundCollide;
}

//function to set gravity
void Emitter::gravity(double _gravity)
{
	m_gravity = _gravity;
}

//setting the scalar that will determine how much energy particles retain after impact with the ground
void Emitter::setBounce(int _bounce)
{
	m_dampener = (100-_bounce) * 0.01;
}

void Emitter::removeParticle()
{
	//if the m_particles vector is not empty remove particle from the end
	if (m_particles.size() > 0)
	{
		m_particles.pop_back();
	}
}

//clears all particles from the m_particles vector
void Emitter::clearParticles()
{
	m_particles.clear();
}

//function to generate a random vector on a sphere for the 'resetParticle' function
ngl::Vec3 Emitter::randomVectorOnSphere(float _radius)
{
	auto rng = ngl::Random::instance();
	float phi = rng->randomPositiveNumber(static_cast<float>(M_PI * 2.0f));
	float costheta = rng->randomNumber();
	float u = rng->randomPositiveNumber();
	float theta = acos(costheta);
	float r = _radius * std::cbrt(u);
	return ngl::Vec3(r * sin(theta) * cos(phi), 
					 r * sin(theta) * sin(phi), 
		             r * cos(theta));	
}

//setting scallar value to influence spread of particles
void Emitter::changeSpread(int _spread)
{
	m_spread = _spread;
}

//setting particle lifespan
void Emitter::setMaxLife(int _maxLife)
{
	m_maxLife = _maxLife;
}

void Emitter::setMinLife(int _minLife)
{
	m_minLife = _minLife;
}

//setting the emit direction that will influence the direction of particles
void Emitter::setEmitDirX(double _emitDirX)
{
	m_emitDir.m_x = _emitDirX;
}

void Emitter::setEmitDirY(double _emitDirY)
{
	m_emitDir.m_y = _emitDirY;
	
}

void Emitter::setEmitDirZ(double _emitDirZ)
{
	m_emitDir.m_z = _emitDirZ;
	

}

void Emitter::setNumParticles(int _numParticles)
{
	m_particles.resize(_numParticles);
}

//function to set R,G,B values of particles
//converting RGB(0-255) values to decimal (0.0-1.0)
void Emitter::setColourR(int _colourR)
{
	m_colour.m_r = _colourR /255.0f;
}

void Emitter::setColourG(int _colourG)
{
	
	m_colour.m_g = _colourG / 255.0f;

}

void Emitter::setColourB(int _colourB)
{
	m_colour.m_b = _colourB/255.0f;

}





