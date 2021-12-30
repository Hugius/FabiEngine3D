#version 330 core
#extension GL_ARB_explicit_uniform_location : require

layout (location = 0) in vec2 v_position;
layout (location = 1) in vec2 v_uv;

uniform mat4 u_transformationMatrix;

uniform vec2 u_multiplierUV;
uniform vec2 u_adderUV;

uniform bool u_isMirroredHorizontally;
uniform bool u_isMirroredVertically;

out vec2 f_uv;

void main()
{
	gl_Position = (u_transformationMatrix * vec4(v_position, 0.0f, 1.0f));
	f_uv.x = (u_isMirroredHorizontally ? -v_uv.x : v_uv.x);
	f_uv.y = (u_isMirroredVertically ? -v_uv.y : v_uv.y);
	f_uv.x = (u_adderUV.x + (f_uv.x * u_multiplierUV.x));
	f_uv.y = (u_adderUV.y + (f_uv.y * u_multiplierUV.y));
}