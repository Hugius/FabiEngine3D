#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
layout(location = 0) in vec2 v_pos;
layout(location = 1) in vec2 v_uv;

// Matrix44 uniforms
uniform mat4 u_modelMatrix;

// Vec2 uniforms
uniform vec2 u_uvAdder;
uniform vec2 u_uvMultiplier;

// Boolean uniforms
uniform bool u_isMirroredHorizontally;
uniform bool u_isMirroredVertically;

// Out variables
out vec2 f_uv;

void main()
{
	gl_Position = u_modelMatrix * vec4(v_pos, 0.0f, 1.0f);
	f_uv.x = u_isMirroredHorizontally ? -v_uv.x : v_uv.x;
	f_uv.y = u_isMirroredVertically ? v_uv.y : -v_uv.y; 
	f_uv = vec2(u_uvAdder.x + (f_uv.x * u_uvMultiplier.x), u_uvAdder.y + (f_uv.y * u_uvMultiplier.y));
}