#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// Constant variables
#define MAX_POINTLIGHT_COUNT 64
#define MAX_SPOTLIGHT_COUNT 64
#define FRAME_COLOR vec3(1.0f, 1.0f, 1.0f)
#define SPOTLIGHT_SMOOTHING_MULTIPLIER 0.95f

// In variables
in vec3 f_position;
in vec2 f_uv;
in vec3 f_normal;
in vec4 f_shadowPosition;
in mat3 f_tbnMatrix;

// Textures
layout (location = 0) uniform sampler2D u_shadowMap;
layout (location = 1) uniform sampler2D u_diffuseMap;
layout (location = 2) uniform sampler2D u_normalMap;
layout (location = 3) uniform sampler2D u_blendMap;
layout (location = 4) uniform sampler2D u_diffuseMapR;
layout (location = 5) uniform sampler2D u_diffuseMapG;
layout (location = 6) uniform sampler2D u_diffuseMapB;
layout (location = 7) uniform sampler2D u_normalMapR;
layout (location = 8) uniform sampler2D u_normalMapG;
layout (location = 9) uniform sampler2D u_normalMapB;

// Vector uniforms
uniform vec3 u_pointlightPositions[MAX_POINTLIGHT_COUNT];
uniform vec3 u_pointlightRadiuses[MAX_POINTLIGHT_COUNT];
uniform vec3 u_pointlightColors[MAX_POINTLIGHT_COUNT];
uniform vec3 u_spotlightPositions[MAX_SPOTLIGHT_COUNT];
uniform vec3 u_spotlightFrontVectors[MAX_SPOTLIGHT_COUNT];
uniform vec3 u_spotlightColors[MAX_SPOTLIGHT_COUNT];
uniform vec3 u_cameraPosition;
uniform vec3 u_ambientLightingColor;
uniform vec3 u_directionalLightingColor;
uniform vec3 u_directionalLightPosition;
uniform vec3 u_shadowAreaCenter;
uniform vec3 u_fogColor;

// Float uniforms
uniform float u_pointlightIntensities[MAX_POINTLIGHT_COUNT];
uniform float u_spotlightIntensities[MAX_SPOTLIGHT_COUNT];
uniform float u_spotlightAngles[MAX_SPOTLIGHT_COUNT];
uniform float u_spotlightDistances[MAX_SPOTLIGHT_COUNT];
uniform float u_lightness;
uniform float u_ambientLightingIntensity;
uniform float u_directionalLightingIntensity;
uniform float u_textureRepeat;
uniform float u_redRepeat;
uniform float u_greenRepeat;
uniform float u_blueRepeat;
uniform float u_shadowAreaSize;
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogThickness;
uniform float u_specularShininess;
uniform float u_specularIntensity;
uniform float u_shadowLightness;

// Integer uniforms
uniform int u_pointlightShapes[MAX_POINTLIGHT_COUNT];
uniform int u_pointlightCount;
uniform int u_spotlightCount;

// Boolean uniforms
uniform bool u_isWireFramed;
uniform bool u_isSpecular;
uniform bool u_isAmbientLightingEnabled;
uniform bool u_isDirectionalLightingEnabled;
uniform bool u_isFogEnabled;
uniform bool u_isShadowsEnabled;
uniform bool u_isShadowFrameRenderEnabled;
uniform bool u_hasDiffuseMap;
uniform bool u_hasNormalMap;
uniform bool u_hasBlendMap;
uniform bool u_hasDiffuseMapR;
uniform bool u_hasDiffuseMapG;
uniform bool u_hasDiffuseMapB;
uniform bool u_hasNormalMapR;
uniform bool u_hasNormalMapG;
uniform bool u_hasNormalMapB;

// Out variables
layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

