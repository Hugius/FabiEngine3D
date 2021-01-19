#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// Const variables
#define MAX_POINT_LIGHT_COUNT 128

// In variables
in vec3 f_pos;
in vec2 f_uv;
in vec3 f_normal;
in vec4 f_shadowPos;
in mat3 f_tbnMatrix;

// Textures
layout(location = 0) uniform sampler2D u_sampler_diffuseMap;
layout(location = 1) uniform sampler2D u_sampler_normalMap;
layout(location = 2) uniform sampler2D u_sampler_blendMap;
layout(location = 3) uniform sampler2D u_sampler_blendMapR;
layout(location = 4) uniform sampler2D u_sampler_blendMapG;
layout(location = 5) uniform sampler2D u_sampler_blendMapB;
layout(location = 6) uniform sampler2D u_sampler_normalMapR;
layout(location = 7) uniform sampler2D u_sampler_normalMapG;
layout(location = 8) uniform sampler2D u_sampler_normalMapB;
layout(location = 9) uniform sampler2D u_sampler_shadowMap;

// Vec3 uniforms
uniform vec3 u_cameraPosition;
uniform vec3 u_cameraFront;
uniform vec3 u_ambientLightColor;
uniform vec3 u_directionalLightColor;
uniform vec3 u_directionalLightPosition;
uniform vec3 u_pointLightPositions[MAX_POINT_LIGHT_COUNT];
uniform vec3 u_pointLightColors[MAX_POINT_LIGHT_COUNT];
uniform vec3 u_spotLightColor;
uniform vec3 u_shadowAreaCenter;
uniform vec3 u_fogColor;

// Float uniforms
uniform float u_lightness;
uniform float u_ambientLightIntensity;
uniform float u_directionalLightIntensity;
uniform float u_pointLightIntensities[MAX_POINT_LIGHT_COUNT];
uniform float u_pointLightDistanceFactors[MAX_POINT_LIGHT_COUNT];
uniform float u_blendMapRepeat;
uniform float u_blendMapRepeatR;
uniform float u_blendMapRepeatG;
uniform float u_blendMapRepeatB;
uniform float u_shadowAreaSize;
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogDefaultFactor;
uniform float u_specularLightFactor;
uniform float u_specularLightIntensity;
uniform float u_maxSpotlightAngle;
uniform float u_spotLightIntensity;
uniform float u_maxSpotLightDistance;

// Boolean uniforms
uniform bool u_isBlendMapped;
uniform bool u_isNormalMapped;
uniform bool u_isNormalMappedR;
uniform bool u_isNormalMappedG;
uniform bool u_isNormalMappedB;
uniform bool u_isSpecularLighted;
uniform bool u_isNormalMappingEnabled;
uniform bool u_isAmbientLightEnabled;
uniform bool u_isDirectionalLightEnabled;
uniform bool u_isPointLightEnabled;
uniform bool u_isSpotLightEnabled;
uniform bool u_isFogEnabled;
uniform bool u_isShadowsEnabled;
uniform bool u_isShadowFrameRenderEnabled;
uniform bool u_isSpecularLightEnabled;

// Integer uniforms
uniform int u_shadowMapSize;
uniform int u_pointLightCount;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Functions
vec3 getNormalMappedVector();
vec3 getTextureColor();
vec3 getAmbientLighting();
vec3 getDirectionalLighting(bool noShadowOcclusion, vec3 normal);
vec3 getPointLighting(vec3 normal);
vec3 getSpotLighting(vec3 normal);
vec3 applyFog(vec3 color);
float getShadowValue();
float getSpecularValue(vec3 position, vec3 normal);

