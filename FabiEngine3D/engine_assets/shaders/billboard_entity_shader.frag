#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
in vec2 f_uv;
in vec3 f_pos;

// Textures
layout(location = 0) uniform sampler2D u_diffuseMap;

// Vec3 uniforms
uniform vec3 u_color;
uniform vec3 u_cameraPosition;
uniform vec3 u_fogColor;

// Float uniforms
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogThickness;
uniform float u_lightness;
uniform float u_inversion;
uniform float u_minAlpha;

// Boolean uniforms
uniform bool u_isFogEnabled;
uniform bool u_isAlphaObject;
uniform bool u_hasDiffuseMap;
uniform bool u_isBright;

// Out variables
layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

// Functions
vec3 applyFog(vec3 color);

// Process fragment
void main()
{
	// Calculate primary color
	vec3 primaryColor;
	if(u_hasDiffuseMap)
	{
		// Calculate the texel color
		vec4 texColor = texture(u_diffuseMap, f_uv);

		// Removing white alpha background
		if(u_isAlphaObject)
		{
			if(texColor.a < u_minAlpha)
			{
				discard;
			}
		}

		// Set primary color
		primaryColor  = texColor.rgb;
		primaryColor *= u_color;
		primaryColor *= u_lightness;
		primaryColor  = clamp(primaryColor, vec3(0.0f), vec3(1.0f));
		primaryColor  = mix(primaryColor, vec3(1.0f) - primaryColor, clamp(u_inversion, 0.0f, 1.0f));
		primaryColor  = applyFog(primaryColor);
	}
	else
	{
		// Set primary color
		primaryColor  = u_color;
		primaryColor *= u_lightness;
		primaryColor  = applyFog(primaryColor);
	}
	
	// Calculate secondary color
	vec3 secondaryColor = (u_isBright ? primaryColor : vec3(0.0f));

	// Set final colors
	o_primaryColor = vec4(primaryColor, 1.0f);
	o_secondaryColor = vec4(secondaryColor, 1.0f);
}

// Calculate fog color
vec3 applyFog(vec3 color)
{
	if(u_isFogEnabled)
	{
        // Calculate distance in world space
        float distance = length(f_pos.xyz - u_cameraPosition);

        // Calculate fog intensity
		float difference = u_fogMaxDistance - u_fogMinDistance;
		float part = (distance - u_fogMinDistance) / difference;
		part = clamp(part, 0.0f, 1.0f);
		float mixValue = part * u_fogThickness;
		return mix(color, u_fogColor, mixValue);
	}
	else
	{
		return color;
	}
}