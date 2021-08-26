#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// Const variables
#define MAX_LIGHT_AMOUNT 128

// In variables
in vec3 f_pos;
in vec2 f_uv;
in vec4 f_clip;

// Textures
layout (location = 0) uniform sampler2D u_reflectionMap;
layout (location = 1) uniform sampler2D u_refractionMap;
layout (location = 2) uniform sampler2D u_depthMap;
layout (location = 3) uniform sampler2D u_dudvMap;
layout (location = 4) uniform sampler2D u_normalMap;

// Vector uniforms
uniform vec3 u_lightPositions[MAX_LIGHT_AMOUNT];
uniform vec3 u_lightRadiuses[MAX_LIGHT_AMOUNT];
uniform vec3 u_lightColors[MAX_LIGHT_AMOUNT];
uniform vec3 u_directionalLightColor;
uniform vec3 u_directionalLightPosition;
uniform vec3 u_cameraPosition;
uniform vec3 u_color;
uniform vec3 u_fogColor;

// Vector2 uniforms
uniform vec2 u_rippleOffset;

// Float uniforms
uniform float u_lightIntensities[MAX_LIGHT_AMOUNT];
uniform float u_directionalLightingIntensity;
uniform float u_specularLightingFactor;
uniform float u_specularLightingIntensity;
uniform float u_nearZ;
uniform float u_farZ;
uniform float u_transparency;
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogThickness;

// Integer uniforms
uniform int u_lightCount;

// Boolean uniforms
uniform bool u_isWireFramed;
uniform bool u_isDirectionalLightingEnabled;
uniform bool u_isFogEnabled;
uniform bool u_isRippling;
uniform bool u_isSpecularLighted;
uniform bool u_isReflective;
uniform bool u_isRefractive;
uniform bool u_isUnderWater;

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
		o_primaryColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
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
	vec3 normal = vec3(0.0f, 1.0f, 0.0f);
	vec3 directionalLighting = vec3(0.0f);

	// Projective texture mapping
	vec2 ndc = (f_clip.xy / f_clip.w) / 2.0 + 0.5;
	vec2 texCoords = vec2(ndc.x, -ndc.y);

	// Depth map
	float alpha = 1.0f;
	if (u_transparency > 0.0f)
	{
		float depth = texture(u_depthMap, vec2(texCoords.x, -texCoords.y)).r;
		float floorDistance = convertDepthToPerspective(depth);
		float waterDistance = convertDepthToPerspective(gl_FragCoord.z);
		float waterDepth = floorDistance - waterDistance;
		alpha = clamp(waterDepth / (u_transparency * 10.0f), 0.0f, 1.0f);
	}

	// Rippling effect
	if (u_isRippling)
	{
		// DUDV mapping
		vec2 distortedTexCoords = f_uv + texture(u_dudvMap, vec2(f_uv.x + u_rippleOffset.x, f_uv.y + u_rippleOffset.y)).rg * 0.1;
		vec2 totalDistortion = (texture(u_dudvMap, distortedTexCoords).rg * 2.0 - 1.0f) * 0.025f;
		texCoords  += totalDistortion;
		texCoords.x = clamp(texCoords.x, 0.001f, 0.999f);
		texCoords.y = clamp(texCoords.y, -0.999f, -0.001f);

		// Normal mapping
		vec3 normalMapColor = texture(u_normalMap, distortedTexCoords).rgb;
		normal              = vec3((normalMapColor.r * 2.0f) - 1.0f, normalMapColor.b, (normalMapColor.g * 2.0f) - 1.0f);
		normal              = normalize(normal);
	}

	// Fresnel effect
	vec3 viewDirection = normalize(u_cameraPosition - f_pos);
	float mixFactor = dot(viewDirection, normal);

	// Finalizing fragment color
	vec3 finalColor;
	vec3 reflectionColor = texture(u_reflectionMap, vec2(texCoords.x,  texCoords.y)).rgb; // Reflection color
	vec3 refractionColor = texture(u_refractionMap, vec2(texCoords.x, -texCoords.y)).rgb; // Refraction color

	// Bloom correction
	reflectionColor *= 1.0f;
	refractionColor *= 1.0f;

	// Determine which textures to mix
	if (u_isReflective && u_isRefractive && !u_isUnderWater) // Both
	{
		finalColor = mix(reflectionColor, refractionColor, mixFactor); // Combining reflection & refraction
		finalColor = mix(finalColor, u_color, 0.1f); // Water color tint
	}
	else if (u_isRefractive) // Only refraction
	{
		finalColor = refractionColor;
		finalColor = mix(finalColor, u_color, 0.1f); // Water color tint
	}
	else if (u_isReflective) // Only reflection
	{
		finalColor = mix(reflectionColor, vec3(0.0f), mixFactor);
		finalColor = mix(finalColor, u_color, 0.1f); // Water color tint
	}
	else // None
	{
		finalColor = u_color;
	}

	// Specular lighting
	if (u_isSpecularLighted)
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
		vec3 lightDirection = normalize(u_lightPositions[i] - f_pos);
		float diffuse = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(u_lightPositions[i], normal);

		// Calculate light attenuation
		vec3 fragmentDistance = abs(u_lightPositions[i] - f_pos);
		float attenuation = max(0.0f, 1.0f - (fragmentDistance.x / u_lightRadiuses[i].x));
		attenuation = min(attenuation, max(0.0f, 1.0f - (fragmentDistance.y / u_lightRadiuses[i].y)));
		attenuation = min(attenuation, max(0.0f, 1.0f - (fragmentDistance.z / u_lightRadiuses[i].z)));

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

vec3 calculateDirectionalLighting(vec3 normal)
{
	if (u_isDirectionalLightingEnabled)
	{
		vec3 lightDirection = normalize(u_directionalLightPosition - f_pos); // Light ray
		vec3 viewDirection = normalize(f_pos - u_cameraPosition); // View ray
		vec3 reflectDirection = reflect(normalize(lightDirection), normal); // Reflect ray
		float specular = pow(clamp(dot(reflectDirection, viewDirection), 0.0f, 1.0f), u_specularLightingFactor); // Calculate if perpendicular
		specular *= u_directionalLightingIntensity; // Directional intensity
		specular *= u_specularLightingIntensity; // Specular intensity
		vec3 result = vec3(specular); // Add to lighting
		result *= u_directionalLightColor; // Directional color
		return result; // Return
	}
	else
	{
		return vec3(0.0f);
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

vec3 calculateFog(vec3 color)
{
	if (u_isFogEnabled)
	{
		// Calculate distance to fragment in world space
		float fragmentDistance = distance(f_pos.xyz, u_cameraPosition);

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
    return (2.0f * u_nearZ * u_farZ) / (u_farZ + u_nearZ - z * (u_farZ - u_nearZ));
}