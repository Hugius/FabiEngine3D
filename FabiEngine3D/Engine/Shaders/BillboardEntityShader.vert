#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec2 v_uv;

// Uniforms
uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projMatrix;
uniform vec2 u_uvAdder;
uniform vec2 u_uvMultiplier;
uniform float u_uvRepeat;

// Out variables
out vec2 f_uv;

void main()
{
	// In variables
	vec4 worldSpacePos = u_modelMatrix * vec4(v_pos, 1.0f);
	vec4 viewSpacePos  = u_viewMatrix * worldSpacePos;
	vec4 clipSpacePos  = u_projMatrix * viewSpacePos;

	// GLSL variables
	gl_Position = clipSpacePos;
	
	// Out variables
	f_uv = vec2(u_uvAdder.x + (v_uv.x*u_uvMultiplier.x), u_uvAdder.y + (-v_uv.y*u_uvMultiplier.y)) *u_uvRepeat;
}