#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Calculate final fragment color
void main()
{
	o_finalColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}