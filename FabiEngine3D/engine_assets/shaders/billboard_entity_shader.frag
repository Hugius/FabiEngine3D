#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
in vec2 f_uv;
in vec3 f_pos;

// Textures
layout(location = 0) uniform sampler2D u_sampler;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Vec3 uniforms
uniform vec3 u_color;
uniform vec3 u_cameraPosition;
uniform vec3 u_fogColor;

// Float uniforms
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogThickness;
uniform float u_lightness;
uniform float u_minAlpha;

// Boolean uniforms
uniform bool u_isFogEnabled;
uniform bool u_isAlphaObject;
uniform bool u_hasTexture;

vec3 applyFog(vec3 color);

// Calculate final fragment color
void main()
{
	if(u_hasTexture) // Render texture
	{
		// Calculating the texel color
		vec4 texColor = texture(u_sampler, f_uv);

		// Removing white alpha background
		if(u_isAlphaObject)
		{
			if(texColor.a < u_minAlpha)
			{
				discard;
			}
		}

		// Set texture color
		o_finalColor = vec4(texColor.rgb * u_color, 1.0f);
	}
	else // Render color only
	{
		o_finalColor = vec4(u_color, 1.0f);
	}

	// Finalize color
	o_finalColor.rgb = applyFog(o_finalColor.rgb);
    o_finalColor.rgb *= u_lightness;
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