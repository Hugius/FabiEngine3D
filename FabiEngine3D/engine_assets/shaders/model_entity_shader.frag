#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// Const variables
#define MAX_POINT_LIGHT_COUNT 128

// In variables
in vec3 f_pos;
in vec2 f_uv;
in vec3 f_normal;
in vec4 f_shadowPos;
in vec4 f_clip;
in mat3 f_tbnMatrix;

// Textures
layout(location = 0) uniform sampler2D   u_sampler_diffuseMap;
layout(location = 1) uniform sampler2D   u_sampler_lightMap;
layout(location = 2) uniform sampler2D   u_sampler_normalMap;
layout(location = 3) uniform sampler2D   u_sampler_reflectionMap;
layout(location = 4) uniform sampler2D   u_sampler_sceneReflectionMap;
layout(location = 5) uniform sampler2D   u_sampler_shadowMap;
layout(location = 6) uniform samplerCube u_sampler_mainSkyMap;
layout(location = 7) uniform samplerCube u_sampler_mixSkyMap;

// Matrix44 uniforms
uniform mat4 u_skyRotationMatrix;

// Vector3 uniforms
uniform vec3 u_cameraPosition;
uniform vec3 u_cameraFront;
uniform vec3 u_ambientLightColor;
uniform vec3 u_directionalLightColor;
uniform vec3 u_directionalLightPosition;
uniform vec3 u_pointLightPositions[MAX_POINT_LIGHT_COUNT];
uniform vec3 u_pointLightColors[MAX_POINT_LIGHT_COUNT];
uniform vec3 u_spotLightColor;
uniform vec3 u_color;
uniform vec3 u_fogColor;
uniform vec3 u_shadowAreaCenter;
uniform vec3 u_mainSkyColor;
uniform vec3 u_mixSkyColor;

// Float uniforms
uniform float u_pointLightIntensities[MAX_POINT_LIGHT_COUNT];
uniform float u_pointLightDistanceFactors[MAX_POINT_LIGHT_COUNT];
uniform float u_ambientLightIntensity;
uniform float u_directionalLightIntensity;
uniform float u_specularLightFactor;
uniform float u_specularLightIntensity;
uniform float u_customAlpha;
uniform float u_skyReflectionMixValue;
uniform float u_sceneReflectionMixValue;
uniform float u_lightness;
uniform float u_shadowAreaSize;
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogThickness;
uniform float u_maxSpotlightAngle;
uniform float u_spotLightIntensity;
uniform float u_maxSpotLightDistance;
uniform float u_skyMixValue;
uniform float u_mainSkyLightness;
uniform float u_mixSkyLightness;
uniform float u_shadowLightness;

// Boolean uniforms
uniform bool u_isTransparent;
uniform bool u_isLightMapped;
uniform bool u_isNormalMapped;
uniform bool u_isSkyReflective;
uniform bool u_isSceneReflective;
uniform bool u_isSpecularLighted;
uniform bool u_isShadowed;
uniform bool u_isShadowFrameRenderEnabled;
uniform bool u_isSoftShadowingEnabled;
uniform bool u_isAmbientLightEnabled;
uniform bool u_isDirectionalLightEnabled;
uniform bool u_isSpecularLightEnabled;
uniform bool u_isSpotLightEnabled;
uniform bool u_lightMappingEnabled;
uniform bool u_isNormalMappingEnabled;
uniform bool u_isPointLightEnabled;
uniform bool u_skyReflectionsEnabled;
uniform bool u_sceneReflectionsEnabled;
uniform bool u_isFogEnabled;
uniform bool u_isShadowsEnabled;
uniform bool u_hasDiffuseMap;
uniform bool u_hasLightMap;
uniform bool u_hasNormalMap;
uniform bool u_hasReflectionMap;

// Integer uniforms
uniform int u_shadowMapSize;
uniform int u_pointLightCount;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Functions
vec3 getNormalMappedVector();
vec3 getTextureColor();
vec3 getAmbientLighting();
vec3 getDirectionalLighting(vec3 normal, bool noShadowOcclusion);
vec3 getPointLighting(vec3 normal);
vec3 getSpotLighting(vec3 normal);
vec3 applyLightMapping(vec3 color);
vec3 applyFog(vec3 color);
vec3 applySkyReflections(vec3 color, vec3 normal);
vec3 applySceneReflections(vec3 color);
float getShadowValue();
float getSpecularValue(vec3 position, vec3 normal);

// Calculate final fragment color
void main()
{
    // Calculate normal vector
    vec3 normal = getNormalMappedVector();

	// Calculate lighting
    float shadow		   = getShadowValue();
	vec3 ambient		   = getAmbientLighting();
	vec3 directional	   = getDirectionalLighting(normal, u_isSoftShadowingEnabled ? true : (shadow == 1.0f));
	vec3 point			   = getPointLighting(normal);
    vec3 spot			   = getSpotLighting(normal);

	// Apply lighting
	vec3 color;
	color  = getTextureColor(); // Diffuse map
    color *= u_color;
	color  = applySkyReflections(color, normal); // Sky reflection
	color  = applySceneReflections(color); // Scene reflection
	color *= vec3(((ambient + directional) * shadow) + point + spot); // Lighting
	color  = applyLightMapping(color); // LightMapping
	color *= u_lightness; // Lightness
    color  = applyFog(color); // Fog

	// Set final color
	o_finalColor = vec4(color, u_customAlpha);
}

