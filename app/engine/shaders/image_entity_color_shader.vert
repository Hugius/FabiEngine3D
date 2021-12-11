#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
layout (location = 0) in vec2 v_pos;
layout (location = 1) in vec2 v_uv;

// Matrix uniforms
uniform mat4 u_transformationMatrix;

// Vector uniforms
uniform vec2 u_adderUV;
uniform vec2 u_multiplierUV;

// Boolean uniforms
uniform bool u_isMirroredHorizontally;
uniform bool u_isMirroredVertically;

// Out variables
out vec2 f_uv;

// Process vertex
void main()
{
	gl_Position = (u_transformationMatrix * vec4(v_pos, 0.0f, 1.0f));
	f_uv.x = u_isMirroredHorizontally ? -v_uv.x : v_uv.x;
	f_uv.y = u_isMirroredVertically ? v_uv.y : -v_uv.y; 
	f_uv = vec2(u_adderUV.x + (f_uv.x * u_multiplierUV.x), u_adderUV.y + (f_uv.y * u_multiplierUV.y));
}