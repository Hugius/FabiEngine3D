#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
in vec3 f_uv;

// Textures
uniform samplerCube u_sampler_cubeMap;

// Float uniforms
uniform float u_lightness;

// Vec3 uniforms
uniform vec3 u_color;

// Out variables
layout (location = 0) out vec4 o_finalColor;

void main()
{
	o_finalColor.rgb = texture(u_sampler_cubeMap, f_uv).rgb;
	o_finalColor.rgb *= u_color;
	o_finalColor.rgb *= u_lightness;
	o_finalColor.a = 1.0f;
}