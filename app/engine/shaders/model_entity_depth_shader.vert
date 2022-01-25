#version 460 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_uv;

uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

uniform vec3 u_minX;
uniform vec3 u_minY;
uniform vec3 u_minZ;
uniform vec3 u_maxX;
uniform vec3 u_maxY;
uniform vec3 u_maxZ;

uniform float u_textureRepeat;

out vec2 f_uv;

void main()
{
	vec4 worldSpacePosition = (u_transformationMatrix * vec4(v_position, 1.0f));
	vec4 viewSpacePosition  = (u_viewMatrix * worldSpacePosition);
	vec4 clipSpacePosition  = (u_projectionMatrix * viewSpacePosition);

	f_uv = (v_uv * u_textureRepeat);

	gl_Position = clipSpacePosition;
	gl_ClipDistance[0] = dot(worldSpacePosition, vec4( 1.0f,  0.0f,  0.0f, -u_minX));
	gl_ClipDistance[1] = dot(worldSpacePosition, vec4(-1.0f,  0.0f,  0.0f,  u_maxX));
	gl_ClipDistance[2] = dot(worldSpacePosition, vec4( 0.0f,  1.0f,  0.0f, -u_minY));
	gl_ClipDistance[3] = dot(worldSpacePosition, vec4( 0.0f, -1.0f,  0.0f,  u_maxY));
	gl_ClipDistance[4] = dot(worldSpacePosition, vec4( 0.0f,  0.0f,  1.0f, -u_minZ));
	gl_ClipDistance[5] = dot(worldSpacePosition, vec4( 0.0f,  0.0f, -1.0f,  u_maxZ));
}