#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// Constant variables
#define MAX_LIGHT_COUNT 128
#define FRAME_COLOR vec3(1.0f, 1.0f, 1.0f)

// In variables
in vec3 f_position;
in vec2 f_uv;
in vec4 f_clip;

// Textures
layout (location = 0) uniform sampler2D u_reflectionMap;
layout (location = 1) uniform sampler2D u_refractionMap;
layout (location = 2) uniform sampler2D u_depthMap;
layout (location = 3) uniform sampler2D u_dudvMap;
layout (location = 4) uniform sampler2D u_normalMap;

// Vector uniforms
uniform vec3 u_pointlightPositions[MAX_LIGHT_COUNT];
uniform vec3 u_pointlightRadiuses[MAX_LIGHT_COUNT];
uniform vec3 u_pointlightColors[MAX_LIGHT_COUNT];
uniform vec3 u_directionalLightingColor;
uniform vec3 u_directionalLightPosition;
uniform vec3 u_cameraPosition;
uniform vec3 u_color;
uniform vec3 u_fogColor;

// Vector2 uniforms
uniform vec2 u_rippleOffset;

// Float uniforms
uniform float u_pointlightIntensities[MAX_LIGHT_COUNT];
uniform float u_directionalLightingIntensity;
uniform float u_specularShininess;
uniform float u_specularIntensity;
uniform float u_nearDistance;
uniform float u_farDistance;
uniform float u_transparency;
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogThickness;

// Integer uniforms
uniform int u_pointlightShapes[MAX_LIGHT_COUNT];
uniform int u_lightCount;

// Boolean uniforms
uniform bool u_isWireFramed;
uniform bool u_isDirectionalLightingEnabled;
uniform bool u_isFogEnabled;
uniform bool u_isSpecular;
uniform bool u_isReflective;
uniform bool u_isRefractive;
uniform bool u_isUnderWater;
uniform bool u_hasDudvMap;
uniform bool u_hasNormalMap;

// Out variables
layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

// Functions
vec4 calculateWaterColor();
vec3 calculateDirectionalLighting(vec3 normal);
vec3 calculateLights(vec3 normal);
vec3 calculateFog(vec3 color);
float calculateSpecularLighting(vec3 position, vec3 normal);
float convertDepthToPerspective(float depth);

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

	// Main water color
	vec4 waterColor = calculateWaterColor();

	// Calculate base color
	vec3 primaryColor = waterColor.rgb;
	primaryColor = calculateFog(primaryColor);
	primaryColor = clamp(primaryColor, vec3(0.0f), vec3(1.0f));

	// Apply gamma correction
	primaryColor = pow(primaryColor, vec3(1.0f / 2.2f));

	// Set final colors
	o_primaryColor   = vec4(primaryColor, waterColor.a);
	o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

