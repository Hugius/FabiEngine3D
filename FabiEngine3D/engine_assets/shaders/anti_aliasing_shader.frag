#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// Constant variables
#define LUMINOSITY_VECTOR vec3(0.299f, 0.587f, 0.114f)
#define MAX_DIRECTION_TEXELS 8.0f
#define MIN_DIRECTION_ADDER 0.0078125f
#define LUMINOSITY_MULTIPLIER 0.03125f

// In variables
in vec2 f_uv;

// Textures
layout (location = 0) uniform sampler2D u_sceneMap;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Process fragment
void main()
{
	// Calculate texel size
	vec2 texelSize = (vec2(1.0f) / textureSize(u_sceneMap, 0));

	// Calculate luminosities
	float luminosityTL = dot(LUMINOSITY_VECTOR, texture(u_sceneMap, f_uv + (vec2(-1.0f, -1.0f) * texelSize)).rgb);
	float luminosityTR = dot(LUMINOSITY_VECTOR, texture(u_sceneMap, f_uv + (vec2(1.0f, -1.0f) * texelSize)).rgb);
	float luminosityBL = dot(LUMINOSITY_VECTOR, texture(u_sceneMap, f_uv + (vec2(-1.0f, 1.0f) * texelSize)).rgb);
	float luminosityBR = dot(LUMINOSITY_VECTOR, texture(u_sceneMap, f_uv + (vec2(1.0f, 1.0f) * texelSize)).rgb);
	float luminosityMM = dot(LUMINOSITY_VECTOR, texture(u_sceneMap, f_uv).rgb);

	// Calculate luminosity direction
	vec2 direction;
	direction.x = -((luminosityTL + luminosityTR) - (luminosityBL + luminosityBR));
	direction.y =  ((luminosityTL + luminosityBL) - (luminosityTR + luminosityBR));
	
	// Calculate direction adder
	float directionAdder = max((luminosityTL + luminosityTR + luminosityBL + luminosityBR) * LUMINOSITY_MULTIPLIER, MIN_DIRECTION_ADDER);

	// Calculate direction adder multiplier
	float directionMultiplier = (1.0f / (min(abs(direction.x), abs(direction.y)) + directionAdder));
	
	// Clamp direction to maximum texel range
	direction = (clamp((direction * directionMultiplier), -MAX_DIRECTION_TEXELS, MAX_DIRECTION_TEXELS) * texelSize);

	// Calculate close range blur
	vec3 closeBlur = vec3(0.0f);
	closeBlur += (texture(u_sceneMap, f_uv + (direction * vec2((1.0f / 3.0f) - 0.5f))).rgb * 0.5f);
	closeBlur += (texture(u_sceneMap, f_uv + (direction * vec2((2.0f / 3.0f) - 0.5f))).rgb * 0.5f);

	// Calculate far range blur
	vec3 farBlur = (closeBlur * 0.5f);
	farBlur += (texture(u_sceneMap, f_uv + (direction * vec2(-0.5f))).rgb * 0.25f);
	farBlur += (texture(u_sceneMap, f_uv + (direction * vec2(0.5f))).rgb * 0.25f);

	// Calculate minimum luminosity
	float minLuminosity = min(luminosityMM, min(min(luminosityTL, luminosityTR), min(luminosityBL, luminosityBR)));

	// Calculate maximum luminosity
	float maxLuminosity = max(luminosityMM, max(max(luminosityTL, luminosityTR), max(luminosityBL, luminosityBR)));

	// Calculate current blur luminosity
	float blurLuminosity = dot(LUMINOSITY_VECTOR, farBlur);
	
	if ((blurLuminosity < minLuminosity) || (blurLuminosity > maxLuminosity)) // Blur is outside of range
	{
		o_finalColor = vec4(closeBlur, 1.0);
	}
	else // Blur is within range
	{
		o_finalColor = vec4(farBlur, 1.0);
	}
}