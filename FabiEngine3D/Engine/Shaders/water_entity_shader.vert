#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec2 v_uv;

// Uniforms
uniform mat4  u_viewMatrix;
uniform mat4  u_projectionMatrix;
uniform float u_uvRepeat;
uniform float u_timeX;
uniform float u_timeZ;
uniform float u_customHeightOffset;
uniform bool  u_waving;

// Out variables
out vec4 f_clip;
out vec2 f_uv;
out vec3 f_pos;

// Main function
void main()
{
	// In variables
	vec3 newPos = v_pos;
	newPos.y += u_customHeightOffset;

	// Water sine waves
	if(u_waving)
	{
		//newPos.y += (sin(newPos.x * u_timeX) * cos(newPos.z * u_timeZ));
	}

	// Camera spaces
	vec4 worldSpace = vec4(v_pos, 1.0);
	vec4 clipSpace  = u_projectionMatrix * u_viewMatrix * vec4(newPos, 1.0);

	// GLSL variables
	gl_Position = clipSpace;

	// Out variables
	f_pos  = worldSpace.xyz;
	f_uv   = vec2(v_uv.x / 2.0 + 0.5, v_uv.y / 2.0 + 0.5) * u_uvRepeat;
	f_clip = clipSpace;
}