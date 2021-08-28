#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// Constant variables
#define MAX_LIGHT_AMOUNT 128

// In variables
in vec3 f_pos;
in vec2 f_uv;
in vec3 f_normal;
in vec4 f_shadowPos;
in vec4 f_clip;
in mat3 f_tbnMatrix;

// Textures
layout (location = 0) uniform samplerCube u_previousCubeReflectionMap;
layout (location = 1) uniform samplerCube u_currentCubeReflectionMap;
layout (location = 2) uniform sampler2D u_planarReflectionMap;
layout (location = 3) uniform sampler2D u_shadowMap;
layout (location = 4) uniform sampler2D u_diffuseMap;
layout (location = 5) uniform sampler2D u_emissionMap;
layout (location = 6) uniform sampler2D u_reflectionMap;
layout (location = 7) uniform sampler2D u_normalMap;

// Vector uniforms
uniform vec3 u_lightPositions[MAX_LIGHT_AMOUNT];
uniform vec3 u_lightRadiuses[MAX_LIGHT_AMOUNT];
uniform vec3 u_lightColors[MAX_LIGHT_AMOUNT];
uniform vec3 u_cameraPosition;
uniform vec3 u_cameraFront;
uniform vec3 u_ambientLightingColor;
uniform vec3 u_directionalLightColor;
uniform vec3 u_directionalLightPosition;
uniform vec3 u_spotLightingColor;
uniform vec3 u_color;
uniform vec3 u_fogColor;
uniform vec3 u_shadowAreaCenter;

// Float uniforms
uniform float u_lightIntensities[MAX_LIGHT_AMOUNT];
uniform float u_ambientLightingIntensity;
uniform float u_directionalLightingIntensity;
uniform float u_specularLightingFactor;
uniform float u_specularLightingIntensity;
uniform float u_alpha;
uniform float u_minDiffuseMapAlpha;
uniform float u_inversion;
uniform float u_shadowAreaSize;
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogThickness;
uniform float u_spotLightingIntensity;
uniform float u_maxSpotLightingAngle;
uniform float u_maxSpotLightingDistance;
uniform float u_reflectivity;
uniform float u_lightness;
uniform float u_shadowLightness;
uniform float u_cubeReflectionMixValue;

// Integer uniforms
uniform int u_lightShapes[MAX_LIGHT_AMOUNT];

// Boolean uniforms
uniform bool u_isWireFramed;
uniform bool u_isTransparent;
uniform bool u_isPlanarReflective;
uniform bool u_isCubeReflective;
uniform bool u_isSpecularLighted;
uniform bool u_isShadowFrameRenderEnabled;
uniform bool u_isAmbientLightingEnabled;
uniform bool u_isDirectionalLightingEnabled;
uniform bool u_isSpotLightingEnabled;
uniform bool u_isReflectionsEnabled;
uniform bool u_isFogEnabled;
uniform bool u_isShadowsEnabled;
uniform bool u_hasDiffuseMap;
uniform bool u_hasEmissionMap;
uniform bool u_hasNormalMap;
uniform bool u_hasReflectionMap;
uniform bool u_isBright;

// Integer uniforms
uniform int u_lightCount;

// Out variables
layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

// Functions
vec3 calculateNormalMapping();
vec3 calculateDiffuseMapping();
vec3 calculateEmissionMapping();
vec3 calculateAmbientLighting();
vec3 calculateDirectionalLighting(vec3 normal);
vec3 calculateSpotLighting(vec3 normal);
vec3 calculateLights(vec3 normal);
vec3 calculateFog(vec3 color);
vec3 calculateCubeReflections(vec3 color, vec3 normal);
vec3 calculatePlanarReflections(vec3 color);
float calculateSpecularLighting(vec3 position, vec3 normal);
float calculateShadows();