// Calculate final fragment color
void main()
{
	// Calculate new normal vector
    vec3 normal = getNormalMappedVector();

	// Calculate lighting
    float shadow = getShadowValue();
	vec3 ambient = getAmbientLighting();
	vec3 directional = getDirectionalLighting(shadow == 1.0f, normal);
	vec3 point = getPointLighting(normal);
	vec3 spot = getSpotLighting(normal);

	// Apply lighting
	vec3 color;
	color = getTextureColor();
	color *= vec3(((ambient + directional) * shadow) + point + spot); // Lighting
	color *= u_lightness; // Lightness
	color = applyFog(color);

	// Set final color
	o_finalColor = vec4(color, 1.0f);
}

// Calculate new normal
vec3 getNormalMappedVector()
{
    if(u_isNormalMappingEnabled && (u_isNormalMapped || u_isNormalMappedR || u_isNormalMappedG || u_isNormalMappedB))
    {
		if(u_isBlendMapped) // Blendmapped mixed normal
		{
			// Get color values of blendmap (R, G, B)
			vec2 blendUV = f_uv / u_blendMapRepeat;
			vec4 blendMapColor = texture(u_sampler_blendMap, blendUV);
			float diffuseStrength = (1.0f - blendMapColor.r - blendMapColor.g - blendMapColor.b);
			float rStrength = blendMapColor.r;
			float gStrength = blendMapColor.g;
			float bStrength = blendMapColor.b;

			// Calculate total normal vector
			vec3 totalNormal;

			// Diffuse normal map
			if(u_isNormalMapped)
			{
				vec3 normal = texture(u_sampler_normalMap, f_uv).rgb * 2.0f - 1.0f;
				totalNormal += normalize(f_tbnMatrix * normal) * diffuseStrength;
			}
			else
			{
				totalNormal += f_normal * diffuseStrength;
			}
			
			// BlendR normal map
			if(u_isNormalMappedR)
			{
				vec3 normal = texture(u_sampler_normalMapR, blendUV * u_blendMapRepeatR).rgb * 2.0f - 1.0f;
				totalNormal += normalize(f_tbnMatrix * normal) * rStrength;
			}
			else
			{
				totalNormal += f_normal * rStrength;
			}

			// BlendG normal map
			if(u_isNormalMappedG)
			{
				vec3 normal = texture(u_sampler_normalMapG, blendUV * u_blendMapRepeatG).rgb * 2.0f - 1.0f;
				totalNormal += normalize(f_tbnMatrix * normal) * gStrength;
			}
			else
			{
				totalNormal += f_normal * gStrength;
			}

			// BlendB normal map
			if(u_isNormalMappedB)
			{
				vec3 normal = texture(u_sampler_normalMapB, blendUV * u_blendMapRepeatB).rgb * 2.0f - 1.0f;
				totalNormal += normalize(f_tbnMatrix * normal) * bStrength;
			}
			else
			{
				totalNormal += f_normal * bStrength;
			}

			// Return
			return totalNormal;
		}
		else // Diffuse normal
		{
			if(u_isNormalMapped)
			{
				// Calculate new normal vector
				vec3 normal = texture(u_sampler_normalMap, f_uv).rgb;
				normal = normal * 2.0f - 1.0f;
				normal = normalize(f_tbnMatrix * normal);
				return normal;
			}
			else
			{
				return f_normal;
			}
		}        
    }
    else
    {
        return f_normal;
    }
}

