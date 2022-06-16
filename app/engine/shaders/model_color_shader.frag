#version 460 core

#define MAX_POINTLIGHT_COUNT 64
#define MAX_SPOTLIGHT_COUNT 64
#define SPOTLIGHT_SMOOTHING_MULTIPLIER 0.95f
#define GAMMA_VALUE 2.2f
#define CUBE_REFRACTION_RATIO 0.75f

in vec4 f_shadowSpacePos;
in vec3 f_worldSpacePos;
in vec4 f_clipSpacePos;
in vec2 f_uv;
in vec3 f_normal;
in mat3 f_tbn;

layout (location = 0) uniform samplerCube u_previousReflectionCubeMap;
layout (location = 1) uniform samplerCube u_previousRefractionCubeMap;
layout (location = 2) uniform samplerCube u_currentReflectionCubeMap;
layout (location = 3) uniform samplerCube u_currentRefractionCubeMap;
layout (location = 4) uniform sampler2D u_planarReflectionMap;
layout (location = 5) uniform sampler2D u_planarRefractionMap;
layout (location = 6) uniform sampler2D u_shadowMap;
layout (location = 7) uniform sampler2D u_diffuseMap;
layout (location = 8) uniform sampler2D u_emissionMap;
layout (location = 9) uniform sampler2D u_specularMap;
layout (location = 10) uniform sampler2D u_reflectionMap;
layout (location = 11) uniform sampler2D u_refractionMap;
layout (location = 12) uniform sampler2D u_normalMap;

uniform vec3 u_wireframeColor;
uniform vec3 u_pointlightPositions[MAX_POINTLIGHT_COUNT];
uniform vec3 u_pointlightRadiuses[MAX_POINTLIGHT_COUNT];
uniform vec3 u_pointlightColors[MAX_POINTLIGHT_COUNT];
uniform vec3 u_spotlightPositions[MAX_SPOTLIGHT_COUNT];
uniform vec3 u_spotlightFronts[MAX_SPOTLIGHT_COUNT];
uniform vec3 u_spotlightColors[MAX_SPOTLIGHT_COUNT];
uniform vec3 u_cameraPosition;
uniform vec3 u_ambientLightingColor;
uniform vec3 u_directionalLightingColor;
uniform vec3 u_directionalLightingPosition;
uniform vec3 u_color;
uniform vec3 u_fogColor;
uniform vec3 u_shadowLookat;

uniform float u_pointlightIntensities[MAX_POINTLIGHT_COUNT];
uniform float u_spotlightIntensities[MAX_SPOTLIGHT_COUNT];
uniform float u_spotlightAngles[MAX_SPOTLIGHT_COUNT];
uniform float u_spotlightDistances[MAX_SPOTLIGHT_COUNT];
uniform float u_ambientLightingIntensity;
uniform float u_directionalLightingIntensity;
uniform float u_specularShininess;
uniform float u_specularIntensity;
uniform float u_opacity;
uniform float u_minAlpha;
uniform float u_shadowSize;
uniform float u_minFogDistance;
uniform float u_maxFogDistance;
uniform float u_fogThickness;
uniform float u_reflectivity;
uniform float u_refractivity;
uniform float u_lightness;
uniform float u_shadowLightness;
uniform float u_shadowBias;
uniform float u_cubeReflectionMixValue;
uniform float u_cubeRefractionMixValue;
uniform float u_emissionIntensity;

uniform int u_pointlightShapes[MAX_POINTLIGHT_COUNT];
uniform int u_pointlightCount;
uniform int u_spotlightCount;
uniform int u_reflectionType;
uniform int u_refractionType;
uniform int u_shadowPcfCount;

uniform bool u_isWireframed;
uniform bool u_isReflective;
uniform bool u_isRefractive;
uniform bool u_isSpecular;
uniform bool u_isShadowCircleEnabled;
uniform bool u_isAmbientLightingEnabled;
uniform bool u_isDirectionalLightingEnabled;
uniform bool u_isReflectionsEnabled;
uniform bool u_isRefractionsEnabled;
uniform bool u_isFogEnabled;
uniform bool u_isShadowsEnabled;
uniform bool u_hasDiffuseMap;
uniform bool u_hasEmissionMap;
uniform bool u_hasSpecularMap;
uniform bool u_hasReflectionMap;
uniform bool u_hasRefractionMap;
uniform bool u_hasNormalMap;
uniform bool u_isBright;

layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

float calculateSpecularLighting(vec3 specularMapColor, vec3 lightDirection, vec3 normal)
{
    if(u_isSpecular)
    {
		float result = 0.0f;
        vec3 viewDirection = normalize(u_cameraPosition - f_worldSpacePos);
        vec3 halfWayDirection = normalize(lightDirection + viewDirection);

		float specularMapIntensity = ((specularMapColor.r + specularMapColor.g + specularMapColor.b) / 3.0f);
        float specular = pow(clamp(dot(normal, halfWayDirection), 0.0f, 1.0f), u_specularShininess);

		result += specular;
		result *= u_specularIntensity;
		result *= specularMapIntensity;

        return result;
    }
    else
    {
        return 0.0f;
    }
}

