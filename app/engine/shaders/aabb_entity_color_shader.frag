#version 330 core
#extension GL_ARB_explicit_uniform_location : require

uniform vec3 u_color;

layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

void main()
{
	// Apply gamma correction
	vec3 primaryColor = pow(u_color, vec3(1.0f / 2.2f));

	// Set final colors
	o_primaryColor = vec4(primaryColor, 1.0f);
	o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}