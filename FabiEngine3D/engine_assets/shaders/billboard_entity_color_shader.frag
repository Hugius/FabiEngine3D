#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
in vec2 f_uv;
in vec3 f_pos;

// Textures
layout (location = 0) uniform sampler2D u_diffuseMap;

// Vector uniforms
uniform vec3 u_color;
uniform vec3 u_cameraPosition;
uniform vec3 u_fogColor;

// Float uniforms
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogThickness;
uniform float u_lightness;
uniform float u_inversion;
uniform float u_minDiffuseMapAlpha;
uniform float u_alpha;

// Boolean uniforms
uniform bool u_isWireFramed;
uniform bool u_isFogEnabled;
uniform bool u_isTransparent;
uniform bool u_hasDiffuseMap;
uniform bool u_isBright;

// Out variables
layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

// Functions
vec3 calculateFog(vec3 color);

// Process fragment
void main()
{
	// Wire frame color
	if(u_isWireFramed)
	{
		o_primaryColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
		return;
	}

	// Calculate primary color
	vec3 primaryColor;
	if (u_hasDiffuseMap)
	{
		// Calculate diffuse map color
		vec4 diffuseMapColor = texture(u_diffuseMap, f_uv);
		diffuseMapColor.rgb = pow(diffuseMapColor.rgb, vec3(2.2f));

		// Removing white alpha background
		if (u_isTransparent)
		{
			if (diffuseMapColor.a < u_minDiffuseMapAlpha)
			{
				discard;
			}
		}

		// Calculate base color
		primaryColor  = diffuseMapColor.rgb;
		primaryColor *= u_color;
		primaryColor *= u_lightness;
		primaryColor  = clamp(primaryColor, vec3(0.0f), vec3(1.0f));
		primaryColor  = mix(primaryColor, (vec3(1.0f) - primaryColor), clamp(u_inversion, 0.0f, 1.0f));

		// Apply fog
		primaryColor = calculateFog(primaryColor);

		// Apply gamma correction
		primaryColor = pow(primaryColor, vec3(1.0f / 2.2f));
	}
	else
	{
		// Calculate base color
		primaryColor  = u_color;
		primaryColor *= u_lightness;
		primaryColor  = clamp(primaryColor, vec3(0.0f), vec3(1.0f));
		primaryColor  = mix(primaryColor, (vec3(1.0f) - primaryColor), clamp(u_inversion, 0.0f, 1.0f));

		// Apply fog
		primaryColor = calculateFog(primaryColor);

		// Apply gamma correction
		primaryColor = pow(primaryColor, vec3(1.0f / 2.2f));
	}

	// Calculate secondary color
	vec3 secondaryColor = (u_isBright ? primaryColor : vec3(0.0f));

	// Set final colors
	o_primaryColor = vec4(primaryColor, u_alpha);
	o_secondaryColor = vec4(secondaryColor, 1.0f);
}

vec3 calculateFog(vec3 color)
{
	if (u_isFogEnabled)
	{
        // Calculate distance in world space
        float fragmentDistance = distance(f_pos.xyz, u_cameraPosition);

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