// Functions
vec3 calculateDiffuseMapping();
vec3 calculateNormalMapping();
vec3 calculateAmbientLighting();
vec3 calculateDirectionalLighting(vec3 normal);
vec3 calculatePointlights(vec3 normal);
vec3 calculateSpotlights(vec3 normal);
vec3 calculateFog(vec3 color);
float calculateSpecularLighting(vec3 lightPosition, vec3 normal);
float calculateShadows();

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

	// Calculate normal mapping
    vec3 normal = calculateNormalMapping();

	// Calculate lighting
    float shadowLighting	 = calculateShadows();
	float shadowOcclusion	 = ((shadowLighting - u_shadowLightness) / (1.0f - u_shadowLightness));
	vec3 ambientLighting	 = (calculateAmbientLighting() * shadowLighting);
	vec3 directionalLighting = (calculateDirectionalLighting(normal) * shadowOcclusion);
	vec3 pointlights	     = calculatePointlights(normal);
	vec3 spotlights		     = calculateSpotlights(normal);

	// Calculate base color
	vec3 primaryColor = vec3(0.0f);
	primaryColor += calculateDiffuseMapping();
	primaryColor *= u_lightness;
	primaryColor  = clamp(primaryColor, vec3(0.0f), vec3(1.0f));

	// Apply lighting
	vec3 lighting = vec3(0.0f);
	lighting += ambientLighting;
	lighting += directionalLighting;
	lighting += pointlights;
	lighting += spotlights;
	primaryColor *= lighting;

	// Apply fog
	primaryColor = calculateFog(primaryColor);

	// Apply gamma correction
	primaryColor = pow(primaryColor, vec3(1.0f / 2.2f));

	// Set final colors
	o_primaryColor = vec4(primaryColor, 1.0f);
	o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

