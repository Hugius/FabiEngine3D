#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// Const variables
#define POINT_LIGHT_AMOUNT 128

// In variables
in vec3 f_pos;
in vec2 f_uv;
in vec3 f_normal;
in vec4 f_shadowPos;
in vec4 f_clip;

// Textures
layout(location = 0) uniform sampler2D   u_sampler_diffuseMap;
layout(location = 1) uniform sampler2D   u_sampler_lightMap;
layout(location = 2) uniform sampler2D   u_sampler_skyReflectionMap;
layout(location = 3) uniform sampler2D   u_sampler_sceneReflectionMap;
layout(location = 4) uniform sampler2D   u_sampler_shadowMap;
layout(location = 5) uniform samplerCube u_sampler_cubeMap;

// Matrix44 uniforms
uniform mat4 u_skyRotationMatrix;

// Vector3 uniforms
uniform vec3 u_cameraPosition;
uniform vec3 u_ambientLightingColor;
uniform vec3 u_directionalLightingColor;
uniform vec3 u_directionalLightingPosition;
uniform vec3 u_pointLightPositions[POINT_LIGHT_AMOUNT];
uniform vec3 u_pointLightColors[POINT_LIGHT_AMOUNT];
uniform vec3 u_color;
uniform vec3 u_fogColor;
uniform vec3 u_shadowAreaCenter;

// Float uniforms
uniform float u_pointLightIntensities[POINT_LIGHT_AMOUNT];
uniform float u_pointLightDistanceFactors[POINT_LIGHT_AMOUNT];
uniform float u_ambientLightingIntensity;
uniform float u_directionalLightingIntensity;
uniform float u_specularLightingFactor;
uniform float u_specularLightingIntensity;
uniform float u_fogMinDistance;
uniform float u_customAlpha;
uniform float u_skyReflectionFactor;
uniform float u_sceneReflectionFactor;
uniform float u_lightness;
uniform float u_shadowAreaSize;

// Boolean uniforms
uniform bool u_isTransparent;
uniform bool u_isLightMapped;
uniform bool u_isSkyReflective;
uniform bool u_isSceneReflective;
uniform bool u_isSpecular;
uniform bool u_isShadowed;
uniform bool u_ambientLightingEnabled;
uniform bool u_directionalLightingEnabled;
uniform bool u_specularLightingEnabled;
uniform bool u_lightMappingEnabled;
uniform bool u_pointLightingEnabled;
uniform bool u_skyReflectionsEnabled;
uniform bool u_sceneReflectionsEnabled;
uniform bool u_fogEnabled;
uniform bool u_shadowsEnabled;
uniform bool u_hasDiffuseMap;
uniform bool u_shadowFrameRenderingEnabled;

// Integer uniforms
uniform int u_shadowMapSize;
uniform int u_pointLightCount;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Functions
vec3 getTextureColor();
vec3 getAmbientLighting();
vec3 getDirectionalLighting();
vec3 getPointLighting();
float getSpecularValue(vec3 position);
vec3 getShadowLighting();
vec3 applyLightMapping(vec3 color);
vec3 applyFog(vec3 color);
vec3 applySkyReflections(vec3 color);
vec3 applySceneReflections(vec3 color);

// Calculate final fragment color
void main()
{
	// Calculate lighting
	vec3 ambient     = getAmbientLighting();
	vec3 directional = getDirectionalLighting();
	vec3 point       = getPointLighting();
	vec3 shadow      = getShadowLighting();

	// Apply lighting
	vec3 color;
	color  = getTextureColor(); // Diffuse map
    color *= u_color;
	color  = applySkyReflections(color); // Sky reflection
	color  = applySceneReflections(color); // Scene reflection
	color *= vec3((ambient + directional) * shadow + point); // Lighting
	color  = applyLightMapping(color); // LightMapping
	color  = applyFog(color); // Fog
	color *= u_lightness;

	// Set final color
	o_finalColor = vec4(color, u_customAlpha);
}