// Calculate new normal
vec3 getNormalMappedVector()
{
    if(u_isNormalMappingEnabled && u_isNormalMapped && u_hasNormalMap)
    {
        // Calculate new normal vector
        vec3 normal = texture(u_sampler_normalMap, f_uv).rgb;
        normal = normal * 2.0f - 1.0f;
        normal = normalize(f_tbnMatrix * normal);

        // Return result
        return normal;
    }
    else
    {
        return f_normal;
    }
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

		// Removing alpha background
		if(u_isTransparent)
		{
			if(texColor.a < 0.25f)
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
	if(u_isAmbientLightEnabled)
	{
		return u_ambientLightColor * u_ambientLightIntensity;
	}
	else
	{
		return vec3(0.0f);
	}
}

// Calculate directional lighting
vec3 getDirectionalLighting(vec3 normal, bool noShadowOcclusion)
{
	if(u_isDirectionalLightEnabled)
	{
        // Calculate lighting strength
        vec3 result = vec3(0.0f);
		vec3 lightDirection = normalize(u_directionalLightPosition - f_pos);
		float diffuse = max(dot(normal, lightDirection), 0.0f);

        // Apply
        result += vec3(diffuse * float(noShadowOcclusion)); // Diffuse
        result += vec3(getSpecularValue(u_directionalLightPosition, normal)) * float(noShadowOcclusion); // Specular
        result *= u_directionalLightColor; // Color
        result *= u_directionalLightIntensity; // Intensity

        // Return
        return result;
	}
	else
	{
		return vec3(0.0f);
	}
}

// Calculate point lighting
vec3 getPointLighting(vec3 normal)
{
	if(u_isPointLightEnabled)
	{
		vec3 result = vec3(0.0f);
		
        // For every pointlight
		for (int i = 0; i < u_pointLightCount; i++)
		{
            // Calculate lighting strength
			vec3  lightDir = normalize(u_pointLightPositions[i] - f_pos);
			float diffuse = max(dot(normal, lightDir), 0.0f);
			float distance = length(u_pointLightPositions[i] - f_pos) * u_pointLightDistanceFactors[i];
			float attenuation = 1.0f / (1.0f + 0.07f * distance + 0.017f * (distance * distance));
			float specular = getSpecularValue(u_pointLightPositions[i], normal);

            // Apply
            vec3 current = vec3(0.0f);
			current += vec3(diffuse); // Diffuse
			current += vec3(specular); // Specular
            current *= u_pointLightColors[i]; // Color
            current *= attenuation; // Distance
            current *= u_pointLightIntensities[i]; // Intensity

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


// Calculate spot lighting
vec3 getSpotLighting(vec3 normal)
{
    if(u_isSpotLightEnabled)
    {
        float fragmentDistance = abs(length(u_cameraPosition - f_pos));
        float distanceFactor = fragmentDistance / u_maxSpotLightDistance;
        distanceFactor = clamp(distanceFactor, 0.0f, 1.0f);
        distanceFactor = 1.0f - distanceFactor;

        // Calculate lighting strength
        vec3 lightDirection = normalize(u_cameraPosition - f_pos);
        float smoothingFactor = 0.9f;
        float spotTheta = dot(lightDirection, normalize(-u_cameraFront));
        float epsilon   = u_maxSpotlightAngle - u_maxSpotlightAngle * smoothingFactor;
        float intensity = clamp((spotTheta - u_maxSpotlightAngle * smoothingFactor) / epsilon, 0.0f, 1.0f);
		float diffuse = max(dot(normal, lightDirection), 0.0f);
        float specular = getSpecularValue(u_cameraPosition, normal);

        // Apply lighting calculations
		vec3 result = vec3(0.0f);
        result += vec3(diffuse * intensity); // Diffuse
        result += vec3(specular * intensity); // Specular
        result *= u_spotLightColor; // Color
        result *= u_spotLightIntensity; // Intensity

        // Return
        return result * distanceFactor;
    }
    else
    {
        return vec3(0.0f);
    }
}

// Calculate specular lighting
float getSpecularValue(vec3 position, vec3 normal)
{
    if(u_isSpecularLightEnabled && u_isSpecularLighted)
    {
        // Calculate
        vec3 lightDirection   = normalize(f_pos - position);
        vec3 viewDirection    = normalize(f_pos - u_cameraPosition);
        vec3 reflectDirection = reflect(-lightDirection, normal);
        float result          = pow(max(dot(viewDirection, reflectDirection), 0.0f), u_specularLightFactor);

        // Return
        return result * u_specularLightIntensity;
    }
    else
    {
        return 0.0f;
    }
}

// Calculate shadow lighting
float getShadowValue()
{
	if(u_isShadowsEnabled && u_isShadowed)
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
			float shadow        = 0.0f;
			vec3 projCoords     = (f_shadowPos.xyz / f_shadowPos.w) * 0.5f + 0.5f;
			float currentDepth  = projCoords.z;
			float texelSize     = 1.0f / float(u_shadowMapSize);
			float bias			= 0.00075f;

			// Skip fragments outside of the depth map
			if (projCoords.z > 1.0f)
			{
				return 1.0f;
			}

			// Calculate PCF shadows
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					float pcfDepth = texture(u_sampler_shadowMap, projCoords.xy + vec2(x, y) * vec2(texelSize)).r; 
					shadow += (currentDepth - bias > pcfDepth) ? u_shadowLightness : 1.0f;        
				}    
			}
            
			// Calculate final shadow value
			shadow /= 9.0f;
			
			// Limit shadows
			if(shadow > 1.0f)
			{
				shadow = 1.0f;
			}

			// Long-distance shadows fading
			float maxDistance = max(abs(f_pos.x - u_shadowAreaCenter.x), abs(f_pos.z - u_shadowAreaCenter.z)); // Max distance to center
			float alpha = maxDistance - (halfSize * 0.9f); // Only for the outer 10% of the shadowed area
			alpha = clamp(alpha, 0.0f, halfSize * 0.1f); // Cannot be negative
			alpha /= (halfSize * 0.1f); // Convert value to 0.0 - 1.0 range

			// Debug area frame rendering
			if(u_isShadowFrameRenderEnabled)
			{
				if((maxDistance - (halfSize * 0.99f)) > 0.0f)
				{
					return 0.0f;
				}
			}

			// Return shadow value
			if(u_isSoftShadowingEnabled)
			{
				return mix(shadow, 1.0f, alpha);
			}
			else
			{
				return shadow;
			}
		}

		// No shadow
		return 1.0f;
	}
	else
	{
		// No shadow
		return 1.0f;
	}
}

