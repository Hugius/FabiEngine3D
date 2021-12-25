#version 330 core
#extension GL_ARB_explicit_uniform_location : require

layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_uv;

uniform mat4 u_transformationMatrix;
uniform mat4 u_lightSpaceMatrix;

uniform float u_minHeight;
uniform float u_maxHeight;

out vec2 f_uv;

void main()
{
	vec4 worldSpacePosition = (u_transformationMatrix * vec4(v_pos, 1.0f));
	vec4 lightSpacePosition = (u_lightSpaceMatrix * worldSpacePosition);

	gl_Position = lightSpacePosition;
	gl_ClipDistance[0] = dot(worldSpacePosition, vec4(0.0f,  1.0f, 0.0f, -u_minHeight));
	gl_ClipDistance[1] = dot(worldSpacePosition, vec4(0.0f, -1.0f, 0.0f,  u_maxHeight));
	
	f_uv = vec2(v_uv.x, -v_uv.y);
}