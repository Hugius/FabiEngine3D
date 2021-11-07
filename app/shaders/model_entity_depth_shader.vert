#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_uv;
layout (location = 4) in vec3 v_offset;

// Matrix uniforms
uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

// Float uniforms
uniform float u_positionY;
uniform float u_minHeight;
uniform float u_maxHeight;
uniform float u_clippingY;

// Boolean uniforms
uniform bool u_isInstanced;
uniform bool u_isUnderWater;

// Out variables
out vec2 f_uv;

// Process vertex
void main()
{
	// In variables
	vec4 worldSpacePosition = (u_transformationMatrix * vec4(v_pos, 1.0f)) + ((u_isInstanced == true) ? vec4(v_offset, 0.0f) : vec4(0.0f));
	vec4 viewSpacePosition  = (u_viewMatrix * worldSpacePosition);
	vec4 clipSpacePosition  = (u_projectionMatrix * viewSpacePosition);

	// GLSL variables
	gl_Position = clipSpacePosition;
	gl_ClipDistance[0] = dot(worldSpacePosition, vec4(0.0f,  1.0f, 0.0f, -(u_positionY + u_minHeight)));
	gl_ClipDistance[1] = dot(worldSpacePosition, vec4(0.0f, -1.0f, 0.0f,  (u_positionY + u_maxHeight)));
	gl_ClipDistance[2] = dot(worldSpacePosition, vec4(0.0f, u_isUnderWater ? -1.0f : 1.0f, 0.0f, u_isUnderWater ? u_clippingY : -u_clippingY));

	// Out variables
	f_uv = vec2(v_uv.x, -v_uv.y);
}