// Calculate light mapping
vec3 applyLightMapping(vec3 color)
{
	if(u_lightMappingEnabled && u_isLightMapped && u_hasLightMap)
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
	if(u_isFogEnabled)
	{
        // Calculate distance in world space
        float distance = length(f_pos.xyz - u_cameraPosition);

        // Calculate fog intensity
		float difference = u_fogMaxDistance - u_fogMinDistance;
		float part = (distance - u_fogMinDistance) / difference;
		part = clamp(part, 0.0f, 1.0f);
		float thickness = clamp(u_fogThickness, 0.0f, 1.0f);
		float mixValue = part * thickness;
		return mix(color, u_fogColor, mixValue);
	}
	else
	{
		return color;
	}
}

// Calculate sky reflections
vec3 applySkyReflections(vec3 color, vec3 normal)
{
	if(u_skyReflectionsEnabled && u_isSkyReflective)
	{
		vec4 reflectionMapColor = u_hasReflectionMap ? texture(u_sampler_reflectionMap, f_uv) : vec4(0.0f);
		
		// Check if current texel allows for reflection
		if(reflectionMapColor.rgb != vec3(0.0f))
		{
			float mixValue    = clamp(u_skyMixValue, 0.0, 1.0f);
			float lightness   = mix(u_mainSkyLightness, u_mixSkyLightness, mixValue);
			vec3 viewDir      = normalize(f_pos - u_cameraPosition);
			vec3 reflectDir   = reflect(viewDir, normal);
			vec3 mainSkyColor = texture(u_sampler_mainSkyMap, vec3(u_skyRotationMatrix * vec4(reflectDir, 1.0f))).rgb * u_mainSkyColor;
			vec3 mixSkyColor  = texture(u_sampler_mixSkyMap, vec3(u_skyRotationMatrix * vec4(reflectDir, 1.0f))).rgb * u_mixSkyColor;
			vec3 reflectColor = mix(mainSkyColor, mixSkyColor, mixValue) * lightness;
			vec3 mixedColor   = mix(color, reflectColor, u_skyReflectionMixValue);

			return mixedColor.rgb;
		}

		return color;
	}
	else
	{
		return color;
	}
}

// Calculate scene reflections
vec3 applySceneReflections(vec3 color)
{
	if(u_sceneReflectionsEnabled && u_isSceneReflective)
	{
		vec4 reflectionMapColor = u_hasReflectionMap ? texture(u_sampler_reflectionMap, f_uv) : vec4(0.0f);
		
		// Check if current texel allows for reflection
		if(reflectionMapColor.rgb != vec3(0.0f))
		{
			vec2 ndc             = (f_clip.xy / f_clip.w) / 2.0 + 0.5;
			vec2 texCoords       = vec2(ndc.x, -ndc.y);
			vec3 reflectionColor = texture(u_sampler_sceneReflectionMap, vec2(texCoords.x,  texCoords.y)).rgb;
			vec3 mixedColor      = mix(color.rgb, reflectionColor, u_sceneReflectionMixValue);
        
			return mixedColor.rgb;
		}

		return color;
	}
	else
	{
		return color;
	}
}