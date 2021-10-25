#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
layout (location = 0) in vec3 v_pos;

// Matrix uniforms
uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

// Out variables
out vec2 f_uv;

// Process vertex
void main()
{
	// In variables
	vec4 worldSpacePosition = (u_transformationMatrix * vec4(v_pos, 1.0f));
	vec4 viewSpacePosition  = (u_viewMatrix * worldSpacePosition);
	vec4 clipSpacePosition  = (u_projectionMatrix * viewSpacePosition);

	// GLSL variables
	gl_Position = clipSpacePosition;
}