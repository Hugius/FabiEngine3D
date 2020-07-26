#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
layout(location = 0) in vec2 v_pos;
layout(location = 1) in vec2 v_uv;

// Out variables
out vec2 f_pos;
out vec2 f_uv;

void main() 
{
	gl_Position = vec4(v_pos, 0.0f, 1.0f);
	f_pos = v_pos;
	f_uv = v_uv;
}