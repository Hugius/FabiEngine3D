#version 460 core

layout (location = 0) in vec2 v_position;
layout (location = 1) in vec2 v_uv;

uniform mat4 u_transformation;

uniform vec2 u_uvMultiplier;
uniform vec2 u_uvOffset;

uniform bool u_isHorizontallyFlipped;
uniform bool u_isVerticallyFlipped;

out vec2 f_uv;

void main()
{
	f_uv.x = (u_isHorizontallyFlipped ? (1.0f - v_uv.x) : v_uv.x);
	f_uv.y = (u_isVerticallyFlipped ? (1.0f - v_uv.y) : v_uv.y);
	f_uv.x = (u_uvOffset.x + (f_uv.x * u_uvMultiplier.x));
	f_uv.y = (u_uvOffset.y + (f_uv.y * u_uvMultiplier.y));

	gl_Position = (u_transformation * vec4(v_position, 0.0f, 1.0f));
}