#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
layout (location = 0) in vec3 v_pos;

// Matrix uniforms
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

// Process vertex
void main()
{
	// In variables
	vec4 worldSpacePos = vec4(v_pos, 1.0f);
	vec4 viewSpacePos  = (u_viewMatrix * worldSpacePos);
	vec4 clipSpacePos  = (u_projectionMatrix * viewSpacePos);

	// GLSL variables
	gl_Position = clipSpacePos;
}