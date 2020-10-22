#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <iostream>
#include<ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Util.h>
#include<ngl/Random.h>


NGLScene::NGLScene(size_t _numParticles, QWidget *_parent) : QOpenGLWidget(_parent)
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  ngl::Random::instance()->setSeed();
  m_numParticles = _numParticles;
  
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}



void NGLScene::resizeGL(int _w , int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );

  m_project = ngl::perspective(45.0f, static_cast<float>(_w) / _h, 0.1f, 1000.0f);
}


void NGLScene::initializeGL()
{
  // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
  // be done once we have a valid GL context but before we call any GL commands. If we dont do
  // this everything will crash
  ngl::NGLInit::instance();
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

  //loading and activating shader
  //linking to the vertex and fragment shaders
  auto shader = ngl::ShaderLib::instance();
  shader->loadShader("ParticleShader",
      "shaders/ParticleVertex.glsl",
      "shaders/ParticleFragment.glsl");
  shader->use("ParticleShader");

  //setting camera
  m_view = ngl::lookAt({ 0,30,60 }, ngl::Vec3(0.0f, 10.0f, 0.0f), ngl::Vec3::up());
  m_emitter = std::make_unique<Emitter>(m_numParticles, ngl::Vec3(0.0f,0.3f,0.0f), 5.0f, ngl::Vec3(0.0f, 10.0f, 0.0f));

  
  //creating preset VAOprimitive 'ground' and setting its shader
  ngl::VAOPrimitives::instance()->createTrianglePlane("ground", 200, 200, 1, 1, ngl::Vec3::up());
  shader->use(ngl::nglCheckerShader);
  shader->setUniform("lightPos", 0.0f, 50.0f, 0.0f);
  shader->setUniform("lightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
  shader->setUniform("checkOn", true);
  shader->setUniform("checkSize", 20.0f);
  shader->setUniform("colour1", 0.7f, 0.7f, 0.7f, 1.0f);
  shader->setUniform("colour2", 0.8f, 0.8f, 0.8f, 1.0f);
  shader->setUniform("normalMatrix", ngl::Mat3());
    
  startTimer(0);
  m_previousTime = std::chrono::high_resolution_clock::now();

}



void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);
  auto shader = ngl::ShaderLib::instance();

  //creating mouse control vectors
  ngl::Mat4 xrot;
  ngl::Mat4 yrot;

  xrot.rotateX(m_win.spinXFace);
  yrot.rotateY(m_win.spinYFace);
  m_globalMouseTX = yrot * xrot;
  m_globalMouseTX.m_m[3][0] = m_modelPos.m_x;
  m_globalMouseTX.m_m[3][1] = m_modelPos.m_y;
  m_globalMouseTX.m_m[3][2] = m_modelPos.m_z;
  shader->use("ParticleShader");

  shader->setUniform("MVP", m_project * m_view * m_globalMouseTX);
  glPointSize(m_pointSize);
  m_emitter->draw();
  shader->use(ngl::nglCheckerShader);
  shader->setUniform("MVP", m_project * m_view * m_globalMouseTX);
  ngl::VAOPrimitives::instance()->draw("ground");

}

//----------------------------------------------------------------------------------------------------------------------



void NGLScene::timerEvent(QTimerEvent*)
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto delta = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - m_previousTime).count();
    m_emitter->update(delta);
    update();

    m_previousTime = currentTime;
}

//reset camera position when user click corresponding GUI button
void NGLScene::resetCamera()
{
    m_win.spinXFace = 0;
    m_win.spinYFace = 0;
    m_modelPos.set(ngl::Vec3::zero());
}

//changing particle size value and updating when user changes GUI value
void NGLScene::setPointSize(int _size)
{
    m_pointSize = _size;
    update();
}

//The rest of these functions are connected to the GUI and are used to call corresponding functions in the emitter class

void NGLScene::clearParticles()
{
    m_emitter->clearParticles();
}

void NGLScene::addParticle()
{
    m_emitter->addParticle();
}

void NGLScene::removeParticle()
{
    m_emitter->removeParticle();
}

void NGLScene::restart()
{
    m_emitter->restartParticles();
}



void NGLScene::groundCollide(int _gCollide)
{
    m_emitter->groundCollide(_gCollide);

}

void NGLScene::gravity(double _gCollide)
{
    m_emitter->gravity(_gCollide);
}

void NGLScene::setBounce(int _bounce)
{
    m_emitter->setBounce(_bounce);
}

void NGLScene::setNumParticles(int _numParticles)
{
    m_emitter->setNumParticles(_numParticles);
}

void NGLScene::setSpread(int _spread)
{
    m_emitter->changeSpread(_spread);  
}

void NGLScene::setMaxLife(int _maxLife)
{
    m_emitter->setMaxLife(_maxLife);
}

void NGLScene::setMinLife(int _minLife)
{
    m_emitter->setMinLife(_minLife);
}

void NGLScene::setEmitDirX(double _emitDirX)
{
    m_emitter->setEmitDirX(_emitDirX);
}

void NGLScene::setEmitDirY(double _emitDirY)
{
    m_emitter->setEmitDirY(_emitDirY);

}

void NGLScene::setEmitDirZ(double _emitDirZ)
{
    m_emitter->setEmitDirZ(_emitDirZ);

}

void NGLScene::setEmitLocX(double _emitDirX)
{
    m_emitter->emitLocX(_emitDirX);

}

void NGLScene::setEmitLocY(double _emitDirY)
{
    m_emitter->emitLocY(_emitDirY);

}

void NGLScene::setEmitLocZ(double _emitDirZ)
{
    m_emitter->emitLocZ(_emitDirZ);

}

void NGLScene::setColourR(int _colourR)
{
    m_emitter->setColourR(_colourR);
}

void NGLScene::setColourG(int _colourG)
{
    m_emitter->setColourG(_colourG);
}

void NGLScene::setColourB(int _colourB)
{
    m_emitter->setColourB(_colourB);
}






