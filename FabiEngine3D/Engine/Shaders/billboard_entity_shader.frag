#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
in vec2 f_uv;
in vec3 f_pos;

// Textures
layout(location = 0) uniform sampler2D u_sampler_diffuseMap;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Vec3 uniforms
uniform vec3 u_color;
uniform vec3 u_cameraPosition;
uniform vec3 u_fogColor;

// Float uniforms
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogDefaultFactor;

// Boolean uniforms
uniform bool u_fogEnabled;
uniform bool u_isAlphaObject;
uniform bool u_noTexture;

vec3 applyFog(vec3 color);

// Calculate final fragment color
void main()
{
	// Calculating the texel color
	vec4 texColor = texture(u_sampler_diffuseMap, f_uv);

	// Removing white alpha background
	if(u_isAlphaObject)
	{
		if(texColor.a <= 0.1f)
		{
			discard;
		}
	}

	// Check if billboard has texture or only color
	if(u_noTexture)
	{
		o_finalColor = vec4(u_color, texColor.a);
	}
	else
	{
		o_finalColor = vec4(texColor.rgb * u_color, texColor.a);
	}

	o_finalColor.rgb = applyFog(o_finalColor.rgb);
}

// Calculate fog color
vec3 applyFog(vec3 color)
{
	if(u_fogEnabled)
	{
        // Calculate distance in world space
        float distance = length(f_pos.xyz - u_cameraPosition);

        // Determine if in fog range
        if(distance > u_fogMaxDistance)
        {
            return mix(color, u_fogColor, u_fogDefaultFactor);
        }
        else
        {
            return mix(u_fogColor, color, min(u_fogMinDistance / distance, 1.0f));
        }
	}
	else
	{
		return color;
	}
}