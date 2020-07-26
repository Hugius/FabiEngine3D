#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
layout(location = 0) in vec3 v_pos;

// Matrix44 uniforms
uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projMatrix;

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
}