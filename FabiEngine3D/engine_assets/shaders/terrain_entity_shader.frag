#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// Const variables
#define MAX_POINT_LIGHT_COUNT 128

// In variables
in vec3 f_pos;
in vec2 f_uv;
in vec3 f_normal;
in vec4 f_shadowPos;
in mat3 f_tbnMatrix;

// Textures
layout (location = 0) uniform sampler2D u_diffuseMap;
layout (location = 1) uniform sampler2D u_normalMap;
layout (location = 2) uniform sampler2D u_blendMap;
layout (location = 3) uniform sampler2D u_diffuseMapR;
layout (location = 4) uniform sampler2D u_diffuseMapG;
layout (location = 5) uniform sampler2D u_diffuseMapB;
layout (location = 6) uniform sampler2D u_normalMapR;
layout (location = 7) uniform sampler2D u_normalMapG;
layout (location = 8) uniform sampler2D u_normalMapB;
layout (location = 9) uniform sampler2D u_shadowMap;

// Vec3 uniforms
uniform vec3 u_pointLightPositions[MAX_POINT_LIGHT_COUNT];
uniform vec3 u_pointLightRadiuses[MAX_POINT_LIGHT_COUNT];
uniform vec3 u_pointLightColors[MAX_POINT_LIGHT_COUNT];
uniform vec3 u_cameraPosition;
uniform vec3 u_cameraFront;
uniform vec3 u_ambientLightColor;
uniform vec3 u_directionalLightColor;
uniform vec3 u_directionalLightPosition;
uniform vec3 u_spotLightColor;
uniform vec3 u_shadowAreaCenter;
uniform vec3 u_fogColor;

// Float uniforms
uniform float u_pointLightIntensities[MAX_POINT_LIGHT_COUNT];
uniform float u_lightness;
uniform float u_ambientLightIntensity;
uniform float u_directionalLightIntensity;
uniform float u_diffuseMapRepeat;
uniform float u_diffuseMapRepeatR;
uniform float u_diffuseMapRepeatG;
uniform float u_diffuseMapRepeatB;
uniform float u_shadowAreaSize;
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogThickness;
uniform float u_specularLightFactor;
uniform float u_specularLightIntensity;
uniform float u_maxSpotlightAngle;
uniform float u_spotLightIntensity;
uniform float u_maxSpotLightDistance;
uniform float u_shadowLightness;

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
uniform bool u_isLightedShadowingEnabled;
uniform bool u_isSpecularLightEnabled;
uniform bool u_hasDiffuseMap;
uniform bool u_hasNormalMap;
uniform bool u_hasBlendMap;
uniform bool u_hasDiffuseMapR;
uniform bool u_hasDiffuseMapG;
uniform bool u_hasDiffuseMapB;
uniform bool u_hasNormalMapR;
uniform bool u_hasNormalMapG;
uniform bool u_hasNormalMapB;

// Integer uniforms
uniform int u_pointLightCount;

// Out variables
layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

// Functions
vec3 getNormalMapping();
vec3 getDiffuseMapping();
vec3 getAmbientLighting();
vec3 getDirectionalLighting(vec3 normal, bool noShadowOcclusion);
vec3 getPointLighting(vec3 normal);
vec3 getSpotLighting(vec3 normal);
vec3 getFog(vec3 color);
float getSpecularLighting(vec3 position, vec3 normal);
float getShadows();