vec3 calculateDiffuseMapping()
{
	if (u_hasBlendMap) // Blendmapped mixed texture
	{
		// Get color value of blendmap (R, G, B)
		vec2 blendUV = (f_uv / u_textureRepeat);
		vec4 blendMapColor = texture(u_blendMap, blendUV);

		// Calculate diffuse map color
		vec3 diffuseMapColor = vec3(0.0f);
		if (u_hasDiffuseMap)
		{
			float blendMultiplier = (1.0f - blendMapColor.r - blendMapColor.g - blendMapColor.b);
			diffuseMapColor = (texture(u_diffuseMap, f_uv).rgb * blendMultiplier);
		}

		// Calculate blending color for every channel
		vec3 rColor = (u_hasDiffuseMapR ? (texture(u_diffuseMapR, (blendUV * u_redRepeat)).rgb * blendMapColor.r) : vec3(0.0f));
		vec3 gColor = (u_hasDiffuseMapG ? (texture(u_diffuseMapG, (blendUV * u_greenRepeat)).rgb * blendMapColor.g) : vec3(0.0f));
		vec3 bColor = (u_hasDiffuseMapB ? (texture(u_diffuseMapB, (blendUV * u_blueRepeat)).rgb * blendMapColor.b) : vec3(0.0f));
		rColor = pow(rColor, vec3(2.2f));
		gColor = pow(gColor, vec3(2.2f));
		bColor = pow(bColor, vec3(2.2f));

		// Compose final color
		vec3 newColor = (diffuseMapColor + rColor + gColor + bColor);
        
		// Return
		return newColor;
	}
	else if (u_hasDiffuseMap) // Diffuse texture
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

vec3 calculateNormalMapping()
{
    if (u_hasNormalMap || u_hasNormalMapR || u_hasNormalMapG || u_hasNormalMapB)
    {
		if (u_hasBlendMap) // Blendmapped mixed normal
		{
			// Get color values of blendmap (R, G, B)
			vec2 blendUV = (f_uv / u_textureRepeat);
			vec4 blendMapColor = texture(u_blendMap, blendUV);
			float diffuseStrength = (1.0f - blendMapColor.r - blendMapColor.g - blendMapColor.b);
			float rStrength = blendMapColor.r;
			float gStrength = blendMapColor.g;
			float bStrength = blendMapColor.b;

			// Calculate total normal vector
			vec3 totalNormal;

			// Diffuse normal map
			if (u_hasNormalMap)
			{
				vec3 normal = texture(u_normalMap, f_uv).rgb;
				normal *= 2.0f;
				normal -= 1.0f;
				totalNormal += (normalize(f_tbnMatrix * normal) * diffuseStrength);
			}
			else
			{
				totalNormal += f_normal * diffuseStrength;
			}
			
			// BlendR normal map
			if (u_hasNormalMapR)
			{
				vec3 normal = texture(u_normalMapR, (blendUV * u_redRepeat)).rgb;
				normal *= 2.0f;
				normal -= 1.0f;
				totalNormal += (normalize(f_tbnMatrix * normal) * rStrength);
			}
			else
			{
				totalNormal += f_normal * rStrength;
			}

			// BlendG normal map
			if (u_hasNormalMapG)
			{
				vec3 normal = texture(u_normalMapG, (blendUV * u_greenRepeat)).rgb;
				normal *= 2.0f;
				normal -= 1.0f;
				totalNormal += (normalize(f_tbnMatrix * normal) * gStrength);
			}
			else
			{
				totalNormal += f_normal * gStrength;
			}

			// BlendB normal map
			if (u_hasNormalMapB)
			{
				vec3 normal = texture(u_normalMapB, (blendUV * u_blueRepeat)).rgb;
				normal *= 2.0f;
				normal -= 1.0f;
				totalNormal += (normalize(f_tbnMatrix * normal) * bStrength);
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
			if (u_hasNormalMap)
			{
				// Calculate new normal vector
				vec3 normal = texture(u_normalMap, f_uv).rgb;
				normal *= 2.0f;
				normal -= 1.0f;
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

vec3 calculateAmbientLighting()
{
	if (u_isAmbientLightingEnabled)
	{
		return (u_ambientLightingColor * u_ambientLightingIntensity);
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 calculateDirectionalLighting(vec3 normal)
{
	if (u_isDirectionalLightingEnabled)
	{
        // Calculate lighting strength
        vec3 result = vec3(0.0f);
        vec3 direction = normalize(u_directionalLightPosition - f_position);
		float diffuse = clamp(dot(normal, direction), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(u_directionalLightPosition, normal);

        // Apply
        result += vec3(diffuse); // Diffuse
        result += vec3(specular); // Specular
        result *= u_directionalLightingColor; // Color
        result *= u_directionalLightingIntensity; // Intensity

        // Return
        return result;
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 calculatePointlights(vec3 normal)
{
	vec3 result = vec3(0.0f);
		
	// For every light
	for (int i = 0; i < u_pointlightCount; i++)
	{
		// Calculate light strength
		vec3 direction = normalize(u_pointlightPositions[i] - f_position);
		float diffuse = clamp(dot(normal, direction), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(u_pointlightPositions[i], normal);

		// Calculate light attenuation
		float attenuation;
		if (u_pointlightShapes[i] == 0)
		{
			float fragmentDistance = distance(u_pointlightPositions[i], f_position);
			float averageRadius = ((u_pointlightRadiuses[i].x + u_pointlightRadiuses[i].y + u_pointlightRadiuses[i].z) / 3.0f);
			attenuation = max(0.0f, (1.0f - (fragmentDistance / averageRadius)));
		}
		else
		{
			vec3 fragmentDistance = abs(u_pointlightPositions[i] - f_position);
			float xAttenuation = max(0.0f, (1.0f - (fragmentDistance.x / u_pointlightRadiuses[i].x)));
			float yAttenuation = max(0.0f, (1.0f - (fragmentDistance.y / u_pointlightRadiuses[i].y)));
			float zAttenuation = max(0.0f, (1.0f - (fragmentDistance.z / u_pointlightRadiuses[i].z)));
			attenuation = min(xAttenuation, min(yAttenuation, zAttenuation));
		}

		// Apply
		vec3 current = vec3(0.0f);
		current += vec3(diffuse); // Diffuse
		current += vec3(specular); // Specular
		current *= u_pointlightColors[i]; // Color
		current *= (attenuation * attenuation); // Distance
		current *= u_pointlightIntensities[i]; // Intensity

		// Add to total lighting value
		result += current;
	}

	// Return
	return result;
}

vec3 calculateSpotlights(vec3 normal)
{
	vec3 result = vec3(0.0f);

    // For every light
	for (int i = 0; i < u_spotlightCount; i++)
	{
		// Calculate light strength
		vec3 direction = normalize(u_spotlightPositions[i] - f_position);
		float spot = dot(direction, normalize(-u_spotlightFrontVectors[i]));
		float diffuse = clamp(dot(normal, direction), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(u_spotlightPositions[i], normal);
		float smoothingAngle = (u_spotlightAngles[i] * (1.0f - SPOTLIGHT_SMOOTHING_MULTIPLIER));
		float intensity = clamp(((spot - (u_spotlightAngles[i] * SPOTLIGHT_SMOOTHING_MULTIPLIER)) / smoothingAngle), 0.0f, 1.0f);  

		// Calculate light distance
		float fragmentDistance = distance(u_spotlightPositions[i], f_position);
		float distanceMultiplier = (fragmentDistance / u_spotlightDistances[i]);
		distanceMultiplier = clamp(distanceMultiplier, 0.0f, 1.0f);
		distanceMultiplier = (1.0f - distanceMultiplier);

		// Apply
		vec3 current = vec3(0.0f);
		current += vec3(diffuse * intensity); // Diffuse
		current += vec3(specular * intensity); // Specular
		current *= u_spotlightColors[i]; // Color
		current *= u_spotlightIntensities[i]; // Intensity
		current *= distanceMultiplier; // Distance

		// Add to total lighting value
		result += current;
	}

	// Return
	return result;
}

vec3 calculateFog(vec3 color)
{
	if (u_isFogEnabled)
	{
		// Calculate distance to fragment in world space
		float fragmentDistance = distance(f_position.xyz, u_cameraPosition);

        // Calculate fog intensity
		float distanceDifference = (u_fogMaxDistance - u_fogMinDistance);
		float fragmentPart = clamp(((fragmentDistance - u_fogMinDistance) / distanceDifference), 0.0f, 1.0f);
		float thickness = clamp(u_fogThickness, 0.0f, 1.0f);
		float mixValue = (fragmentPart * thickness);

		// Return
		return mix(color, u_fogColor, mixValue);
	}
	else
	{
		return color;
	}
}

float calculateSpecularLighting(vec3 lightPosition, vec3 normal)
{
    if (u_isSpecular)
    {
        // Calculate
        vec3 lightDirection   = normalize(lightPosition - f_position);
        vec3 viewDirection    = normalize(u_cameraPosition - f_position);
        vec3 halfWayDirection = normalize(lightDirection + viewDirection);
        float result          = pow(clamp(dot(normal, halfWayDirection), 0.0f, 1.0f), u_specularShininess);

        // Return
        return (result * u_specularIntensity);
    }
    else
    {
        return 0.0f;
    }
}

float calculateShadows()
{
	if (u_isShadowsEnabled)
	{
		// Temporary values
		float halfSize = (u_shadowAreaSize / 2.0f);
		float fragmentDistance = distance(f_position.xz, u_shadowAreaCenter.xz);

		// Check if fragment is within shadow area
		if (fragmentDistance <= halfSize)
		{
			// Variables
			float shadow       = 0.0f;
			vec3 projCoords    = (f_shadowPosition.xyz / f_shadowPosition.w) * 0.5f + 0.5f;
			float currentDepth = projCoords.z;
			vec2 texelSize     = (vec2(1.0f) / textureSize(u_shadowMap, 0));

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
			if (shadow > 1.0f)
			{
				shadow = 1.0f;
			}

			// Long-distance shadows fading
			float alpha = (fragmentDistance - (halfSize * 0.9f)); // Only for the outer 10% of the shadowed area
			alpha = clamp(alpha, 0.0f, halfSize * 0.1f); // Cannot be negative
			alpha /= (halfSize * 0.1f); // Convert value to 0.0 - 1.0 range

			// Debug area frame rendering
			if (u_isShadowFrameRenderEnabled)
			{
				if ((fragmentDistance - (halfSize * 0.99f)) > 0.0f)
				{
					return 0.0f;
				}
			}

			// Return
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