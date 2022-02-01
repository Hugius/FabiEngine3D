#version 460 core

#define MAX_POINTLIGHT_COUNT 64
#define MAX_SPOTLIGHT_COUNT 64
#define SPOTLIGHT_SMOOTHING_MULTIPLIER 0.95f

in vec3 f_position;
in vec2 f_uv;
in vec3 f_normal;
in vec4 f_shadowPosition;
in vec4 f_clip;
in mat3 f_tbn;

layout (location = 0) uniform samplerCube u_previousCubeReflectionMap;
layout (location = 1) uniform samplerCube u_currentCubeReflectionMap;
layout (location = 2) uniform sampler2D u_planarReflectionMap;
layout (location = 3) uniform sampler2D u_shadowMap;
layout (location = 4) uniform sampler2D u_diffuseMap;
layout (location = 5) uniform sampler2D u_emissionMap;
layout (location = 6) uniform sampler2D u_specularMap;
layout (location = 7) uniform sampler2D u_reflectionMap;
layout (location = 8) uniform sampler2D u_normalMap;

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
uniform float u_minTextureAlpha;
uniform float u_shadowSize;
uniform float u_minFogDistance;
uniform float u_maxFogDistance;
uniform float u_fogThickness;
uniform float u_reflectivity;
uniform float u_lightness;
uniform float u_shadowLightness;
uniform float u_cubeReflectionMixValue;
uniform float u_emissionIntensity;

uniform int u_pointlightShapes[MAX_POINTLIGHT_COUNT];
uniform int u_pointlightCount;
uniform int u_spotlightCount;
uniform int u_reflectionType;

uniform bool u_isWireframed;
uniform bool u_isReflective;
uniform bool u_isSpecular;
uniform bool u_isShadowCircleEnabled;
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

layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

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

void main()
{
	if(u_isWireframed)
	{
		o_primaryColor = vec4(u_wireframeColor, 1.0f);
		o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
		return;
	}

	vec3 diffuseMapping = calculateDiffuseMapping();
	vec3 emissionMapping = calculateEmissionMapping();
    vec3 specularMapping = calculateSpecularMapping();
    vec3 reflectionMapping = calculateReflectionMapping();
    vec3 normalMapping = calculateNormalMapping();

	float shadowLighting	 = calculateShadows();
	float shadowOcclusion	 = ((shadowLighting - u_shadowLightness) / (1.0f - u_shadowLightness));
	vec3 ambientLighting	 = (calculateAmbientLighting() * shadowLighting);
	vec3 directionalLighting = (calculateDirectionalLighting(specularMapping, normalMapping) * shadowOcclusion);
	vec3 pointlights		 = calculatePointlights(specularMapping, normalMapping);
	vec3 spotlights		     = calculateSpotlights(specularMapping, normalMapping);

	vec3 primaryColor = vec3(0.0f);
	primaryColor += diffuseMapping;
	primaryColor += emissionMapping;
	primaryColor  = calculateCubeReflection(reflectionMapping, primaryColor, normalMapping);
	primaryColor  = calculatePlanarReflection(reflectionMapping, primaryColor);
	primaryColor *= u_color;
	primaryColor *= u_lightness;
	primaryColor  = clamp(primaryColor, vec3(0.0f), vec3(1.0f));
	
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

	primaryColor = calculateFog(primaryColor);

    primaryColor = pow(primaryColor, vec3(1.0f / 2.2f));

	o_primaryColor = vec4(primaryColor, u_opacity);
	o_secondaryColor = vec4((isBright ? primaryColor : vec3(0.0f)), 1.0f);
}

