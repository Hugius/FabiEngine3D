#version 460 core

layout (location = 0) in vec2 v_position;
layout (location = 1) in vec2 v_uv;

uniform mat4 u_transformationMatrix;

uniform vec2 u_uvMultiplier;
uniform vec2 u_uvOffset;

uniform bool u_isMirroredHorizontally;
uniform bool u_isMirroredVertically;

out vec2 f_uv;

void main()
{
	gl_Position = (u_transformationMatrix * vec4(v_position, 0.0f, 1.0f));
	f_uv.x = (u_isMirroredHorizontally ? (1.0f - v_uv.x) : v_uv.x);
	f_uv.y = (u_isMirroredVertically ? (1.0f - v_uv.y) : v_uv.y);
	f_uv.x = (u_uvOffset.x + (f_uv.x * u_uvMultiplier.x));
	f_uv.y = (u_uvOffset.y + (f_uv.y * u_uvMultiplier.y));
}