// Calculate texture color
vec3 getTextureColor()
{
	if(!u_hasDiffuseMap)
	{
		return vec3(1.0f);
	}
	else
	{
		// Calculating the texel color
		vec4 texColor = texture(u_sampler_diffuseMap, f_uv);

		// Removing white alpha background
		if(u_isTransparent)
		{
			if(texColor.a <= 0.25f)
			{
				discard;
			}
		}

		// Returning the texture color
		return texColor.rgb;
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
        // Calculate
        vec3 result = vec3(0.0f);
		vec3 lightDirection = normalize(u_directionalLightingPosition - f_pos);
		float diffuse = max(dot(f_normal, lightDirection), 0.0);

        // Apply
        result += vec3(diffuse);
        result += vec3(getSpecularValue(u_directionalLightingPosition));
        result *= u_directionalLightingColor;
        result *= u_directionalLightingIntensity;

        // Return
        return result;
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
			current += vec3(getSpecularValue(u_pointLightPositions[i]));
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

float getSpecularValue(vec3 position)
{
    if(u_specularLightingEnabled && u_isSpecular)
    {
        // Calculate
        vec3 lightDirection   = normalize(f_pos - position);
        vec3 viewDirection    = normalize(f_pos - u_cameraPosition);
        vec3 reflectDirection = reflect(-lightDirection, f_normal);
        float result          = pow(max(dot(viewDirection, reflectDirection), 0.0f), u_specularLightingFactor);

        // Return
        return result * u_specularLightingIntensity;
    }
    else
    {
        return 0.0f;
    }
}

float getRandomFloat(vec3 seed, int i)
{
	vec4 seed4 = vec4(seed,i);
	float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
	return fract(sin(dot_product) * 43758.5453);
}

vec3 getShadowLighting()
{
	if(u_shadowsEnabled && u_isShadowed)
	{
        float halfSize = u_shadowAreaSize / 2.0f;

        // Check if fragment is within shadow area
		if
		(
			abs(f_pos.x - u_shadowAreaCenter.x) <= (halfSize) && 
			abs(f_pos.z - u_shadowAreaCenter.z) <= (halfSize)
		)
		{
			// Variables
			float shadow       = 1.0f;
			vec3 projCoords    = (f_shadowPos.xyz / f_shadowPos.w) * 0.5f + 0.5f;
			float currentDepth = projCoords.z;
			float texelSize    = 1.0f / float(u_shadowMapSize);

			// Skip fragments outside of the depth map
			if (projCoords.z > 1.0f)
			{	
				return vec3(1.0f);
			}

			// Calculate depth from shadow map
			float shadowMapDepth = texture(u_sampler_shadowMap, projCoords.xy).r;

			// Apply result value
			if((currentDepth - texelSize) > shadowMapDepth)
			{
				shadow = 0.2f; // Shadow
			}
			else
			{
				shadow = 1.0f; // No shadow
			}
			
			// Long-distance shadows fading
			float maxDistance = max(abs(f_pos.x - u_shadowAreaCenter.x), abs(f_pos.z - u_shadowAreaCenter.z)); // Max distance to center
			float alpha = maxDistance - (halfSize * 0.9f); // Only for the outer 10% of the shadowed area
			alpha = clamp(alpha, 0.0f, halfSize * 0.1f); // Cannot be negative
			alpha /= (halfSize * 0.1f); // Convert value to 0.0 - 1.0 range

			// Debug area frame rendering
			if(u_shadowFrameRenderingEnabled)
			{
				if((maxDistance - (halfSize * 0.99f)) > 0.0f)
				{
					return vec3(0.0f);
				}
			}

			// Return shadow value
			return vec3(mix(shadow, 1.0f, alpha));
		}

		// No shadow
		return vec3(1.0f);
	}
	else
	{
		// No shadow
		return vec3(1.0f);
	}
}

vec3 applyLightMapping(vec3 color)
{
	if(u_lightMappingEnabled && u_isLightMapped)
	{
		vec3 lightMapColor = texture(u_sampler_lightMap, f_uv).rgb;
		vec3 lightMappedColor = color + lightMapColor;
		return lightMappedColor;
	}
	else
	{
		return color;
	}
}

// Calculate fog color
vec3 applyFog(vec3 color)
{
	if(u_fogEnabled)
	{
		float  distance    = length(f_pos.xyz - u_cameraPosition);
		vec3   foggedColor = mix(u_fogColor, color, min(u_fogMinDistance / distance, 1.0f));
		return foggedColor;
	}
	else
	{
		return color;
	}
}

vec3 applySkyReflections(vec3 color)
{
	if(u_skyReflectionsEnabled && u_isSkyReflective)
	{
		vec4 reflMapColor = texture(u_sampler_skyReflectionMap, f_uv);
		
		if(reflMapColor.rgb != vec3(0.0f))
		{
			vec3 viewDir      = normalize(f_pos - u_cameraPosition);
			vec3 reflectDir   = reflect(viewDir, f_normal);
			vec4 reflectColor = vec4(texture(u_sampler_cubeMap, vec3(u_skyRotationMatrix * vec4(reflectDir, 1.0f))).rgb, 1.0);
			vec3 mixedColor   = mix(color.rgb, reflectColor.rgb, u_skyReflectionFactor);

			return mixedColor.rgb;
		}

		return color;
	}
	else
	{
		return color;
	}
}

vec3 applySceneReflections(vec3 color)
{
	if(u_sceneReflectionsEnabled && u_isSceneReflective)
	{
		vec2 ndc             = (f_clip.xy / f_clip.w) / 2.0 + 0.5;
		vec2 texCoords       = vec2(ndc.x, -ndc.y);
		vec4 reflectionColor = texture(u_sampler_sceneReflectionMap, vec2(texCoords.x,  texCoords.y));
		vec3 mixedColor      = mix(color.rgb, reflectionColor.rgb, u_sceneReflectionFactor);
        
		return mixedColor.rgb;
	}
	else
	{
		return color;
	}
}