// Calculate texture color
vec3 getTextureColor()
{
	if(u_isBlendMapped) // Blendmapped mixed texture
	{
		// Get color value of blendmap (R, G, B)
		vec2 blendUV = f_uv / u_blendMapRepeat;
		vec4 blendMapColor = texture(u_sampler_blendMap, blendUV);

		// Calculate diffuse color
		vec4 diffuseTextureColor = texture(u_sampler_diffuseMap, f_uv) * (1.0f - blendMapColor.r - blendMapColor.g - blendMapColor.b);

		// Calculate blending color for every channel
		vec4 rTextureColor = texture(u_sampler_blendMapR, blendUV * u_blendMapRepeatR) * blendMapColor.r;
		vec4 gTextureColor = texture(u_sampler_blendMapG, blendUV * u_blendMapRepeatG) * blendMapColor.g;
		vec4 bTextureColor = texture(u_sampler_blendMapB, blendUV * u_blendMapRepeatB) * blendMapColor.b;

		// Compose final color
		vec4 newColor = diffuseTextureColor + rTextureColor + gTextureColor + bTextureColor;
        
		// Return
		return newColor.rgb;
	}
	else // Diffuse texture
	{
		// Calculate diffuse color
		vec4 newColor = texture(u_sampler_diffuseMap, vec2(-f_uv.x, f_uv.y));

		// Return
		return newColor.rgb;
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
vec3 getDirectionalLighting(bool noShadowOcclusion, vec3 normal)
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
		for(int i = 0; i < u_pointLightCount; i++)
		{
            // Calculate lighting strength
			vec3  lightDir = normalize(u_pointLightPositions[i] - f_pos);
			float diffuse = max(dot(normal, lightDir), 0.0f);
			float distance = length(u_pointLightPositions[i] - f_pos) * u_pointLightDistanceFactors[i];
			float attenuation = 1.0f / (1.0f + 0.07f * distance + 0.017f * (distance * distance));

            // Apply
            vec3 current = vec3(0.0f);
			current += vec3(diffuse); // Diffuse
            current += vec3(getSpecularValue(u_pointLightPositions[i], normal)); // Specular
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
		// Calculate distance
    	float fragmentDistance = abs(length(u_cameraPosition - f_pos));
        float distanceFactor = fragmentDistance / u_maxSpotLightDistance;
        distanceFactor = clamp(distanceFactor, 0.0f, 1.0f);
        distanceFactor = 1.0f - distanceFactor;

        // Calculate lighting strength
        vec3 result = vec3(0.0f);
        vec3 lightDirection = normalize(u_cameraPosition - f_pos);
        float smoothingFactor = 0.9f;
        float spotTheta = dot(lightDirection, normalize(-u_cameraFront));
        float epsilon   = u_maxSpotlightAngle - u_maxSpotlightAngle * smoothingFactor;
        float intensity = clamp((spotTheta - u_maxSpotlightAngle * smoothingFactor) / epsilon, 0.0f, 1.0f);  

        // Apply lighting calculations
        float diffuse = max(dot(normal, lightDirection), 0.0f);
        float specular = getSpecularValue(u_cameraPosition, normal);
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

// Calculate random float
float getRandomFloat(vec3 seed, int i) // http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping/#stratified-poisson-sampling
{
	vec4 seed4 = vec4(seed,i);
	float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
	return fract(sin(dot_product) * 43758.5453);
}

// Calculate shadow lighting
float getShadowValue()
{
	if(u_isShadowsEnabled)
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
				return 1.0f;
			}

			// Poisson values
			const vec2 poissonDisk[4] = vec2[]
			(
			  vec2(-0.94201624f, -0.39906216f),
			  vec2(0.94558609f, -0.76890725f),
			  vec2(-0.094184101f, -0.92938870f),
			  vec2(0.34495938f, 0.29387760)
			);

			// Calculate poisson sampled shadows
			for(int i = 0; i < 4; i++)
			{
				// Get random index
				int index = int(16.0f*getRandomFloat(floor(f_pos.xyz*1000.0f), i))%16;

				// Calculate depth from shadow map
				float shadowMapDepth = texture(u_sampler_shadowMap, projCoords.xy + (poissonDisk[index] / 700.0f)).r;

				// Apply result value
				if((currentDepth - texelSize) > shadowMapDepth)
				{
					shadow -= 0.15f; // Shadow
				}
				else
				{
					shadow -= 0.0f; // No shadow
				}
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
			return mix(shadow, 1.0f, alpha);
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

// Calculate fog color
vec3 applyFog(vec3 color)
{
	if(u_isFogEnabled)
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