vec3 calculateDiffuseMapping()
{
	if (u_hasDiffuseMap)
	{
		vec4 diffuseMapColor = texture(u_diffuseMap, f_uv);
		diffuseMapColor.rgb = pow(diffuseMapColor.rgb, vec3(2.2f));

		if (diffuseMapColor.a < u_minTextureAlpha)
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
	if (u_hasEmissionMap)
	{
		vec4 emissionMapColor = texture(u_emissionMap, f_uv);

		if (emissionMapColor.a < u_minTextureAlpha)
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
    if (u_hasSpecularMap)
    {
		vec4 specularMapColor = texture(u_specularMap, f_uv);

		if (specularMapColor.a < u_minTextureAlpha)
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
    if (u_hasReflectionMap)
    {
		vec4 reflectionMapColor = texture(u_reflectionMap, f_uv);

		if (reflectionMapColor.a < u_minTextureAlpha)
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

vec3 calculateNormalMapping()
{
    if (u_hasNormalMap)
    {
        vec3 normal = texture(u_normalMap, f_uv).rgb;
        normal = ((normal * 2.0f) - 1.0f);
        normal = normalize(f_tbn * normal);

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
        vec3 result = vec3(0.0f);
		vec3 direction = normalize(u_directionalLightingPosition - f_position);
		float diffuse = clamp(dot(normal, direction), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(specularMapColor, u_directionalLightingPosition, normal);

        result += vec3(diffuse);
        result += vec3(specular);
        result *= u_directionalLightingColor;
        result *= u_directionalLightingIntensity;

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

	for (int i = 0; i < u_pointlightCount; i++)
	{
		vec3 direction = normalize(u_pointlightPositions[i] - f_position);
		float diffuse = clamp(dot(normal, direction), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(specularMapColor, u_pointlightPositions[i], normal);

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

		vec3 current = vec3(0.0f);
		current += vec3(diffuse);
		current += vec3(specular);
		current *= u_pointlightColors[i];
		current *= (attenuation * attenuation);
		current *= u_pointlightIntensities[i];

		result += current;
	}

	return result;
}

vec3 calculateSpotlights(vec3 specularMapColor, vec3 normal)
{
	vec3 result = vec3(0.0f);

	for (int i = 0; i < u_spotlightCount; i++)
	{
		vec3 direction = normalize(u_spotlightPositions[i] - f_position);
		float spot = dot(direction, normalize(-u_spotlightFronts[i]));
		float diffuse = clamp(dot(normal, direction), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(specularMapColor, u_spotlightPositions[i], normal);
		float smoothingAngle = (u_spotlightAngles[i] * (1.0f - SPOTLIGHT_SMOOTHING_MULTIPLIER));
		float intensity = clamp(((spot - (u_spotlightAngles[i] * SPOTLIGHT_SMOOTHING_MULTIPLIER)) / smoothingAngle), 0.0f, 1.0f);  

		float fragmentDistance = distance(u_spotlightPositions[i], f_position);
		float distanceMultiplier = (fragmentDistance / u_spotlightDistances[i]);
		distanceMultiplier = clamp(distanceMultiplier, 0.0f, 1.0f);
		distanceMultiplier = (1.0f - distanceMultiplier);

		vec3 current = vec3(0.0f);
		current += vec3(diffuse * intensity);
		current += vec3(specular * intensity);
		current *= u_spotlightColors[i];
		current *= u_spotlightIntensities[i];
		current *= distanceMultiplier;

		result += current;
	}

	return result;
}

vec3 calculateFog(vec3 color)
{
	if (u_isFogEnabled)
	{
        float fragmentDistance = distance(f_position.xyz, u_cameraPosition);
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

vec3 calculateCubeReflection(vec3 reflectionMapColor, vec3 color, vec3 normal)
{
	if (u_isReflectionsEnabled && u_isReflective && (u_reflectionType == 0))
	{		
		if (reflectionMapColor != vec3(0.0f))
		{
			vec3 viewDirection = normalize(f_position - u_cameraPosition);
			vec3 reflectionDirection = reflect(viewDirection, normal);
			vec3 previousCubeReflectionMapColor = texture(u_previousCubeReflectionMap, reflectionDirection).rgb;
			vec3 currentCubeReflectionMapColor = texture(u_currentCubeReflectionMap, reflectionDirection).rgb;
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

vec3 calculatePlanarReflection(vec3 reflectionMapColor, vec3 color)
{
	if (u_isReflectionsEnabled && u_isReflective && (u_reflectionType == 1))
	{
		if (reflectionMapColor != vec3(0.0f))
		{
			vec2 ndc = (((f_clip.xy / f_clip.w) * 0.5f) + 0.5f);
			vec2 texCoords = vec2(ndc.x, -ndc.y);
			vec3 reflectionColor = texture(u_planarReflectionMap, vec2(texCoords.x,  texCoords.y)).rgb;
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

float calculateShadows()
{
	if (u_isShadowsEnabled)
	{
		float halfSize = (u_shadowSize * 0.5f);
		float fragmentDistance = distance(f_position.xz, u_shadowLookat.xz);

		if (fragmentDistance <= halfSize)
		{
			vec2 texelSize = (vec2(1.0f) / textureSize(u_shadowMap, 0));
			float shadow = 0.0f;
			vec3 projCoords = (((f_shadowPosition.xyz / f_shadowPosition.w) * 0.5f) + 0.5f);
			float currentDepth = projCoords.z;
			float bias = 0.00075f;

			if (projCoords.z > 1.0f)
			{
				return 1.0f;
			}

			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					float pcfDepth = texture(u_shadowMap, projCoords.xy + (vec2(x, y) * texelSize)).r; 
					shadow += ((currentDepth - texelSize.x) > pcfDepth) ? u_shadowLightness : 1.0f;        
				}    
			}
            
			shadow /= 9.0f;
			
			if (shadow > 1.0f)
			{
				shadow = 1.0f;
			}

			float opacity = (fragmentDistance - (halfSize * 0.9f));
			opacity = clamp(opacity, 0.0f, (halfSize * 0.1f));
			opacity /= (halfSize * 0.1f);
			opacity = (1.0f - opacity);

			if (u_isShadowCircleEnabled)
			{
				if ((fragmentDistance - (halfSize * 0.99f)) > 0.0f)
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

float calculateSpecularLighting(vec3 specularMapColor, vec3 lightPosition, vec3 normal)
{
    if (u_isSpecular)
    {
        vec3 lightDirection = normalize(lightPosition - f_position);
        vec3 viewDirection = normalize(u_cameraPosition - f_position);
        vec3 halfWayDirection = normalize(lightDirection + viewDirection);
		float specularMapIntensity = ((specularMapColor.r + specularMapColor.g + specularMapColor.b) / 3.0f);
        float result = pow(clamp(dot(normal, halfWayDirection), 0.0f, 1.0f), (u_specularShininess * specularMapIntensity));

        return (result * u_specularIntensity * specularMapIntensity);
    }
    else
    {
        return 0.0f;
    }
}