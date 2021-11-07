#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
layout (location = 0) in vec2 v_pos;
layout (location = 1) in vec2 v_uv;

// Out variables
out vec2 f_uv;

// Process vertex
void main()
{
	gl_Position = vec4(v_pos, 0.0f, 1.0f);
	f_uv = v_uv;
}