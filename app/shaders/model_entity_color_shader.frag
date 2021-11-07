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
in vec4 f_clip;
in mat3 f_tbnMatrix;

// Textures
layout (location = 0) uniform samplerCube u_previousCubeReflectionMap;
layout (location = 1) uniform samplerCube u_currentCubeReflectionMap;
layout (location = 2) uniform sampler2D u_planarReflectionMap;
layout (location = 3) uniform sampler2D u_shadowMap;
layout (location = 4) uniform sampler2D u_diffuseMap;
layout (location = 5) uniform sampler2D u_emissionMap;
layout (location = 6) uniform sampler2D u_specularMap;
layout (location = 7) uniform sampler2D u_reflectionMap;
layout (location = 8) uniform sampler2D u_normalMap;

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
uniform vec3 u_color;
uniform vec3 u_fogColor;
uniform vec3 u_shadowAreaCenter;

// Float uniforms
uniform float u_pointlightIntensities[MAX_POINTLIGHT_COUNT];
uniform float u_spotlightIntensities[MAX_SPOTLIGHT_COUNT];
uniform float u_spotlightAngles[MAX_SPOTLIGHT_COUNT];
uniform float u_spotlightDistances[MAX_SPOTLIGHT_COUNT];
uniform float u_ambientLightingIntensity;
uniform float u_directionalLightingIntensity;
uniform float u_specularShininess;
uniform float u_specularIntensity;
uniform float u_alpha;
uniform float u_minTextureAlpha;
uniform float u_colorInversion;
uniform float u_shadowAreaSize;
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogThickness;
uniform float u_reflectivity;
uniform float u_lightness;
uniform float u_shadowLightness;
uniform float u_cubeReflectionMixValue;
uniform float u_emissionIntensity;

// Integer uniforms
uniform int u_pointlightShapes[MAX_POINTLIGHT_COUNT];
uniform int u_pointlightCount;
uniform int u_spotlightCount;
uniform int u_reflectionType;

// Boolean uniforms
uniform bool u_isWireFramed;
uniform bool u_isReflective;
uniform bool u_isSpecular;
uniform bool u_isShadowFrameRenderEnabled;
uniform bool u_isAmbientLightingEnabled;
uniform bool u_isDirectionalLightingEnabled;
uniform bool u_isReflectionsEnabled;
uniform bool u_isFogEnabled;
uniform bool u_isShadowsEnabled;
uniform bool u_hasDiffuseMap;
uniform bool u_hasEmissionMap;
uniform bool u_hasReflectionMap;
uniform bool u_hasNormalMap;
uniform bool u_hasSpecularMap;
uniform bool u_isBright;

// Out variables
layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

// Functions
vec3 calculateDiffuseMapping();
vec3 calculateEmissionMapping();
vec3 calculateSpecularMapping();
vec3 calculateReflectionMapping();
vec3 calculateNormalMapping();
vec3 calculateAmbientLighting();
vec3 calculateDirectionalLighting(vec3 specularMapColor, vec3 normal);
vec3 calculatePointlights(vec3 specularMapColor, vec3 normal);
vec3 calculateSpotlights(vec3 specularMapColor, vec3 normal);
vec3 calculateFog(vec3 color);
vec3 calculateCubeReflection(vec3 reflectionMapColor, vec3 color, vec3 normal);
vec3 calculatePlanarReflection(vec3 reflectionMapColor, vec3 color);
float calculateSpecularLighting(vec3 specularMapColor, vec3 lightPosition, vec3 normal);
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

	// Calculate diffuse mapping
	vec3 diffuseMapping = calculateDiffuseMapping();

	// Calculate emission mapping
	vec3 emissionMapping = calculateEmissionMapping();

	// Calculate specular mapping
    vec3 specularMapping = calculateSpecularMapping();

	// Calculate reflection mapping
    vec3 reflectionMapping = calculateReflectionMapping();

    // Calculate normal mapping
    vec3 normalMapping = calculateNormalMapping();

	// Calculate lighting
	float shadowLighting	 = calculateShadows();
	float shadowOcclusion	 = ((shadowLighting - u_shadowLightness) / (1.0f - u_shadowLightness));
	vec3 ambientLighting	 = (calculateAmbientLighting() * shadowLighting);
	vec3 directionalLighting = (calculateDirectionalLighting(specularMapping, normalMapping) * shadowOcclusion);
	vec3 pointlights		 = calculatePointlights(specularMapping, normalMapping);
	vec3 spotlights		     = calculateSpotlights(specularMapping, normalMapping);

	// Calculate base color
	vec3 primaryColor = vec3(0.0f);
	primaryColor += diffuseMapping;
	primaryColor += emissionMapping;
	primaryColor  = calculateCubeReflection(reflectionMapping, primaryColor, normalMapping);
	primaryColor  = calculatePlanarReflection(reflectionMapping, primaryColor);
	primaryColor *= u_color;
	primaryColor *= u_lightness;
	primaryColor  = clamp(primaryColor, vec3(0.0f), vec3(1.0f));
	primaryColor  = mix(primaryColor, (vec3(1.0f) - primaryColor), clamp(u_colorInversion, 0.0f, 1.0f));
	
	// Apply lighting
	bool isBright = ((emissionMapping != vec3(0.0f)) || u_isBright);
	if (!isBright)
	{
		vec3 lighting = vec3(0.0f);
		lighting += ambientLighting;
		lighting += directionalLighting;
		lighting += pointlights;
		lighting += spotlights;
		primaryColor *= lighting;
	}

	// Apply fog
	primaryColor = calculateFog(primaryColor);

	// Apply gamma correction
    primaryColor = pow(primaryColor, vec3(1.0f / 2.2f));

	// Set final colors
	o_primaryColor = vec4(primaryColor, u_alpha);
	o_secondaryColor = vec4((isBright ? primaryColor : vec3(0.0f)), 1.0f);
}