// Process fragment
void main()
{
	// Calculate new normal vector
    vec3 normal = getNormalMapping();

	// Calculate lighting
    float shadow	 = getShadows();
	vec3 ambient	 = getAmbientLighting();
	vec3 directional = getDirectionalLighting(normal, (u_isLightedShadowingEnabled ? true : (shadow == 1.0f)));
	vec3 point		 = getPointLighting(normal);
	vec3 spot		 = getSpotLighting(normal);

	// Calculate primary color
	vec3 primaryColor;
	primaryColor  = getDiffuseMapping();
	primaryColor *= u_lightness;
	primaryColor  = clamp(primaryColor, vec3(0.0f), vec3(1.0f));
	primaryColor *= vec3(((ambient + directional) * shadow) + point + spot);
	primaryColor  = getFog(primaryColor);
	primaryColor  = pow(primaryColor, vec3(1.0f / 2.2f));

	// Set final colors
	o_primaryColor   = vec4(primaryColor, 1.0f);
	o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

vec3 getNormalMapping()
{
    if
    (
		u_isNormalMappingEnabled && 
		((u_isNormalMapped && u_hasNormalMap)  || 
		(u_isNormalMappedR && u_hasNormalMapR) || 
		(u_isNormalMappedG && u_hasNormalMapG) || 
		(u_isNormalMappedB && u_hasNormalMapB))
	)
    {
		if(u_isBlendMapped && u_hasBlendMap) // Blendmapped mixed normal
		{
			// Get color values of blendmap (R, G, B)
			vec2 blendUV = f_uv / u_diffuseMapRepeat;
			vec4 blendMapColor = texture(u_blendMap, blendUV);
			float diffuseStrength = (1.0f - blendMapColor.r - blendMapColor.g - blendMapColor.b);
			float rStrength = blendMapColor.r;
			float gStrength = blendMapColor.g;
			float bStrength = blendMapColor.b;

			// Calculate total normal vector
			vec3 totalNormal;

			// Diffuse normal map
			if(u_isNormalMapped && u_hasNormalMap)
			{
				vec3 normal = texture(u_normalMap, f_uv).rgb * 2.0f - 1.0f;
				totalNormal += normalize(f_tbnMatrix * normal) * diffuseStrength;
			}
			else
			{
				totalNormal += f_normal * diffuseStrength;
			}
			
			// BlendR normal map
			if(u_isNormalMappedR && u_hasNormalMapR)
			{
				vec3 normal = texture(u_normalMapR, blendUV * u_diffuseMapRepeatR).rgb * 2.0f - 1.0f;
				totalNormal += normalize(f_tbnMatrix * normal) * rStrength;
			}
			else
			{
				totalNormal += f_normal * rStrength;
			}

			// BlendG normal map
			if(u_isNormalMappedG && u_hasNormalMapG)
			{
				vec3 normal = texture(u_normalMapG, blendUV * u_diffuseMapRepeatG).rgb * 2.0f - 1.0f;
				totalNormal += normalize(f_tbnMatrix * normal) * gStrength;
			}
			else
			{
				totalNormal += f_normal * gStrength;
			}

			// BlendB normal map
			if(u_isNormalMappedB && u_hasNormalMapB)
			{
				vec3 normal = texture(u_normalMapB, blendUV * u_diffuseMapRepeatB).rgb * 2.0f - 1.0f;
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
			if(u_isNormalMapped && u_hasNormalMap)
			{
				// Calculate new normal vector
				vec3 normal = texture(u_normalMap, f_uv).rgb;
				normal = normal * 2.0f - 1.0f;
				normal = normalize(f_tbnMatrix * normal);

				// Return
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

vec3 getDiffuseMapping()
{
	if(u_isBlendMapped && u_hasBlendMap) // Blendmapped mixed texture
	{
		// Get color value of blendmap (R, G, B)
		vec2 blendUV = f_uv / u_diffuseMapRepeat;
		vec4 blendMapColor = texture(u_blendMap, blendUV);

		// Calculate diffuse color
		vec3 diffuseMapColor = vec3(0.0f);
		if(u_hasDiffuseMap)
		{
			diffuseMapColor = texture(u_diffuseMap, f_uv).rgb* (1.0f - blendMapColor.r - blendMapColor.g - blendMapColor.b);
		}

		// Calculate blending color for every channel
		vec3 rColor = u_hasDiffuseMapR ? (texture(u_diffuseMapR, blendUV * u_diffuseMapRepeatR).rgb * blendMapColor.r) : vec3(0.0f);
		vec3 gColor = u_hasDiffuseMapG ? (texture(u_diffuseMapG, blendUV * u_diffuseMapRepeatG).rgb * blendMapColor.g) : vec3(0.0f);
		vec3 bColor = u_hasDiffuseMapB ? (texture(u_diffuseMapB, blendUV * u_diffuseMapRepeatB).rgb * blendMapColor.b) : vec3(0.0f);
		rColor = pow(rColor, vec3(2.2f));
		gColor = pow(gColor, vec3(2.2f));
		bColor = pow(bColor, vec3(2.2f));

		// Compose final color
		vec3 newColor = diffuseMapColor + rColor + gColor + bColor;
        
		// Return
		return newColor;
	}
	else if(u_hasDiffuseMap) // Diffuse texture
	{
		// Calculate
		vec3 newColor = texture(u_diffuseMap, vec2(-f_uv.x, f_uv.y)).rgb;
		newColor = pow(newColor, vec3(2.2f));

		// Return
		return newColor;
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 getAmbientLighting()
{
	if(u_isAmbientLightEnabled)
	{
		return (u_ambientLightColor * u_ambientLightIntensity);
	}
	else
	{
		return vec3(0.0f);
	}
}

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
        result += vec3(getSpecularLighting(u_directionalLightPosition, normal)) * float(noShadowOcclusion); // Specular
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

vec3 getPointLighting(vec3 normal)
{
	if(u_isPointLightEnabled)
	{
		vec3 result = vec3(0.0f);
		
        // For every pointLight
		for (int i = 0; i < u_pointLightCount; i++)
		{
            // Calculate light strength
			vec3 lightDir = normalize(u_pointLightPositions[i] - f_pos);
			float diffuse = max(dot(normal, lightDir), 0.0f);
			float specular = getSpecularLighting(u_pointLightPositions[i], normal);

			// Calculate light attenuation
			vec3 distance = abs(u_pointLightPositions[i] - f_pos);
			float attenuation = max(0.0f, 1.0f - (distance.x / u_pointLightRadiuses[i].x));
			attenuation = min(attenuation, max(0.0f, 1.0f - (distance.y / u_pointLightRadiuses[i].y)));
			attenuation = min(attenuation, max(0.0f, 1.0f - (distance.z / u_pointLightRadiuses[i].z)));

            // Apply
            vec3 current = vec3(0.0f);
			current += vec3(diffuse); // Diffuse
            current += vec3(specular); // Specular
            current *= u_pointLightColors[i]; // Color
            current *= (attenuation * attenuation); // Distance
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
        float specular = getSpecularLighting(u_cameraPosition, normal);
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

vec3 getFog(vec3 color)
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

		// Return
		return mix(color, u_fogColor, mixValue);
	}
	else
	{
		return color;
	}
}

float getSpecularLighting(vec3 position, vec3 normal)
{
    if(u_isSpecularLightEnabled && u_isSpecularLighted)
    {
        // Calculate
        vec3 lightDirection   = normalize(position - f_pos);
        vec3 viewDirection    = normalize(u_cameraPosition - f_pos);
        vec3 halfWayDirection = normalize(lightDirection + viewDirection);
        float result          = pow(max(dot(normal, halfWayDirection), 0.0f), u_specularLightFactor);

        // Return
        return (result * u_specularLightIntensity);
    }
    else
    {
        return 0.0f;
    }
}

float getShadows()
{
	if(u_isShadowsEnabled)
	{
		float halfSize = u_shadowAreaSize / 2.0f;

		// Check if fragment is within shadow area
		if
		(
			abs(f_pos.x - u_shadowAreaCenter.x) <= halfSize && 
			abs(f_pos.z - u_shadowAreaCenter.z) <= halfSize
		)
		{
			// Variables
			float shadow       = 0.0f;
			vec3 projCoords    = (f_shadowPos.xyz / f_shadowPos.w) * 0.5f + 0.5f;
			float currentDepth = projCoords.z;
			vec2 texelSize    = (vec2(1.0f) / textureSize(u_shadowMap, 0));

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
					float pcfDepth = texture(u_shadowMap, projCoords.xy + (vec2(x, y) * texelSize)).r; 
					shadow += (currentDepth - texelSize.x > pcfDepth) ? u_shadowLightness : 1.0f;        
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

			// Return
			if(u_isLightedShadowingEnabled)
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