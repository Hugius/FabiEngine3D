#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
in vec2 f_uv;

// Textures
layout (location = 0) uniform sampler2D u_sceneMap;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Process fragment
void main()
{
	o_finalColor = texture(u_sceneMap, f_uv);
}