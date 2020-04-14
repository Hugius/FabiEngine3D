#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// Const variables
#define POINT_LIGHT_AMOUNT 10

// In variables
in vec3 f_pos;
in vec2 f_uv;
in vec3 f_normal;
in vec4 f_shadowPos;
in vec4 f_clip;

// Textures
layout(location = 0) uniform sampler2D   u_sampler_diffuseMap;
layout(location = 1) uniform sampler2D   u_sampler_lightMap;
layout(location = 2) uniform sampler2D   u_sampler_skyReflectionMap;
layout(location = 3) uniform sampler2D   u_sampler_sceneReflectionMap;
layout(location = 4) uniform sampler2D   u_sampler_shadowMap;
layout(location = 5) uniform samplerCube u_sampler_dayCubeMap;
layout(location = 6) uniform samplerCube u_sampler_nightCubeMap;

// Matrix uniforms
uniform mat4  u_skyRotationMatrix;

// Vector3 uniforms
uniform vec3  u_cameraPos;
uniform vec3  u_dirLightPos;
uniform vec3  u_pointLightsPos[POINT_LIGHT_AMOUNT];
uniform vec3  u_pointLightsColor[POINT_LIGHT_AMOUNT];
uniform vec3  u_color;

// Float uniforms
uniform float u_pointLightsStrength[POINT_LIGHT_AMOUNT];
uniform float u_ambientStrength;
uniform float u_dirLightStrength;
uniform float u_specLightStrength;
uniform float u_fogMinDistance;
uniform float u_skyReflectionMixValue;
uniform float u_customAlpha;
uniform float u_skyReflectionFactor;
uniform float u_sceneReflectionFactor;

// Boolean uniforms
uniform bool u_isTransparent;
uniform bool u_isLightmapped;
uniform bool u_isSkyReflective;
uniform bool u_isSceneReflective;
uniform bool u_isSpecular;
uniform bool u_isShadowed;
uniform bool u_ambientLightingEnabled;
uniform bool u_dirLightingEnabled;
uniform bool u_specLightingEnabled;
uniform bool u_lightMappingEnabled;
uniform bool u_pointLightingEnabled;
uniform bool u_skyReflectionsEnabled;
uniform bool u_sceneReflectionsEnabled;
uniform bool u_fogEnabled;
uniform bool u_shadowsEnabled;
uniform bool u_hasDiffuseMap;

// Integer uniforms
uniform int u_shadowMapSize;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Functions
vec3 getTextureColor();
vec3 getAmbientLighting();
vec3 getDirectionalLighting();
vec3 getSpecularLighting();
vec3 getPointLighting();
vec3 getShadowLighting();
vec3 applyLightmapping(vec3 color);
vec3 applyFog(vec3 color);
vec3 applySkyReflections(vec3 color);
vec3 applySceneReflections(vec3 color);

