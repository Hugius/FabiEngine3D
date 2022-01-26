#version 460 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_uv;

layout (location = 0) uniform sampler2D u_displacementMap;

uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

uniform vec2 u_waveOffset;

uniform float u_minX;
uniform float u_minY;
uniform float u_minZ;
uniform float u_maxX;
uniform float u_maxY;
uniform float u_maxZ;
uniform float u_height;
uniform float u_textureRepeat;
uniform float u_waveHeight;

uniform bool u_hasDisplacementMap;

void main()
{
	vec3 newPosition = v_position;
	newPosition.y = u_height;

	if (u_hasDisplacementMap)
	{
		vec2 texelSize = (vec2(1.0f) / textureSize(u_displacementMap, 0));
		float heightPercentage = texture(u_displacementMap, ((v_uv * u_textureRepeat) + (u_waveOffset * texelSize))).r;
		newPosition.y += (heightPercentage * u_waveHeight);
	}

	vec4 worldSpacePosition = vec4(newPosition, 1.0f);
	vec4 clipSpacePosition  = (u_projectionMatrix * u_viewMatrix * vec4(newPosition, 1.0f));

	gl_Position = clipSpacePosition;
	gl_ClipDistance[0] = dot(worldSpacePosition, vec4( 1.0f,  0.0f,  0.0f, -u_minX));
	gl_ClipDistance[1] = dot(worldSpacePosition, vec4(-1.0f,  0.0f,  0.0f,  u_maxX));
	gl_ClipDistance[2] = dot(worldSpacePosition, vec4( 0.0f,  1.0f,  0.0f, -u_minY));
	gl_ClipDistance[3] = dot(worldSpacePosition, vec4( 0.0f, -1.0f,  0.0f,  u_maxY));
	gl_ClipDistance[4] = dot(worldSpacePosition, vec4( 0.0f,  0.0f,  1.0f, -u_minZ));
	gl_ClipDistance[5] = dot(worldSpacePosition, vec4( 0.0f,  0.0f, -1.0f,  u_maxZ));
}