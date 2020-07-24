#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// Const variables
#define POINT_LIGHT_AMOUNT 128

// In variables
in vec3 f_pos;
in vec2 f_uv;
in vec3 f_normal;
in vec4 f_shadowPos;

// Textures
layout(location = 0) uniform sampler2D   u_sampler_diffuseMap;
layout(location = 1) uniform sampler2D   u_sampler_blendMap;
layout(location = 2) uniform sampler2D   u_sampler_blendMapR;
layout(location = 3) uniform sampler2D   u_sampler_blendMapG;
layout(location = 4) uniform sampler2D   u_sampler_blendMapB;
layout(location = 5) uniform sampler2D   u_sampler_shadowMap;

// Uniforms
uniform vec3 u_cameraPosition;
uniform vec3 u_ambientLightingColor;
uniform vec3 u_directionalLightingColor;
uniform vec3 u_directionalLightingPosition;
uniform vec3 u_pointLightPositions[POINT_LIGHT_AMOUNT];
uniform vec3 u_pointLightColors[POINT_LIGHT_AMOUNT];

uniform float u_lightness;
uniform float u_ambientLightingIntensity;
uniform float u_directionalLightingIntensity;
uniform float u_pointLightIntensities[POINT_LIGHT_AMOUNT];
uniform float u_pointLightDistanceFactors[POINT_LIGHT_AMOUNT];
uniform float u_fogMinDistance;
uniform float u_blendmapRepeat;
uniform float u_blendmapRepeatR;
uniform float u_blendmapRepeatG;
uniform float u_blendmapRepeatB;

uniform bool u_blendmappingEnabled;
uniform bool u_ambientLightingEnabled;
uniform bool u_directionalLightingEnabled;
uniform bool u_pointLightingEnabled;
uniform bool u_fogEnabled;
uniform bool u_shadowsEnabled;

uniform int u_shadowMapSize;
uniform int u_pointLightCount;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Functions
vec3 getTextureColor();
vec3 getAmbientLighting();
vec3 getDirectionalLighting();
vec3 getPointLighting();
vec3 applyFog(vec3 color);
vec3 getShadowLighting();

// Calculate final fragment color
void main()
{
	// Calculate lighting
	vec3 a = getAmbientLighting();
	vec3 d = getDirectionalLighting();
	vec3 p = getPointLighting();
	vec3 h = getShadowLighting();

	// Apply lighting
	vec3 color;
	color = getTextureColor() * vec3((a + d) * h + p);
	color = applyFog(color);
	color *= u_lightness;

	// Set final color
	o_finalColor = vec4(color, 1.0f);
}

// Calculate texture color
vec3 getTextureColor()
{
	if(u_blendmappingEnabled)
	{
		vec4 blendmapColor    = texture(u_sampler_blendMap,   f_uv / u_blendmapRepeat);
		vec4 mainTextureColor = texture(u_sampler_diffuseMap, f_uv) * (1.0f - blendmapColor.r - blendmapColor.g - blendmapColor.b);
		vec4 rTextureColor    = texture(u_sampler_blendMapR, (f_uv / u_blendmapRepeat) * u_blendmapRepeatR) * blendmapColor.r;
		vec4 gTextureColor    = texture(u_sampler_blendMapG, (f_uv / u_blendmapRepeat) * u_blendmapRepeatG) * blendmapColor.g;
		vec4 bTextureColor    = texture(u_sampler_blendMapB, (f_uv / u_blendmapRepeat) * u_blendmapRepeatB) * blendmapColor.b;
		vec4 newColor         = mainTextureColor + rTextureColor + gTextureColor + bTextureColor;
        
		return newColor.rgb;
	}
	else
	{
		// Calculating the texel color
		vec4 texColor = texture(u_sampler_diffuseMap, vec2(-f_uv.x, f_uv.y));

		// Returning the texture color
		return texColor.rgb;
	}
}

// Calculate fog color
vec3 applyFog(vec3 color)
{
	if(u_fogEnabled)
	{
		float  distance    = length(f_pos.xyz - u_cameraPosition);
		vec3   foggedColor = mix(vec3(0.75f, 0.75f, 0.75f), color, min(u_fogMinDistance / distance, 1.0f));
		return foggedColor;
	}
	else
	{
		return color;
	}
}

// Calculate ambient lighting
vec3 getAmbientLighting()
{
	if(u_ambientLightingEnabled)
	{
		return u_ambientLightingColor * u_ambientLightingIntensity;
	}
	else
	{
		return vec3(0.0f);
	}
}

// Calculate directional lighting
vec3 getDirectionalLighting()
{
	if(u_directionalLightingEnabled)
	{
		vec3 lightDir = normalize(u_directionalLightingPosition - f_pos);
		float lightIntensity = max(dot(f_normal, lightDir), 0.0);
		return u_directionalLightingColor * (lightIntensity * u_directionalLightingIntensity);
	}
	else
	{
		return vec3(0.0f);
	}
}

// Calculate point lighting
vec3 getPointLighting()
{
	if(u_pointLightingEnabled)
	{
		vec3 result = vec3(0.0f);
		
        // For every pointlight
		for(int i = 0; i < u_pointLightCount; i++)
		{
            // Calculate
			vec3  lightDir = normalize(u_pointLightPositions[i] - f_pos);
			float diffuse = max(dot(f_normal, lightDir), 0.0);
			float distance = length(u_pointLightPositions[i] - f_pos) * u_pointLightDistanceFactors[i];
			float attenuation = 1.0f / (1.0f + 0.07f * distance + 0.017f * (distance * distance));

            // Apply
            vec3 current = vec3(0.0f);
			current += vec3(diffuse);
            current *= u_pointLightColors[i];
            current *= attenuation;
            current *= u_pointLightIntensities[i];

            // Add to total lighting value
            result += current;
		}

        // Return
		return result;
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 getShadowLighting()
{
	if(u_shadowsEnabled)
	{
		// Variables
		float shadow       = 0.0f;
		vec3 projCoords    = (f_shadowPos.xyz / f_shadowPos.w) * 0.5 + 0.5;
		float currentDepth = projCoords.z;
		float texelSize    = 1.0f / float(u_shadowMapSize);

		// Skip fragments outside of the depth map
		if (projCoords.z > 1.0f)
		{	
			return vec3(1.0f);
		}

		// Calculate PCF shadows
		for(int x = -1; x <= 1; ++x)
		{
			for(int y = -1; y <= 1; ++y)
			{
				float pcfDepth = texture(u_sampler_shadowMap, projCoords.xy + vec2(x, y) * vec2(texelSize)).r; 
				shadow += currentDepth - texelSize > pcfDepth ? 0.2f : 1.0f;        
			}    
		}
		
		// Return shadow value
		shadow /= 9.0f;
		return vec3(shadow);
	}
	else
	{
		return vec3(1.0f);
	}
}