vec3 calculateDiffuseMapping()
{
	if(u_hasDiffuseMap)
	{
		vec4 diffuseMapColor = texture(u_diffuseMap, f_uv);
		
		diffuseMapColor.rgb = pow(diffuseMapColor.rgb, vec3(GAMMA_VALUE));

		if(diffuseMapColor.a < u_minAlpha)
		{
			discard;
		}

		return diffuseMapColor.rgb;
	}
	else
	{
		return vec3(1.0f);
	}
}

vec3 calculateEmissionMapping()
{
	if(u_hasEmissionMap)
	{
		vec4 emissionMapColor = texture(u_emissionMap, f_uv);

		if(emissionMapColor.a < u_minAlpha)
		{
			return vec3(0.0f);
		}

		return (emissionMapColor.rgb * u_emissionIntensity);
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 calculateSpecularMapping()
{
    if(u_hasSpecularMap)
    {
		vec4 specularMapColor = texture(u_specularMap, f_uv);

		if(specularMapColor.a < u_minAlpha)
		{
			return vec3(0.0f);
		}

		return specularMapColor.rgb;
	}
	else
	{
		return vec3(1.0f);
	}
}

vec3 calculateReflectionMapping()
{
    if(u_hasReflectionMap)
    {
		vec4 reflectionMapColor = texture(u_reflectionMap, f_uv);

		if(reflectionMapColor.a < u_minAlpha)
		{
			return vec3(0.0f);
		}

		return reflectionMapColor.rgb;
	}
	else
	{
		return vec3(1.0f);
	}
}

vec3 calculateRefractionMapping()
{
    if(u_hasRefractionMap)
    {
		vec4 refractionMapColor = texture(u_refractionMap, f_uv);

		if(refractionMapColor.a < u_minAlpha)
		{
			return vec3(0.0f);
		}

		return refractionMapColor.rgb;
	}
	else
	{
		return vec3(1.0f);
	}
}

vec3 calculateNormalMapping()
{
    if(u_hasNormalMap)
    {
        vec3 normalMapColor = texture(u_normalMap, f_uv).rgb;
        vec3 normal = normalize(f_tbn * ((normalMapColor * 2.0f) - 1.0f));

        return normal;
    }
    else
    {
        return f_normal;
    }
}

float calculateShadows()
{
	if(u_isShadowsEnabled)
	{
		float halfSize = (u_shadowSize * 0.5f);
		float fragmentDistance = distance(f_worldSpacePos.xz, u_shadowLookat.xz);

		if(fragmentDistance <= halfSize)
		{
			vec3 uvCoords = (((f_shadowSpacePos.xyz / f_shadowSpacePos.w) * 0.5f) + 0.5f);
			vec2 texelSize = (vec2(1.0f) / textureSize(u_shadowMap, 0));

			float shadow = 0.0f;

			if(uvCoords.z > 1.0f)
			{
				return 1.0f;
			}

			for (int x = -u_shadowPcfCount; x <= u_shadowPcfCount; x++)
			{
				for (int y = -u_shadowPcfCount; y <= u_shadowPcfCount; y++)
				{
					vec2 uvOffset = (vec2(x, y) * texelSize);

					float depth = texture(u_shadowMap, (uvCoords.xy + uvOffset)).r;
					float lightness = (((uvCoords.z - u_shadowBias) > depth) ? u_shadowLightness : 1.0f);

					shadow += lightness;         
				}    
			}
            
			int fullPcfCount = ((u_shadowPcfCount * 2) + 1);

			shadow /= float(fullPcfCount * fullPcfCount);
			
			if(shadow > 1.0f)
			{
				shadow = 1.0f;
			}

			float opacity = (fragmentDistance - (halfSize * 0.9f));

			opacity = clamp(opacity, 0.0f, (halfSize * 0.1f));
			opacity /= (halfSize * 0.1f);
			opacity = (1.0f - opacity);

			if(u_isShadowCircleEnabled)
			{
				if((fragmentDistance - (halfSize * 0.99f)) > 0.0f)
				{
					return 0.0f;
				}
			}

			return mix(1.0f, shadow, opacity);
		}

		return 1.0f;
	}
	else
	{
		return 1.0f;
	}
}

vec3 calculateAmbientLighting(float shadowLighting)
{
	if(u_isAmbientLightingEnabled)
	{
		vec3 result = vec3(0.0f);

		result += u_ambientLightingColor;
		result *= u_ambientLightingIntensity;
		result *= shadowLighting;

		return result;
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 calculateDirectionalLighting(vec3 specularMapColor, vec3 normal, float shadowLighting)
{
	if(u_isDirectionalLightingEnabled)
	{
        vec3 result = vec3(0.0f);
		vec3 lightDirection = normalize(u_directionalLightingPosition - f_worldSpacePos);

		float diffuse = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(specularMapColor, lightDirection, normal);

        result += vec3(diffuse * shadowLighting);
        result += vec3(specular * (shadowLighting * shadowLighting));
        result *= u_directionalLightingColor;
        result *= u_directionalLightingIntensity;

        return result;
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 calculatePointLighting(vec3 specularMapColor, vec3 normal)
{
	vec3 result = vec3(0.0f);

	for (int index = 0; index < u_pointlightCount; index++)
	{
		vec3 current = vec3(0.0f);
		vec3 lightDirection = normalize(u_pointlightPositions[index] - f_worldSpacePos);

		float diffuse = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(specularMapColor, lightDirection, normal);
		float attenuation;

		if(u_pointlightShapes[index] == 0)
		{
			float fragmentDistance = distance(u_pointlightPositions[index], f_worldSpacePos);
			float averageRadius = ((u_pointlightRadiuses[index].x + u_pointlightRadiuses[index].y + u_pointlightRadiuses[index].z) / 3.0f);

			attenuation = max(0.0f, (1.0f - (fragmentDistance / averageRadius)));
		}
		else
		{
			vec3 fragmentDistance = abs(u_pointlightPositions[index] - f_worldSpacePos);

			float xAttenuation = max(0.0f, (1.0f - (fragmentDistance.x / u_pointlightRadiuses[index].x)));
			float yAttenuation = max(0.0f, (1.0f - (fragmentDistance.y / u_pointlightRadiuses[index].y)));
			float zAttenuation = max(0.0f, (1.0f - (fragmentDistance.z / u_pointlightRadiuses[index].z)));

			attenuation = min(xAttenuation, min(yAttenuation, zAttenuation));
		}

		current += vec3(diffuse);
		current += vec3(specular);
		current *= u_pointlightColors[index];
		current *= (attenuation * attenuation);
		current *= u_pointlightIntensities[index];

		result += current;
	}

	return result;
}

vec3 calculateSpotLighting(vec3 specularMapColor, vec3 normal)
{
	vec3 result = vec3(0.0f);

	for (int index = 0; index < u_spotlightCount; index++)
	{
		vec3 current = vec3(0.0f);
		vec3 lightDirection = normalize(u_spotlightPositions[index] - f_worldSpacePos);

		float diffuse = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(specularMapColor, lightDirection, normal);
		float spot = dot(lightDirection, normalize(-u_spotlightFronts[index]));
		float smoothingAngle = (u_spotlightAngles[index] * (1.0f - SPOTLIGHT_SMOOTHING_MULTIPLIER));
		float intensity = clamp(((spot - (u_spotlightAngles[index] * SPOTLIGHT_SMOOTHING_MULTIPLIER)) / smoothingAngle), 0.0f, 1.0f);  
		float fragmentDistance = distance(u_spotlightPositions[index], f_worldSpacePos);
		float distanceMultiplier = (1.0f - clamp((fragmentDistance / u_spotlightDistances[index]), 0.0f, 1.0f));

		current += vec3(diffuse);
		current += vec3(specular);
		current *= intensity;
		current *= u_spotlightColors[index];
		current *= u_spotlightIntensities[index];
		current *= distanceMultiplier;

		result += current;
	}

	return result;
}

vec3 calculateCubeReflection(vec3 reflectionMapColor, vec3 color, vec3 normal)
{
	if(u_isReflectionsEnabled && u_isReflective && (u_reflectionType == 0))
	{		
		if(reflectionMapColor != vec3(0.0f))
		{
			vec3 viewDirection = normalize(f_worldSpacePos - u_cameraPosition);
			vec3 reflectionDirection = reflect(viewDirection, normal);
			vec3 previousCubeReflectionMapColor = texture(u_previousReflectionCubeMap, reflectionDirection).rgb;
			vec3 currentCubeReflectionMapColor = texture(u_currentReflectionCubeMap, reflectionDirection).rgb;
			vec3 cubeReflectionMapColor = mix(previousCubeReflectionMapColor, currentCubeReflectionMapColor, u_cubeReflectionMixValue);
			vec3 mixedColor = mix(color, cubeReflectionMapColor, u_reflectivity);

			return mixedColor;
		}

		return color;
	}
	else
	{
		return color;
	}
}

vec3 calculateCubeRefraction(vec3 refractionMapColor, vec3 color, vec3 normal)
{
	if(u_isRefractionsEnabled && u_isRefractive && (u_refractionType == 0))
	{		
		if(refractionMapColor != vec3(0.0f))
		{
			vec3 viewDirection = normalize(f_worldSpacePos - u_cameraPosition);
			vec3 refractionDirection = refract(viewDirection, normal, CUBE_REFRACTION_RATIO);
			vec3 previousCubeRefractionMapColor = texture(u_previousRefractionCubeMap, refractionDirection).rgb;
			vec3 currentCubeRefractionMapColor = texture(u_currentRefractionCubeMap, refractionDirection).rgb;
			vec3 cubeRefractionMapColor = mix(previousCubeRefractionMapColor, currentCubeRefractionMapColor, u_cubeRefractionMixValue);
			vec3 mixedColor = mix(color, cubeRefractionMapColor, u_refractivity);

			return mixedColor;
		}

		return color;
	}
	else
	{
		return color;
	}
}

vec3 calculatePlanarReflection(vec3 reflectionMapColor, vec3 color)
{
	if(u_isReflectionsEnabled && u_isReflective && (u_reflectionType == 1))
	{
		if(reflectionMapColor != vec3(0.0f))
		{
			vec2 uvCoords = (((f_clipSpacePos.xy / f_clipSpacePos.w) * 0.5f) + 0.5f);
			vec3 reflectionColor = texture(u_planarReflectionMap, vec2(uvCoords.x, -uvCoords.y)).rgb;
			vec3 mixedColor = mix(color, reflectionColor, u_reflectivity);
        
			return mixedColor;
		}

		return color;
	}
	else
	{
		return color;
	}
}

vec3 calculatePlanarRefraction(vec3 refractionMapColor, vec3 color)
{
	if(u_isRefractionsEnabled && u_isRefractive && (u_refractionType == 1))
	{
		if(refractionMapColor != vec3(0.0f))
		{
			vec2 uvCoords = (((f_clipSpacePos.xy / f_clipSpacePos.w) * 0.5f) + 0.5f);
			vec3 refractionColor = texture(u_planarRefractionMap, uvCoords).rgb;
			vec3 mixedColor = mix(color, refractionColor, u_refractivity);
        
			return mixedColor;
		}

		return color;
	}
	else
	{
		return color;
	}
}

vec3 calculateFog(vec3 color)
{
	if(u_isFogEnabled)
	{
        float fragmentDistance = distance(f_worldSpacePos.xyz, u_cameraPosition);
		float distanceDifference = (u_maxFogDistance - u_minFogDistance);
		float distancePart = clamp(((fragmentDistance - u_minFogDistance) / distanceDifference), 0.0f, 1.0f);
		float thickness = clamp(u_fogThickness, 0.0f, 1.0f);
		float mixValue = (distancePart * thickness);

		return mix(color, u_fogColor, mixValue);
	}
	else
	{
		return color;
	}
}

void main()
{
	if(u_isWireframed)
	{
		o_primaryColor = vec4(u_wireframeColor, 1.0f);
		o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);

		return;
	}

	vec3 primaryColor = vec3(0.0f);
	vec3 diffuseMapping = calculateDiffuseMapping();
	vec3 emissionMapping = calculateEmissionMapping();
    vec3 specularMapping = calculateSpecularMapping();
    vec3 reflectionMapping = calculateReflectionMapping();
	vec3 refractionMapping = calculateRefractionMapping();
    vec3 normalMapping = calculateNormalMapping();

	float shadowLighting = calculateShadows();

	vec3 ambientLighting = calculateAmbientLighting(shadowLighting);
	vec3 directionalLighting = calculateDirectionalLighting(specularMapping, normalMapping, shadowLighting);
	vec3 pointLighting = calculatePointLighting(specularMapping, normalMapping);
	vec3 spotLighting = calculateSpotLighting(specularMapping, normalMapping);

	primaryColor += diffuseMapping;
	primaryColor += emissionMapping;
	primaryColor = calculateCubeReflection(reflectionMapping, primaryColor, normalMapping);
	primaryColor = calculateCubeRefraction(refractionMapping, primaryColor, normalMapping);
	primaryColor = calculatePlanarReflection(reflectionMapping, primaryColor);
	primaryColor = calculatePlanarRefraction(refractionMapping, primaryColor);
	primaryColor *= u_color;
	primaryColor *= u_lightness;
	
	bool isBright = ((emissionMapping != vec3(0.0f)) || u_isBright);

	if(!isBright)
	{
		primaryColor *= (ambientLighting + directionalLighting + pointLighting + spotLighting);
	}

	primaryColor = calculateFog(primaryColor);
	primaryColor = clamp(primaryColor, vec3(0.0f), vec3(1.0f));
    primaryColor = pow(primaryColor, vec3(1.0f / GAMMA_VALUE));

	o_primaryColor = vec4(primaryColor, u_opacity);
	o_secondaryColor = vec4((isBright ? primaryColor : vec3(0.0f)), 1.0f);
}