vec3 calculateDiffuseMapping()
{
	if (u_hasDiffuseMap)
	{
		// Calculate diffuse map color
		vec4 diffuseMapColor = texture(u_diffuseMap, f_uv);
		diffuseMapColor.rgb = pow(diffuseMapColor.rgb, vec3(2.2f));

		// Check if transparent
		if (diffuseMapColor.a < u_minTextureAlpha)
		{
			discard;
		}

		// Return
		return diffuseMapColor.rgb;
	}
	else
	{
		return vec3(1.0f);
	}
}

vec3 calculateEmissionMapping()
{
	if (u_hasEmissionMap)
	{
		// Calculate emission map color
		vec4 emissionMapColor = texture(u_emissionMap, f_uv);

		// Check if transparent
		if (emissionMapColor.a < u_minTextureAlpha)
		{
			return vec3(0.0f);
		}

		// Return
		return (emissionMapColor.rgb * u_emissionIntensity);
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 calculateSpecularMapping()
{
    if (u_hasSpecularMap)
    {
		// Calculation reflection color
		vec4 specularMapColor = texture(u_specularMap, f_uv);

		// Check if transparent
		if (specularMapColor.a < u_minTextureAlpha)
		{
			return vec3(0.0f);
		}

		// Return
		return specularMapColor.rgb;
	}
	else
	{
		return vec3(1.0f);
	}
}

vec3 calculateReflectionMapping()
{
    if (u_hasReflectionMap)
    {
		// Calculation reflection color
		vec4 reflectionMapColor = texture(u_reflectionMap, f_uv);

		// Check if transparent
		if (reflectionMapColor.a < u_minTextureAlpha)
		{
			return vec3(0.0f);
		}

		// Return
		return reflectionMapColor.rgb;
	}
	else
	{
		return vec3(1.0f);
	}
}

vec3 calculateNormalMapping()
{
    if (u_hasNormalMap)
    {
        // Calculate new normal vector
        vec3 normal = texture(u_normalMap, f_uv).rgb;
        normal = ((normal * 2.0f) - 1.0f);
        normal = normalize(f_tbnMatrix * normal);

        // Return
        return normal;
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

vec3 calculateDirectionalLighting(vec3 specularMapColor, vec3 normal)
{
	if (u_isDirectionalLightingEnabled)
	{
        // Calculate lighting strength
        vec3 result = vec3(0.0f);
		vec3 direction = normalize(u_directionalLightPosition - f_position);
		float diffuse = clamp(dot(normal, direction), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(specularMapColor, u_directionalLightPosition, normal);

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

vec3 calculatePointlights(vec3 specularMapColor, vec3 normal)
{
	vec3 result = vec3(0.0f);

	// For every light
	for (int i = 0; i < u_pointlightCount; i++)
	{
		// Calculate light strength
		vec3 direction = normalize(u_pointlightPositions[i] - f_position);
		float diffuse = clamp(dot(normal, direction), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(specularMapColor, u_pointlightPositions[i], normal);

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

vec3 calculateSpotlights(vec3 specularMapColor, vec3 normal)
{
	vec3 result = vec3(0.0f);

	// For every light
	for (int i = 0; i < u_spotlightCount; i++)
	{
		// Calculate light strength
		vec3 direction = normalize(u_spotlightPositions[i] - f_position);
		float spot = dot(direction, normalize(-u_spotlightFrontVectors[i]));
		float diffuse = clamp(dot(normal, direction), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(specularMapColor, u_spotlightPositions[i], normal);
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
		// Calculate
        float fragmentDistance = distance(f_position.xyz, u_cameraPosition);
		float distanceDifference = (u_fogMaxDistance - u_fogMinDistance);
		float distancePart = clamp(((fragmentDistance - u_fogMinDistance) / distanceDifference), 0.0f, 1.0f);
		float thickness = clamp(u_fogThickness, 0.0f, 1.0f);
		float mixValue = (distancePart * thickness);

		// Return
		return mix(color, u_fogColor, mixValue);
	}
	else
	{
		return color;
	}
}

vec3 calculateCubeReflection(vec3 reflectionMapColor, vec3 color, vec3 normal)
{
	if (u_isReflectionsEnabled && u_isReflective && (u_reflectionType == 0))
	{		
		// Check if current texel allows for reflection
		if (reflectionMapColor != vec3(0.0f))
		{
			// Calculate
			vec3 viewDirection = normalize(f_position - u_cameraPosition);
			vec3 reflectionDirection = reflect(viewDirection, normal);
			vec3 previousCubeReflectionMapColor = texture(u_previousCubeReflectionMap, reflectionDirection).rgb;
			vec3 currentCubeReflectionMapColor = texture(u_currentCubeReflectionMap, reflectionDirection).rgb;
			vec3 cubeReflectionMapColor = mix(previousCubeReflectionMapColor, currentCubeReflectionMapColor, u_cubeReflectionMixValue);
			vec3 mixedColor = mix(color, cubeReflectionMapColor, u_reflectivity);

			// Return
			return mixedColor;
		}

		// Return
		return color;
	}
	else
	{
		return color;
	}
}

vec3 calculatePlanarReflection(vec3 reflectionMapColor, vec3 color)
{
	if (u_isReflectionsEnabled && u_isReflective && (u_reflectionType == 1))
	{
		// Check if current texel allows for reflection
		if (reflectionMapColor != vec3(0.0f))
		{
			// Calculate
			vec2 ndc = (((f_clip.xy / f_clip.w) / 2.0f) + 0.5f);
			vec2 texCoords = vec2(ndc.x, -ndc.y);
			vec3 reflectionColor = texture(u_planarReflectionMap, vec2(texCoords.x,  texCoords.y)).rgb;
			vec3 mixedColor = mix(color, reflectionColor, u_reflectivity);
        
        	// Return
			return mixedColor;
		}

		return color;
	}
	else
	{
		return color;
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
			vec2 texelSize = (vec2(1.0f) / textureSize(u_shadowMap, 0));
			float shadow = 0.0f;
			vec3 projCoords = (((f_shadowPosition.xyz / f_shadowPosition.w) * 0.5f) + 0.5f);
			float currentDepth = projCoords.z;
			float bias = 0.00075f;

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
					shadow += ((currentDepth - texelSize.x) > pcfDepth) ? u_shadowLightness : 1.0f;        
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

float calculateSpecularLighting(vec3 specularMapColor, vec3 lightPosition, vec3 normal)
{
    if (u_isSpecular)
    {
    	// Calculate
        vec3 lightDirection = normalize(lightPosition - f_position);
        vec3 viewDirection = normalize(u_cameraPosition - f_position);
        vec3 halfWayDirection = normalize(lightDirection + viewDirection);
		float specularMapIntensity = ((specularMapColor.r + specularMapColor.g + specularMapColor.b) / 3.0f);
        float result = pow(clamp(dot(normal, halfWayDirection), 0.0f, 1.0f), (u_specularShininess * specularMapIntensity));

        // Return
        return (result * u_specularIntensity * specularMapIntensity);
    }
    else
    {
        return 0.0f;
    }
}