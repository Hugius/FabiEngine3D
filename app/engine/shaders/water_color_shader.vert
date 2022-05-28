#version 460 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_uv;

layout (location = 5) uniform sampler2D u_heightMap;

uniform mat4 u_cameraView;
uniform mat4 u_cameraProjection;
uniform mat4 u_shadowView;
uniform mat4 u_shadowProjection;

uniform vec2 u_waveOffset;

uniform float u_minX;
uniform float u_minY;
uniform float u_minZ;
uniform float u_maxX;
uniform float u_maxY;
uniform float u_maxZ;
uniform float u_height;
uniform float u_waveHeight;

uniform int u_textureRepeat;

uniform bool u_hasHeightMap;

out vec4 f_shadowSpacePos;
out vec3 f_worldSpacePos;
out vec4 f_clipSpacePos;
out vec2 f_uv;

void main()
{
	vec3 newPosition = v_position;
	newPosition.y = u_height;

	if(u_hasHeightMap)
	{
		float heightPercentage = texture(u_heightMap, ((v_uv * float(u_textureRepeat)) + (u_waveOffset))).r;
		newPosition.y += (heightPercentage * u_waveHeight);
	}

	vec4 worldSpacePosition = vec4(newPosition, 1.0f);
	vec4 viewSpacePosition = (u_cameraView * worldSpacePosition);
	vec4 clipSpacePosition = (u_cameraProjection * viewSpacePosition);

	f_shadowSpacePos = (u_shadowProjection * u_shadowView * worldSpacePosition);
	f_worldSpacePos = worldSpacePosition.xyz;
	f_clipSpacePos = clipSpacePosition;
	f_uv = (v_uv * float(u_textureRepeat));

	gl_Position = clipSpacePosition;
	gl_ClipDistance[0] = dot(worldSpacePosition, vec4( 1.0f,  0.0f,  0.0f, -u_minX));
	gl_ClipDistance[1] = dot(worldSpacePosition, vec4(-1.0f,  0.0f,  0.0f,  u_maxX));
	gl_ClipDistance[2] = dot(worldSpacePosition, vec4( 0.0f,  1.0f,  0.0f, -u_minY));
	gl_ClipDistance[3] = dot(worldSpacePosition, vec4( 0.0f, -1.0f,  0.0f,  u_maxY));
	gl_ClipDistance[4] = dot(worldSpacePosition, vec4( 0.0f,  0.0f,  1.0f, -u_minZ));
	gl_ClipDistance[5] = dot(worldSpacePosition, vec4( 0.0f,  0.0f, -1.0f,  u_maxZ));
}