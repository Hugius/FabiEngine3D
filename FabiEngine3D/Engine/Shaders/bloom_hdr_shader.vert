#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

layout(location = 0) in vec2 v_pos;
layout(location = 1) in vec2 v_uv;

// Matrix44 uniforms
uniform mat4 u_modelMatrix;

// Boolean uniforms
uniform bool u_mirrorHor;
uniform bool u_mirrorVer;

out vec2 f_uv;

void main()
{
	gl_Position = u_modelMatrix * vec4(v_pos, 0.0f, 1.0f);
	f_uv.x = u_mirrorHor ? -v_uv.x : v_uv.x;
	f_uv.y = u_mirrorVer ?  v_uv.y : -v_uv.y; 
}