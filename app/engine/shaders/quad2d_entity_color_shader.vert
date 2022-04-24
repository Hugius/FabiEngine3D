#version 460 core

layout (location = 0) in vec2 v_position;
layout (location = 1) in vec2 v_uv;

uniform mat4 u_transformation;

uniform vec2 u_uvMultiplier;
uniform vec2 u_uvOffset;

uniform float u_minX;
uniform float u_minY;
uniform float u_maxX;
uniform float u_maxY;

uniform int u_textureRepeat;

uniform bool u_isHorizontallyFlipped;
uniform bool u_isVerticallyFlipped;

out vec2 f_uv;

void main()
{
	vec4 worldSpacePosition = (u_transformation * vec4(v_position, 0.0f, 1.0f));

	f_uv.x = (u_isHorizontallyFlipped ? (1.0f - v_uv.x) : v_uv.x);
	f_uv.y = (u_isVerticallyFlipped ? (1.0f - v_uv.y) : v_uv.y);
	f_uv.x = ((u_uvOffset.x + (f_uv.x * u_uvMultiplier.x)) * float(u_textureRepeat));
	f_uv.y = ((u_uvOffset.y + (f_uv.y * u_uvMultiplier.y)) * float(u_textureRepeat));

	gl_Position = worldSpacePosition;
	gl_ClipDistance[0] = dot(worldSpacePosition, vec4( 1.0f,  0.0f,  0.0f, -u_minX));
	gl_ClipDistance[1] = dot(worldSpacePosition, vec4(-1.0f,  0.0f,  0.0f,  u_maxX));
	gl_ClipDistance[2] = dot(worldSpacePosition, vec4( 0.0f,  1.0f,  0.0f, -u_minY));
	gl_ClipDistance[3] = dot(worldSpacePosition, vec4( 0.0f, -1.0f,  0.0f,  u_maxY));
}