// Process fragment
void main()
{
	// Wire frame color
	if(u_isWireFramed)
	{
		o_primaryColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
		return;
	}

    // Calculate emission mapping
    vec3 emissionMapColor = calculateEmissionMapping();
	bool isBright = ((emissionMapColor != vec3(0.0f)) || u_isBright);

    // Calculate normal mapping
    vec3 normal = calculateNormalMapping();

	// Calculate lighting
	float shadowLighting	 = calculateShadows();
	float shadowOcclusion	 = ((shadowLighting - u_shadowLightness) / (1.0f - u_shadowLightness));
	vec3 ambientLighting	 = (calculateAmbientLighting() * shadowLighting);
	vec3 directionalLighting = (calculateDirectionalLighting(normal) * shadowOcclusion);
	vec3 spotLighting		 = calculateSpotLighting(normal);
	vec3 lights			     = calculateLights(normal);

	// Calculate base color
	vec3 primaryColor = vec3(0.0f);
	primaryColor += calculateDiffuseMapping();
	primaryColor += emissionMapColor;
	primaryColor  = calculatePlanarReflections(primaryColor);
	primaryColor  = calculateCubeReflections(primaryColor, normal);
	primaryColor *= u_color;
	primaryColor *= u_lightness;
	primaryColor  = clamp(primaryColor, vec3(0.0f), vec3(1.0f));
	primaryColor  = mix(primaryColor, (vec3(1.0f) - primaryColor), clamp(u_inversion, 0.0f, 1.0f));
	
	// Apply lighting
	if (!isBright)
	{
		vec3 lighting = vec3(0.0f);
		lighting += ambientLighting;
		lighting += directionalLighting;
		lighting += spotLighting;
		lighting += lights;
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

vec3 calculateDiffuseMapping()
{
	if (!u_hasDiffuseMap)
	{
		return vec3(1.0f);
	}
	else
	{
		// Calculate diffuse map color
		vec4 diffuseMapColor = texture(u_diffuseMap, f_uv);
		diffuseMapColor.rgb = pow(diffuseMapColor.rgb, vec3(2.2f));

		// Removing alpha background
		if (u_isTransparent)
		{
			if (diffuseMapColor.a < u_minDiffuseMapAlpha)
			{
				discard;
			}
		}

		// Return
		return diffuseMapColor.rgb;
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
		vec3 lightDirection = normalize(u_directionalLightPosition - f_pos);
		float diffuse = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(u_directionalLightPosition, normal);

        // Apply
        result += vec3(diffuse); // Diffuse
        result += vec3(specular); // Specular
        result *= u_directionalLightColor; // Color
        result *= u_directionalLightingIntensity; // Intensity

        // Return
        return result;
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 calculateLights(vec3 normal)
{
	vec3 result = vec3(0.0f);
		
	// For every light
	for (int i = 0; i < u_lightCount; i++)
	{
		// Calculate light strength
		vec3 lightDirection = normalize(u_lightPositions[i] - f_pos);
		float diffuse = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(u_lightPositions[i], normal);

		// Calculate light attenuation
		float attenuation;
		if (u_lightShapes[i] == 0)
		{
			float fragmentDistance = distance(u_lightPositions[i], f_pos);
			float averageRadius = ((u_lightRadiuses[i].x + u_lightRadiuses[i].y + u_lightRadiuses[i].z) / 3.0f);
			attenuation = max(0.0f, (1.0f - (fragmentDistance / averageRadius)));
		}
		else
		{
			vec3 fragmentDistance = abs(u_lightPositions[i] - f_pos);
			float xAttenuation = max(0.0f, (1.0f - (fragmentDistance.x / u_lightRadiuses[i].x)));
			float yAttenuation = max(0.0f, (1.0f - (fragmentDistance.y / u_lightRadiuses[i].y)));
			float zAttenuation = max(0.0f, (1.0f - (fragmentDistance.z / u_lightRadiuses[i].z)));
			attenuation = min(xAttenuation, min(yAttenuation, zAttenuation));
		}

		// Apply
		vec3 current = vec3(0.0f);
		current += vec3(diffuse); // Diffuse
		current += vec3(specular); // Specular
		current *= u_lightColors[i]; // Color
		current *= (attenuation * attenuation); // Distance
		current *= u_lightIntensities[i]; // Intensity

		// Add to total lighting value
		result += current;
	}

	// Return
	return result;
}

vec3 calculateSpotLighting(vec3 normal)
{
    if (u_isSpotLightingEnabled)
    {
    	// Calculate distance
        float fragmentDistance = distance(u_cameraPosition, f_pos);
        float distanceFactor = (fragmentDistance / u_maxSpotLightingDistance);
        distanceFactor = clamp(distanceFactor, 0.0f, 1.0f);
        distanceFactor = 1.0f - distanceFactor;

        // Calculate lighting strength
        vec3 lightDirection = normalize(u_cameraPosition - f_pos);
        float smoothingFactor = 0.9f;
        float spotTheta = dot(lightDirection, normalize(-u_cameraFront));
        float epsilon = u_maxSpotLightingAngle - u_maxSpotLightingAngle * smoothingFactor;
        float intensity = clamp((spotTheta - u_maxSpotLightingAngle * smoothingFactor) / epsilon, 0.0f, 1.0f);
		float diffuse = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
        float specular = calculateSpecularLighting(u_cameraPosition, normal);

        // Apply lighting calculations
		vec3 result = vec3(0.0f);
        result += vec3(diffuse * intensity); // Diffuse
        result += vec3(specular * intensity); // Specular
        result *= u_spotLightingColor; // Color
        result *= u_spotLightingIntensity; // Intensity

        // Return
        return (result * distanceFactor);
    }
    else
    {
        return vec3(0.0f);
    }
}

vec3 calculateEmissionMapping()
{
	if (u_hasEmissionMap)
	{
		return texture(u_emissionMap, f_uv).rgb;
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 calculateFog(vec3 color)
{
	if (u_isFogEnabled)
	{
		// Calculate
        float fragmentDistance = distance(f_pos.xyz, u_cameraPosition);
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

vec3 calculateCubeReflections(vec3 color, vec3 normal)
{
	if (u_isReflectionsEnabled && u_isCubeReflective)
	{
		// Calculation reflection color
		vec3 reflectionMapColor = (u_hasReflectionMap ? texture(u_reflectionMap, f_uv).rgb : vec3(0.0f));
		
		// Check if current texel allows for reflection
		if (reflectionMapColor != vec3(0.0f))
		{
			// Calculate
			vec3 viewDirection = normalize(f_pos - u_cameraPosition);
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

vec3 calculatePlanarReflections(vec3 color)
{
	if (u_isReflectionsEnabled && u_isPlanarReflective)
	{
		// Calculation reflection color
		vec3 reflectionMapColor = u_hasReflectionMap ? texture(u_reflectionMap, f_uv).rgb : vec3(0.0f);
		
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
		float fragmentDistance = distance(f_pos.xz, u_shadowAreaCenter.xz);

        // Check if fragment is within shadow area
		if (fragmentDistance <= halfSize)
		{
			// Variables
			vec2 texelSize = (vec2(1.0f) / textureSize(u_shadowMap, 0));
			float shadow = 0.0f;
			vec3 projCoords = (((f_shadowPos.xyz / f_shadowPos.w) * 0.5f) + 0.5f);
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

float calculateSpecularLighting(vec3 position, vec3 normal)
{
    if (u_isSpecularLighted)
    {
    	// Calculate
        vec3 lightDirection   = normalize(position - f_pos);
        vec3 viewDirection    = normalize(u_cameraPosition - f_pos);
        vec3 halfWayDirection = normalize(lightDirection + viewDirection);
        float result          = pow(clamp(dot(normal, halfWayDirection), 0.0f, 1.0f), u_specularLightingFactor);

        // Return
        return (result * u_specularLightingIntensity);
    }
    else
    {
        return 0.0f;
    }
}