vec4 calculateWaterColor()
{
	// Variables to be used
	vec2 mapUV = f_uv;
	vec3 normal = vec3(0.0f, 1.0f, 0.0f);
	vec3 directionalLighting = vec3(0.0f);

	// Projective texture mapping
	vec2 ndc = (f_clip.xy / f_clip.w);
	ndc /= 2.0f;
	ndc += 0.5f;
	vec2 reflectionUV = vec2(ndc.x, -ndc.y);
	vec2 refractionUV = vec2(ndc.x, ndc.y);

	// Depth map
	float alpha = 1.0f;
	if (u_transparency > 0.0f)
	{
		float depth = texture(u_depthMap, refractionUV).r;
		float floorDistance = convertDepthToPerspective(depth);
		float waterDistance = convertDepthToPerspective(gl_FragCoord.z);
		float waterDepth = floorDistance - waterDistance;
		alpha = clamp(waterDepth / (u_transparency * 10.0f), 0.0f, 1.0f);
	}

	// DUDV mapping
	if (u_hasDudvMap)
	{
		// Distort map UV coordinates
		vec2 distortedMapUV = texture(u_dudvMap, (mapUV + u_rippleOffset)).rg;
		distortedMapUV *= 0.1f;
		mapUV += distortedMapUV;

		// Distort NDC UV coordinates
		vec2 distortedNdcUV = texture(u_dudvMap, mapUV).rg;
		distortedNdcUV *= 2.0f;
		distortedNdcUV -= 1.0f;
		distortedNdcUV *= 0.025f;

		// Add to refraction UV coordinates
		reflectionUV += distortedNdcUV;

		// Add to reflection UV coordinates
		refractionUV += distortedNdcUV;

		// Limit reflection UV coordinates
		reflectionUV.x = clamp(reflectionUV.x, 0.001f, 0.999f);
		reflectionUV.y = clamp(reflectionUV.y, -0.999f, -0.001f);

		// Limit refraction UV coordinates
		refractionUV.x = clamp(refractionUV.x, 0.001f, 0.999f);
		refractionUV.y = clamp(refractionUV.y, 0.001f, 0.999f);
	}

	// Normal mapping
	if (u_hasNormalMap)
	{
		vec3 normalMapColor = texture(u_normalMap, mapUV).rgb;
		normal = vec3(((normalMapColor.r * 2.0f) - 1.0f), normalMapColor.b, ((normalMapColor.g * 2.0f) - 1.0f));
		normal = normalize(normal);
	}

	// Fresnel effect
	vec3 viewDirection = normalize(u_cameraPosition - f_position);
	float fresnelMixValue = dot(viewDirection, normal);

	// Finalizing fragment color
	vec3 finalColor;
	vec3 reflectionColor = texture(u_reflectionMap, reflectionUV).rgb;
	vec3 refractionColor = texture(u_refractionMap, refractionUV).rgb;

	// Calculate final color
	if (u_isReflective && u_isRefractive && !u_isUnderWater) // Refraction & reflection
	{
		finalColor = mix(reflectionColor, refractionColor, fresnelMixValue); // Refraction fresnel effect
		finalColor *= u_color;
	}
	else if (u_isRefractive) // Only refraction
	{
		finalColor = refractionColor; // No fresnel effect
		finalColor *= u_color;
	}
	else if (u_isReflective) // Only reflection
	{
		finalColor = mix(reflectionColor, (reflectionColor * 0.1f), fresnelMixValue); // Dark fresnel effect
		finalColor *= u_color;
	}
	else // Only color
	{
		finalColor = u_color;
	}

	// Specular lighting
	if (u_isSpecular)
	{
		finalColor += calculateDirectionalLighting(normal);
		finalColor += calculateLights(normal);
	}

	// Return final color
	return vec4(finalColor, alpha);
}

vec3 calculateLights(vec3 normal)
{
		vec3 result = vec3(0.0f);
		
    // For every light
	for (int i = 0; i < u_lightCount; i++)
	{
        // Calculate light strength
		vec3 lightDirection = normalize(u_pointlightPositions[i] - f_position);
		float diffuse = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
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

vec3 calculateDirectionalLighting(vec3 normal)
{
	if (u_isDirectionalLightingEnabled)
	{
		vec3 lightDirection = normalize(u_directionalLightPosition - f_position); // Light ray
		vec3 viewDirection = normalize(f_position - u_cameraPosition); // View ray
		vec3 reflectDirection = reflect(normalize(lightDirection), normal); // Reflect ray
		float specular = pow(clamp(dot(reflectDirection, viewDirection), 0.0f, 1.0f), u_specularShininess); // Calculate if perpendicular
		specular *= u_directionalLightingIntensity; // Directional intensity
		specular *= u_specularIntensity; // Specular intensity
		vec3 result = vec3(specular); // Add to lighting
		result *= u_directionalLightingColor; // Directional color
		return result; // Return
	}
	else
	{
		return vec3(0.0f);
	}
}

float calculateSpecularLighting(vec3 position, vec3 normal)
{
    if (u_isSpecular)
    {
    	// Calculate
        vec3 lightDirection   = normalize(position - f_position);
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

vec3 calculateFog(vec3 color)
{
	if (u_isFogEnabled)
	{
		// Calculate distance to fragment in world space
		float fragmentDistance = distance(f_position.xyz, u_cameraPosition);

        // Calculate fog intensity
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

float convertDepthToPerspective(float depth)
{
    float z = ((depth * 2.0f) - 1.0f);
    return ((2.0f * u_nearDistance * u_farDistance) / (u_farDistance + u_nearDistance - z * (u_farDistance - u_nearDistance)));
}