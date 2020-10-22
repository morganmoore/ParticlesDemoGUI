#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_gl = new NGLScene(20000);
    //defining layout of scene widget on GUI
    ui->gridLayout->addWidget(m_gl, 0, 1, 2, 6);

    //connecting buttons, sliders, check boxes, spin boxes etc to corresponding 'slot' functions declared in NGLScene.h
    connect(ui->clearAll, SIGNAL(clicked()), m_gl, SLOT(clearParticles()));
    connect(ui->addParticle, SIGNAL(clicked()), m_gl, SLOT(addParticle()));
    connect(ui->removeParticle, SIGNAL(clicked()), m_gl, SLOT(removeParticle()));
    connect(ui->restart, SIGNAL(clicked()), m_gl, SLOT(restart()));
    connect(ui->cameraReset, SIGNAL(clicked()), m_gl, SLOT(resetCamera()));

    connect(ui->groundCollide, SIGNAL(stateChanged(int)), m_gl, SLOT(groundCollide(int)));

    connect(ui->pointSize, SIGNAL(valueChanged(int)), m_gl, SLOT(setPointSize(int)));
    connect(ui->setSpread, SIGNAL(valueChanged(int)), m_gl, SLOT(setSpread(int)));
    connect(ui->numParticles, SIGNAL(valueChanged(int)), m_gl, SLOT(setNumParticles(int)));
    connect(ui->maxLife, SIGNAL(valueChanged(int)), m_gl, SLOT(setMaxLife(int)));
    connect(ui->minLife, SIGNAL(valueChanged(int)), m_gl, SLOT(setMinLife(int)));
    connect(ui->bounce, SIGNAL(valueChanged(int)), m_gl, SLOT(setBounce(int)));

    connect(ui->rColour, SIGNAL(valueChanged(int)), m_gl, SLOT(setColourR(int)));
    connect(ui->gColour, SIGNAL(valueChanged(int)), m_gl, SLOT(setColourG(int)));
    connect(ui->bColour, SIGNAL(valueChanged(int)), m_gl, SLOT(setColourB(int)));
    connect(ui->xDir, SIGNAL(valueChanged(double)), m_gl, SLOT(setEmitDirX(double)));
    connect(ui->yDir, SIGNAL(valueChanged(double)), m_gl, SLOT(setEmitDirY(double)));
    connect(ui->zDir, SIGNAL(valueChanged(double)), m_gl, SLOT(setEmitDirZ(double)));
    connect(ui->xLoc, SIGNAL(valueChanged(double)), m_gl, SLOT(setEmitLocX(double)));
    connect(ui->yLoc, SIGNAL(valueChanged(double)), m_gl, SLOT(setEmitLocY(double)));
    connect(ui->zLoc, SIGNAL(valueChanged(double)), m_gl, SLOT(setEmitLocZ(double)));

    connect(ui->gravity, SIGNAL(valueChanged(double)), m_gl, SLOT(gravity(double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

