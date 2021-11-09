#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_uv;
layout (location = 4) in vec3 v_offset;

// Matrix uniforms
uniform mat4 u_transformationMatrix;
uniform mat4 u_lightSpaceMatrix;

// Float uniforms
uniform float u_positionY;
uniform float u_minHeight;
uniform float u_maxHeight;

// Boolean uniforms
uniform bool u_isInstanced;

// Out variables
out vec2 f_uv;

// Process vertex
void main()
{
	// In variables
	vec4 worldSpacePosition = (u_transformationMatrix * vec4(v_pos, 1.0f)) + ((u_isInstanced == true) ? vec4(v_offset, 0.0f) : vec4(0.0f));
	vec4 lightSpacePosition = (u_lightSpaceMatrix * worldSpacePosition);

	// GLSL variables
	gl_Position = lightSpacePosition;
	gl_ClipDistance[0] = dot(worldSpacePosition, vec4(0.0f,  1.0f, 0.0f, -(u_positionY + u_minHeight)));
	gl_ClipDistance[1] = dot(worldSpacePosition, vec4(0.0f, -1.0f, 0.0f,  (u_positionY + u_maxHeight)));
	
	// Out variables
	f_uv = vec2(v_uv.x, -v_uv.y);
}