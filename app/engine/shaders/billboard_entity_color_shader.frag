#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// Constant variables
#define FRAME_COLOR vec3(1.0f, 1.0f, 1.0f)

// In variables
in vec2 f_uv;
in vec3 f_position;

// Textures
layout (location = 0) uniform sampler2D u_diffuseMap;
layout (location = 1) uniform sampler2D u_emissionMap;

// Vector uniforms
uniform vec3 u_color;
uniform vec3 u_cameraPosition;
uniform vec3 u_fogColor;

// Float uniforms
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogThickness;
uniform float u_lightness;
uniform float u_colorInversion;
uniform float u_minTextureAlpha;
uniform float u_alpha;
uniform float u_emissionIntensity;

// Boolean uniforms
uniform bool u_isWireFramed;
uniform bool u_isFogEnabled;
uniform bool u_hasDiffuseMap;
uniform bool u_isBright;
uniform bool u_hasEmissionMap;

// Out variables
layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

// Functions
vec3 calculateDiffuseMapping();
vec3 calculateEmissionMapping();
vec3 calculateFog(vec3 color);

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

	// Calculate diffuse mapping
	vec3 diffuseMapping = calculateDiffuseMapping();

	// Calculate emission mapping
	vec3 emissionMapping = calculateEmissionMapping();

	// Calculate base color
	vec3 primaryColor = vec3(0.0f);
	primaryColor += diffuseMapping;
	primaryColor += emissionMapping;
	primaryColor *= u_color;
	primaryColor *= u_lightness;
	primaryColor  = clamp(primaryColor, vec3(0.0f), vec3(1.0f));
	primaryColor  = mix(primaryColor, (vec3(1.0f) - primaryColor), clamp(u_colorInversion, 0.0f, 1.0f));

	// Apply fog
	primaryColor = calculateFog(primaryColor);

	// Apply gamma correction
	primaryColor = pow(primaryColor, vec3(1.0f / 2.2f));

	// Set final colors
	o_primaryColor = vec4(primaryColor, u_alpha);
	o_secondaryColor = vec4((((emissionMapping != vec3(0.0f)) || u_isBright) ? primaryColor : vec3(0.0f)), 1.0f);
}

vec3 calculateDiffuseMapping()
{
	if (u_hasDiffuseMap)
	{
		// Calculate diffuse map color
		vec4 diffuseMapColor = texture(u_diffuseMap, f_uv);
		diffuseMapColor.rgb = pow(diffuseMapColor.rgb, vec3(2.2f));

		// Check if transparent
		if (diffuseMapColor.a < u_minTextureAlpha)
		{
			discard;
		}

		// Return
		return diffuseMapColor.rgb;
	}
	else
	{
		return vec3(1.0f);
	}
}

vec3 calculateEmissionMapping()
{
	if (u_hasEmissionMap)
	{
		// Calculate emission map color
		vec4 emissionMapColor = texture(u_emissionMap, f_uv);

		// Check if transparent
		if (emissionMapColor.a < u_minTextureAlpha)
		{
			return vec3(0.0f);
		}

		// Return
		return (emissionMapColor.rgb * u_emissionIntensity);
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 calculateFog(vec3 color)
{
	if (u_isFogEnabled)
	{
        // Calculate distance in world space
        float fragmentDistance = distance(f_position.xyz, u_cameraPosition);

        // Calculate fog intensity
		float distanceDifference = (u_fogMaxDistance - u_fogMinDistance);
		float distancePart = clamp(((fragmentDistance - u_fogMinDistance) / distanceDifference), 0.0f, 1.0f);
		float mixValue = (distancePart * u_fogThickness);

		// Return
		return mix(color, u_fogColor, mixValue);
	}
	else
	{
		return color;
	}
}