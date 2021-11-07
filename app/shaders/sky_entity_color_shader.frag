#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// Constant variables
#define FRAME_COLOR vec3(1.0f, 1.0f, 1.0f)

// In variables
in vec3 f_uv;

// Textures
layout (location = 0) uniform samplerCube u_mainCubeMap;
layout (location = 1) uniform samplerCube u_mixCubeMap;

// Float uniforms
uniform float u_mainLightness;
uniform float u_mixLightness;
uniform float u_mixValue;

// Vector uniforms
uniform vec3 u_mainColor;
uniform vec3 u_mixColor;

// Boolean uniforms
uniform bool u_isWireFramed;

// Out variables
layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

// Process fragment
void main()
{
	// Wire frame color
	if(u_isWireFramed)
	{
		o_primaryColor = vec4(FRAME_COLOR, 1.0f);
		o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
		return;
	}

	// Sky colors
	vec3 mainColor = texture(u_mainCubeMap, f_uv).rgb;
	vec3 mixColor  = texture(u_mixCubeMap, f_uv).rgb;
	mainColor = pow(mainColor, vec3(2.2f));
	mixColor = pow(mixColor, vec3(2.2f));
	mainColor *= u_mainColor;
	mixColor *= u_mixColor;

	// Apply mixing & lightness
	float mixValue  = clamp(u_mixValue, 0.0, 1.0f);
	float lightness = mix(u_mainLightness, u_mixLightness, mixValue);

	// Calculate base color
	vec3 primaryColor;
	primaryColor  = mix(mainColor, mixColor, mixValue);
	primaryColor *= lightness;
	primaryColor  = clamp(primaryColor, vec3(0.0f), vec3(1.0f));

	// Apply gamma correction
	primaryColor = pow(primaryColor, vec3(1.0f / 2.2f));

	// Set final colors
	o_primaryColor   = vec4(primaryColor, 1.0f);
	o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}