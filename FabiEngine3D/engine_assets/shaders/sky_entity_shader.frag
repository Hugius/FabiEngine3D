#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
in vec3 f_uv;

// Textures
layout(location = 0) uniform samplerCube u_sampler_mainCubeMap;
layout(location = 1) uniform samplerCube u_sampler_mixCubeMap;

// Float uniforms
uniform float u_mainLightness;
uniform float u_mixLightness;
uniform float u_mixValue;

// Vec3 uniforms
uniform vec3 u_mainColor;
uniform vec3 u_mixColor;

// Out variables
layout (location = 0) out vec4 o_finalColor;

void main()
{
	vec3 mainColor = texture(u_sampler_mainCubeMap, f_uv).rgb * u_mainColor;
	vec3 mixColor = texture(u_sampler_mixCubeMap, f_uv).rgb * u_mixColor;
	float mixValue = clamp(u_mixValue, 0.0, 1.0f);
	float lightness = mix(u_mainLightness, u_mixLightness, mixValue);
	o_finalColor.rgb = mix(mainColor, mixColor, mixValue);
	o_finalColor.rgb *= lightness;
	o_finalColor.a = 1.0f;
}