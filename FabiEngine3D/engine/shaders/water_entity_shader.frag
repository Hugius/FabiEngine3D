#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

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
uniform vec3 u_ambientLightPosition;
uniform vec3 u_cameraPosition;
uniform vec3 u_color;
uniform vec3 u_fogColor;

// Vector2 uniforms
uniform vec2 u_rippleOffset;

// Float uniforms
uniform float u_specularLightFactor;
uniform float u_specularLightIntensity;
uniform float u_nearZ;
uniform float u_farZ;
uniform float u_transparency;
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogDefaultFactor;

// Boolean uniforms
uniform bool u_fogEnabled;
uniform bool u_effectsEnabled;
uniform bool u_isRippling;
uniform bool u_isSpecularLighted;
uniform bool u_isReflective;
uniform bool u_isRefractive;

// Out variables
layout(location = 0) out vec4 o_finalColor;

// Functions
vec4 getMainColor();
vec3 applyFog(vec3 color);
float convertDepthToLinear(float depth);

// Calculate final fragment color
void main()
{    
	if(u_effectsEnabled)
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
	float specular = 0.0f;

	// Projective texture mapping
	vec2 ndc = (f_clip.xy / f_clip.w) / 2.0 + 0.5;
	vec2 texCoords = vec2(ndc.x, -ndc.y);

	// Depth map
	float depth = texture(u_sampler_depthMap, vec2(texCoords.x, -texCoords.y)).r;
	float floorDistance = convertDepthToLinear(depth);
	float waterDistance = convertDepthToLinear(gl_FragCoord.z);
	float waterDepth = floorDistance - waterDistance;
	waterDepth = clamp(waterDepth / (u_transparency * 10.0f), 0.0f, 1.0f);

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
	if(u_isSpecularLighted)
	{
		vec3 lightDir     = normalize(u_ambientLightPosition - f_pos);
		vec3 viewDir      = normalize(f_pos - u_cameraPosition);
		vec3 reflectDir   = reflect(normalize(lightDir), normal);
		specular = pow(max(dot(reflectDir, viewDir), 0.0f), u_specularLightFactor) * u_specularLightIntensity;
	}

	// Fresnel effect
	vec3 viewDir = normalize(u_cameraPosition - f_pos);
	float mixFactor = dot(viewDir, normal);

	// Finalizing fragment color
	vec3 finalColor;
	vec3 reflectionColor = texture(u_sampler_reflectionMap, vec2(texCoords.x,  texCoords.y)).rgb; // Reflection color
	vec3 refractionColor = texture(u_sampler_refractionMap, vec2(texCoords.x, -texCoords.y)).rgb; // Refraction color

	// Determine which textures to mix
	if(u_isReflective && u_isRefractive) // Both
	{
		finalColor = mix(reflectionColor, refractionColor, mixFactor); // Combining reflection & refraction
		finalColor = mix(finalColor, u_color, 0.1f); // Water color tint
	}
	else if(u_isReflective) // Only reflection
	{
		finalColor = reflectionColor;
		finalColor = mix(finalColor, u_color, 0.1f); // Water color tint
	}
	else if(u_isRefractive) // Only refraction
	{
		finalColor = refractionColor;
		finalColor = mix(finalColor, u_color, 0.1f); // Water color tint
	}
	else // None
	{
		finalColor = u_color;
	}

	// Specular highlights
	if(u_isSpecularLighted)
	{
		finalColor += vec3(specular);
	}

	// Return final color
	return vec4(finalColor, waterDepth);
}

// Calculate fog color
vec3 applyFog(vec3 color)
{
	if(u_fogEnabled)
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
	
	return color;
}

float convertDepthToLinear(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * u_nearZ * u_farZ) / (u_farZ + u_nearZ - z * (u_farZ - u_nearZ));
}