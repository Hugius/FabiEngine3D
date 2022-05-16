#version 460 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_uv;

uniform mat4 u_cameraView;
uniform mat4 u_cameraProjection;

uniform float u_minX;
uniform float u_minY;
uniform float u_minZ;
uniform float u_maxX;
uniform float u_maxY;
uniform float u_maxZ;
uniform float u_height;

void main()
{
	vec3 position = vec3(v_position.x, u_height, v_position.z);
	vec4 worldSpacePosition = vec4(position, 1.0f);
	vec4 viewSpacePosition = (u_cameraView * worldSpacePosition);
	vec4 clipSpacePosition = (u_cameraProjection * viewSpacePosition);

	gl_Position = clipSpacePosition;
	gl_ClipDistance[0] = dot(worldSpacePosition, vec4( 1.0f,  0.0f,  0.0f, -u_minX));
	gl_ClipDistance[1] = dot(worldSpacePosition, vec4(-1.0f,  0.0f,  0.0f,  u_maxX));
	gl_ClipDistance[2] = dot(worldSpacePosition, vec4( 0.0f,  1.0f,  0.0f, -u_minY));
	gl_ClipDistance[3] = dot(worldSpacePosition, vec4( 0.0f, -1.0f,  0.0f,  u_maxY));
	gl_ClipDistance[4] = dot(worldSpacePosition, vec4( 0.0f,  0.0f,  1.0f, -u_minZ));
	gl_ClipDistance[5] = dot(worldSpacePosition, vec4( 0.0f,  0.0f, -1.0f,  u_maxZ));
}