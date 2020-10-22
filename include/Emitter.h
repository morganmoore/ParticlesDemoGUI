#ifndef EMITTER_H_
#define EMITTER_H_
#include <vector>
#include "Particle.h"
#include <ngl/AbstractVAO.h>
#include <memory>

class Emitter
{
public :
	//declaring public emitter class functions
	//giving devault values to arguments of emitter function
	Emitter(size_t _numParticles = 20000, ngl::Vec3 _pos = 0, float _spead = 1.5, ngl::Vec3 _emitDir = ngl::Vec3(0.0f, 15.0f, 0.0f), ngl::Vec3 _colour = ngl::Vec3(0.0f, 0.0f, 1.0f));
	~Emitter() = default;
	void update(float _deltaTime);
	void draw() const;

	void emitLocX(double _dy);
	void emitLocY(double _dy);
	void emitLocZ(double _dx);

	void addParticle();
	void removeParticle();
	void clearParticles();
	void restartParticles();

	void groundCollide(int _groundCollide);
	void gravity(double _gravity);
	void setBounce(int _bounce);

	void changeSpread(int _spread);
	void setNumParticles(int _numParticles);
	void setMaxLife(int _maxLife);
	void setMinLife(int _minLife);

	void setColourR(int _colourR);
	void setColourG(int _colourG);
	void setColourB(int _colourB);
	
	void setEmitDirX(double _emitDirX);
	void setEmitDirY(double _emitDirY);
	void setEmitDirZ(double _emitDirZ);

	void collision(Particle& io_p, float _deltaT);

private :
	void resetParticle(Particle& io_p);
	ngl::Vec3 randomVectorOnSphere(float _radius = 1.0f);
	std::vector<Particle> m_particles;
	std::unique_ptr<ngl::AbstractVAO> m_vao;
	ngl::Vec3 m_pos;
	int m_spread;
	ngl::Vec3 m_emitDir;
	ngl::Vec3 m_colour;
	size_t m_numParticles;
	int m_groundCollide = 0;
	float m_gravity = -9.81f;
	int m_maxLife = 2500;
	int m_minLife = 100;
	float m_dampener = 0.65f;

};
#endif