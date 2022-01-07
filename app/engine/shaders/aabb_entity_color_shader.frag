#version 460 core

uniform vec3 u_color;

layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

void main()
{
	vec3 primaryColor = pow(u_color, vec3(1.0f / 2.2f));

	o_primaryColor = vec4(primaryColor, 1.0f);
	o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}