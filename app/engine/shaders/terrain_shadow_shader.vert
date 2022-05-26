#version 460 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_uv;

uniform mat4 u_transformation;
uniform mat4 u_shadowView;
uniform mat4 u_shadowProjection;

uniform float u_minX;
uniform float u_minY;
uniform float u_minZ;
uniform float u_maxX;
uniform float u_maxY;
uniform float u_maxZ;

uniform int u_textureRepeat;

out vec2 f_uv;

void main()
{
	vec4 worldSpacePosition = (u_transformation * vec4(v_position, 1.0f));
	vec4 shadowSpacePosition = (u_shadowProjection * u_shadowView * worldSpacePosition);

	f_uv = (v_uv * float(u_textureRepeat));

	gl_Position = shadowSpacePosition;
	gl_ClipDistance[0] = dot(worldSpacePosition, vec4( 1.0f,  0.0f,  0.0f, -u_minX));
	gl_ClipDistance[1] = dot(worldSpacePosition, vec4(-1.0f,  0.0f,  0.0f,  u_maxX));
	gl_ClipDistance[2] = dot(worldSpacePosition, vec4( 0.0f,  1.0f,  0.0f, -u_minY));
	gl_ClipDistance[3] = dot(worldSpacePosition, vec4( 0.0f, -1.0f,  0.0f,  u_maxY));
	gl_ClipDistance[4] = dot(worldSpacePosition, vec4( 0.0f,  0.0f,  1.0f, -u_minZ));
	gl_ClipDistance[5] = dot(worldSpacePosition, vec4( 0.0f,  0.0f, -1.0f,  u_maxZ));
}