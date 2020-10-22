Morgan Moore Programming
Controls: All controls are in the GUI. There are no keyboard controls. Hold Right mouse button to pan scene Hold Left mouse button to rotate

N.B. In visual studio I ran the project on 'release' mode, 'debug' mode gave many unknown errors.

The task of this project was to develop a set of C++ classes/data structures and algorithms that provide a high-level OpenGL object/scene management. I decided to develop a particle system that would allow the simulation of real-world physics such as gravity and friction springs e.g. collisions.

Initial Research:

A primary source of information for this project was from the slides and lectures provided by Jon Macey. There were also several other resources that I used for this project to develop my understanding of OpenGL, Object Oriented Programming, Particle Systems, GUI setup etc

1.Reeves, W., 1983. Particle Systems—a Technique for Modelling a Class of Fuzzy Objects. ACM Transactions on Graphics (TOG), 2(2), pp.91-108.

This paper introduces the topic of creating particle systems and presents methods for specific systems including smoke water and fire. The paper covers ways of representing particle motion, changes of form and various other dynamic.

2.CopperSpice, 2020. Modern C++ (Data Types, References). [online] YouTube. Available at: https://www.youtube.com/watch?time_continue=10&v=1QT9HnCkz4I&feature=emb_logo [Accessed 2 April 2020].

This channel provides many lessons on Modern C++. I followed the lessons titled 'From the Beginning to the Middle' in order to learn the fundamentals of C++ including data Types Lambdas, classes, structs, Namespaces, pointers, and the C++ Standard library.

3.Banas, D., 2020. Derek Banas. [online] YouTube. Available at: https://www.youtube.com/watch?v=ZOKLjJF54Xc [Accessed 2 April 2020].

This tutorial covers the crucial topics of Object-Oriented Programming, Private, Public, Constructors, and inheritance. This tutorial allowed me to put these concepts into practice and learn the fundamentals.

4.Gordon, V. and Clevenger, J., n.d. Computer Graphics Programming in Opengl with C++.

This book provided an in-depth look at working with OpenGl and C++. It covered topics including the OpenGL graphics pipeline, Maths for Computer Graphics, Managing 3D data and shading. The 'Getting started' chapter and the 'Pipeline' chapter were particularly helpful in understanding some of the fundamentals of OpenGL.

5.Gamma, E., Helm, R., Johnson, R., Vlissides, J. and Booch, G., 1994. Design Patterns: Elements of Reusable Object-Oriented Software. Boston: Addison Wesley Professional.

This book describes Object-oriented programming in detail. It outlines several design patterns and a case study to demonstrate some of these concepts.

Design Consideration:

In order to consider the design of the project I looked at various other example of OpenGL/c++ applications and also GUI designs from both lecture/tutorials and my own personal research. From this research I was able to consider how to create an object-oriented program. This type of program arranges its design around objects/data rather than functions and logic. These objects can contain data fields, as well as procedures. An interface/methods corresponding to this data is then used to apply it.

Through several iterations I was able to develop my code from initially creating a window, to having a fully functioning scene with several particle controls and a GUI. Some of the key algorithms and steps include:

Creating a collision function to create bounce vectors when particle hits ground level. Since the ground is a flat plane the new bounce vector is simply the current vector j value * -1. I then use the float scalar parameter 'm_dampener' as defined by the user to reduce the speed of the particle after each bounce. 'm_dampener' is used to approximate the loss of kinetic energy and the effect of friction.

Using the ‘Emitter::draw()’ function to draw particles in the scene. This involved setting data to the ‘vao’, including the size of the structure ‘m_particles’, a pointer to the first element and the number of particles. When draw is called ‘vao’ is reset the current frame particle data. The format of the data structure ‘m_particles’ also needed to be defined so that each individual element could be accessed.

Creating the 'resetParticles' function which creates new instances of particles. The data of these particles is then defined including their direction vector, colour, and lifespan, and some randomness is used.

A key part of this project was the GUI. This was setup using Qtcreator and designed using Qtdesigner. Setting up the GUI required a well-planned layout. I used group boxes and spacers to define this layout and used a mixture of input widgets and buttons to receive user inputs. In the MainWindow.cpp file connections were made between the GUI widgets and corresponding function set up as 'slots' in scene.h. The values could then be used in various functions to update the particle system with new data.
