#version 410 core


layout (location =0) out vec4 fragColour;
//recieving colour from vertex shader
in vec3 particleColour;

void main()
{
	//setting colour of frag shader
	fragColour.rgb=particleColour;

}