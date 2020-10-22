#version 410 core
//shader takes two Vec3s, position and colour,
//using layouts to access these inputs when draw function is called
layout (location = 0) in vec3 pos;
layout(location =1) in vec3 colour;

//attributes only available in vertex shader
//colour is used in fragment shader and is passed here from vertex shader.
out vec3 particleColour;
//adding model view project for camera
uniform mat4 MVP;

void main()
{
	particleColour=colour;
	gl_Position = MVP * vec4(pos,1);
}