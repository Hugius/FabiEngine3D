#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
in vec2 f_uv;

// Textures
uniform sampler2D u_sampler_scene;

// Out variables
layout (location = 0) out vec4 o_finalColor;

void main()
{
	o_finalColor = texture(u_sampler_scene, f_uv);
}