// Calculate final fragment color
void main()
{
	// Calculate lighting
	vec3 a = getAmbientLighting();
	vec3 d = getDirectionalLighting();
	vec3 s = getSpecularLighting();
	vec3 p = getPointLighting();
	vec3 h = getShadowLighting();

	// Apply lighting
	vec3 color;
	color  = getTextureColor();
	color  = applySkyReflections(color);
	color  = applySceneReflections(color);
	color *= vec3((a + d + s) * h + p);
	color  = applyLightmapping(color);
	color  = applyFog(color);

	// Set final color
	o_finalColor = vec4(color * u_color, u_customAlpha);
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

		// Removing white alpha background
		if(u_isTransparent)
		{
			if(texColor.a <= 0.25f)
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
	if(u_ambientLightingEnabled)
	{
		return vec3(u_ambientStrength);
	}

	return vec3(0.0f);
}

// Calculate directional lighting
vec3 getDirectionalLighting()
{
	if(u_dirLightingEnabled)
	{
		vec3 lightDir = normalize(u_dirLightPos - f_pos);
		float lightStrength = max(dot(f_normal, lightDir), 0.0);
		return vec3(lightStrength * u_dirLightStrength);
	}

	return vec3(0.0f);
}

vec3 getSpecularLighting()
{
	if(u_specLightingEnabled && u_isSpecular)
	{
		vec3 lightDir   = normalize(u_dirLightPos - f_pos);
		vec3 viewDir    = normalize(f_pos - u_cameraPos);
		vec3 reflectDir = reflect(-lightDir, f_normal);
		float specular  = pow(max(dot(viewDir, reflectDir), 0.0f), u_specLightStrength);
		return vec3(specular*10.0f);
	}

	return vec3(0.0f);
}

// Calculate point lighting
vec3 getPointLighting()
{
	if(u_pointLightingEnabled)
	{
		vec3 pointStrength = vec3(0.0f);
		
		for(int i = 0; i < POINT_LIGHT_AMOUNT; i++)
		{
			vec3  lightDir = normalize(u_pointLightsPos[i] - f_pos);
			float diffuse = max(dot(f_normal, lightDir), 0.0);
			float distance = length(u_pointLightsPos[i] - f_pos);
			float attenuation = 1.0f / (1.0f + 0.07f * distance + 0.017f * (distance * distance * distance));
			diffuse *= attenuation * (u_pointLightsStrength[i] * 10.0f);
			pointStrength += (diffuse * u_pointLightsColor[i]);
		}

		return pointStrength;
	}
	
	return vec3(0.0f);
}

vec3 getShadowLighting()
{
	if(u_shadowsEnabled && u_isShadowed)
	{
		// Variables
		float shadow       = 0.0f;
		vec3 projCoords    = (f_shadowPos.xyz / f_shadowPos.w) * 0.5 + 0.5;
		float currentDepth = projCoords.z;
		float texelSize    = 1.0f / float(u_shadowMapSize);

		// Skip fragments outside of the depth map
		if (projCoords.z > 1.0f)
		{	
			return vec3(1.0f);
		}

		// Calculate PCF shadows
		for(int x = -1; x <= 1; ++x)
		{
			for(int y = -1; y <= 1; ++y)
			{
				float pcfDepth = texture(u_sampler_shadowMap, projCoords.xy + vec2(x, y) * vec2(texelSize)).r; 
				shadow += currentDepth - texelSize > pcfDepth ? 0.2f : 1.0f;        
			}    
		}
		
		// Return shadow value
		shadow /= 9.0f;
		return vec3(shadow);
	}

	return vec3(1.0f);
}

vec3 applyLightmapping(vec3 color)
{
	if(u_lightMappingEnabled && u_isLightmapped)
	{
		vec3 lightmapColor = texture(u_sampler_lightMap, f_uv).rgb;
		vec3 lightmappedColor = color + lightmapColor;
		return lightmappedColor;
	}

	return color;
}

// Calculate fog color
vec3 applyFog(vec3 color)
{
	if(u_fogEnabled)
	{
		float  distance    = length(f_pos.xyz - u_cameraPos);
		vec3   foggedColor = mix(vec3(0.75f, 0.75f, 0.75f), color, min(u_fogMinDistance / distance, 1.0f));
		return foggedColor;
	}
	
	return color;
}

vec3 applySkyReflections(vec3 color)
{
	if(u_skyReflectionsEnabled && u_isSkyReflective)
	{
		vec4 reflMapColor = texture(u_sampler_skyReflectionMap, f_uv);
		
		if(reflMapColor.rgb != vec3(0.0f))
		{
			vec3 viewDir      = normalize(f_pos - u_cameraPos);
			vec3 reflectDir   = reflect(viewDir, f_normal);
			vec4 dayColor     = vec4(texture(u_sampler_dayCubeMap, vec3(u_skyRotationMatrix * vec4(reflectDir, 1.0f))).rgb, 1.0);
			vec4 nightColor   = vec4(texture(u_sampler_nightCubeMap, vec3(u_skyRotationMatrix * vec4(reflectDir, 1.0f))).rgb, 1.0);
			vec4 reflectColor = mix(dayColor, nightColor, u_skyReflectionMixValue);
			vec3 mixedColor   = mix(color.rgb, reflectColor.rgb, u_skyReflectionFactor);
			return mixedColor.rgb;
		}

		return color;
	}

	return color;
}

vec3 applySceneReflections(vec3 color)
{
	if(u_sceneReflectionsEnabled && u_isSceneReflective)
	{
		vec2 ndc = (f_clip.xy / f_clip.w) / 2.0 + 0.5;
		vec2 texCoords = vec2(ndc.x, -ndc.y);
		vec4 reflectionColor = texture(u_sampler_sceneReflectionMap, vec2(texCoords.x,  texCoords.y));
		vec3 mixedColor   = mix(color.rgb, reflectionColor.rgb, u_sceneReflectionFactor);
		return mixedColor.rgb;
	}

	return color;
}
