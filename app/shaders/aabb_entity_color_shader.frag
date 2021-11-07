#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// Constant variables
#define FRAME_COLOR vec3(1.0f, 0.0f, 0.0f)

// Out variables
layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

// Process fragments
void main()
{
	// Apply gamma correction
	vec3 primaryColor = pow(FRAME_COLOR, vec3(1.0f / 2.2f));

	// Set final colors
	o_primaryColor = vec4(primaryColor, 1.0f);
	o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}