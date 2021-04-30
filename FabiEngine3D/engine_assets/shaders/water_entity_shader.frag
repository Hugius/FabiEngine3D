#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// Const variables
#define MAX_POINT_LIGHT_COUNT 128

// In variables
in vec3 f_pos;
in vec2 f_uv;
in vec4 f_clip;

// Textures
layout(location = 0) uniform sampler2D u_sampler_reflectionMap;
layout(location = 1) uniform sampler2D u_sampler_refractionMap;
layout(location = 2) uniform sampler2D u_sampler_depthMap;
layout(location = 3) uniform sampler2D u_sampler_dudvMap;
layout(location = 4) uniform sampler2D u_sampler_normalMap;

// Vector3 uniforms
uniform vec3 u_directionalLightColor;
uniform vec3 u_directionalLightPosition;
uniform vec3 u_cameraPosition;
uniform vec3 u_color;
uniform vec3 u_fogColor;
uniform vec3 u_pointLightPositions[MAX_POINT_LIGHT_COUNT];
uniform vec3 u_pointLightColors[MAX_POINT_LIGHT_COUNT];

// Vector2 uniforms
uniform vec2 u_rippleOffset;

// Float uniforms
uniform float u_directionalLightIntensity;
uniform float u_specularLightFactor;
uniform float u_specularLightIntensity;
uniform float u_nearZ;
uniform float u_farZ;
uniform float u_transparency;
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogThickness;
uniform float u_pointLightIntensities[MAX_POINT_LIGHT_COUNT];
uniform float u_pointLightDistanceFactors[MAX_POINT_LIGHT_COUNT];

// Integer uniforms
uniform int u_pointLightCount;

// Boolean uniforms
uniform bool u_isDirectionalLightEnabled;
uniform bool u_isFogEnabled;
uniform bool u_isEffectsEnabled;
uniform bool u_isRippling;
uniform bool u_isSpecularLighted;
uniform bool u_isReflective;
uniform bool u_isRefractive;
uniform bool u_isUnderWater;
uniform bool u_isPointLightEnabled;
uniform bool u_isSpecularLightEnabled;

// Out variables
layout(location = 0) out vec4 o_finalColor;

// Functions
vec4 getMainColor();
vec3 getPointLighting(vec3 normal);
float getSpecularValue(vec3 position, vec3 normal);
vec3 applyFog(vec3 color);
float convertDepthToLinear(float depth);

// Calculate final fragment color
void main()
{    
	if(u_isEffectsEnabled)
	{
		o_finalColor = getMainColor();
		o_finalColor.rgb = applyFog(o_finalColor.rgb);
	}
	else
	{
		o_finalColor = vec4(u_color, 0.5f);
	}
}

vec4 getMainColor()
{
	// Variables to be used
	vec3 normal = vec3(0.0f, 1.0f, 0.0f);
	vec3 directionalLighting = vec3(0.0f);

	// Projective texture mapping
	vec2 ndc = (f_clip.xy / f_clip.w) / 2.0 + 0.5;
	vec2 texCoords = vec2(ndc.x, -ndc.y);

	// Depth map
	float alpha = 1.0f;
	if(u_transparency > 0.0f)
	{
		float depth = texture(u_sampler_depthMap, vec2(texCoords.x, -texCoords.y)).r;
		float floorDistance = convertDepthToLinear(depth);
		float waterDistance = convertDepthToLinear(gl_FragCoord.z);
		float waterDepth = floorDistance - waterDistance;
		alpha = clamp(waterDepth / (u_transparency * 10.0f), 0.0f, 1.0f);
	}

	// Rippling effect
	if(u_isRippling)
	{
		// DUDV mapping
		vec2 distortedTexCoords = f_uv + texture(u_sampler_dudvMap, vec2(f_uv.x + u_rippleOffset.x, f_uv.y + u_rippleOffset.y)).rg * 0.1;
		vec2 totalDistortion = (texture(u_sampler_dudvMap, distortedTexCoords).rg * 2.0 - 1.0f) * 0.025f;
		texCoords  += totalDistortion;
		texCoords.x = clamp(texCoords.x, 0.001f, 0.999f);
		texCoords.y = clamp(texCoords.y, -0.999f, -0.001f);

		// Normal mapping
		vec3 normalMapColor = texture(u_sampler_normalMap, distortedTexCoords).rgb;
		normal              = vec3((normalMapColor.r * 2.0f) - 1.0f, normalMapColor.b, (normalMapColor.g * 2.0f) - 1.0f);
		normal              = normalize(normal);
	}

	// Specular lighting
	if(u_isDirectionalLightEnabled && u_isSpecularLightEnabled && u_isSpecularLighted)
	{
		vec3 lightDir     = normalize(u_directionalLightPosition - f_pos); // Light ray
		vec3 viewDir      = normalize(f_pos - u_cameraPosition); // View ray
		vec3 reflectDir   = reflect(normalize(lightDir), normal); // Reflect ray
		float specular = pow(max(dot(reflectDir, viewDir), 0.0f), u_specularLightFactor); // Calculate if perpendicular
		specular *= u_directionalLightIntensity; // Directional intensity
		specular *= u_specularLightIntensity; // Specular intensity
		directionalLighting = vec3(specular); // Add to lighting
		directionalLighting *= u_directionalLightColor; // Directional color
	}

	// Fresnel effect
	vec3 viewDir = normalize(u_cameraPosition - f_pos);
	float mixFactor = dot(viewDir, normal);

	// Finalizing fragment color
	vec3 finalColor;
	vec3 reflectionColor = texture(u_sampler_reflectionMap, vec2(texCoords.x,  texCoords.y)).rgb; // Reflection color
	vec3 refractionColor = texture(u_sampler_refractionMap, vec2(texCoords.x, -texCoords.y)).rgb; // Refraction color

	// Bloom correction
	reflectionColor *= 1.5f;
	refractionColor *= 1.5f;

	// Determine which textures to mix
	if(u_isReflective && u_isRefractive && !u_isUnderWater) // Both
	{
		finalColor = mix(reflectionColor, refractionColor, mixFactor); // Combining reflection & refraction
		finalColor = mix(finalColor, u_color, 0.1f); // Water color tint
	}
	else if(u_isRefractive) // Only refraction
	{
		finalColor = refractionColor;
		finalColor = mix(finalColor, u_color, 0.1f); // Water color tint
	}
	else if(u_isReflective) // Only reflection
	{
		finalColor = mix(reflectionColor, vec3(0.0f), mixFactor);
		finalColor = mix(finalColor, u_color, 0.1f); // Water color tint
	}
	else // None
	{
		finalColor = u_color;
	}

	// Specular highlights
	if(u_isSpecularLightEnabled && u_isSpecularLighted)
	{
		finalColor += directionalLighting;
		finalColor += getPointLighting(normal);
	}

	// Return final color
	return vec4(finalColor, alpha);
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
            // Calculate lighting distance
			float distance = length(u_pointLightPositions[i] - f_pos) * u_pointLightDistanceFactors[i];
			float attenuation = 1.0f / (1.0f + 0.07f * distance + 0.017f * (distance * distance));

            // Apply
            vec3 current = vec3(0.0f);
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
	
	return color;
}

// Convert the depth to a linear value
float convertDepthToLinear(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * u_nearZ * u_farZ) / (u_farZ + u_nearZ - z * (u_farZ - u_nearZ));
}