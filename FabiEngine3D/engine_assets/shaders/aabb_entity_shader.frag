#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// Out variables
layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

// Process fragments
void main()
{
	o_primaryColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}