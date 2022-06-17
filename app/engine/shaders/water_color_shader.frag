#version 460 core

#define MAX_POINTLIGHT_COUNT 64
#define MAX_SPOTLIGHT_COUNT 64
#define SPOTLIGHT_SMOOTHING_MULTIPLIER 0.95f
#define GAMMA_VALUE 2.2f

in vec4 f_shadowSpacePos;
in vec3 f_worldSpacePos;
in vec4 f_clipSpacePos;
in vec2 f_uv;

layout (location = 0) uniform sampler2D u_reflectionMap;
layout (location = 1) uniform sampler2D u_refractionMap;
layout (location = 2) uniform sampler2D u_edgeMap;
layout (location = 3) uniform sampler2D u_dudvMap;
layout (location = 4) uniform sampler2D u_normalMap;
layout (location = 6) uniform sampler2D u_shadowMap;

uniform vec3 u_pointlightPositions[MAX_POINTLIGHT_COUNT];
uniform vec3 u_pointlightRadiuses[MAX_POINTLIGHT_COUNT];
uniform vec3 u_pointlightColors[MAX_POINTLIGHT_COUNT];
uniform vec3 u_spotlightPositions[MAX_SPOTLIGHT_COUNT];
uniform vec3 u_spotlightFronts[MAX_SPOTLIGHT_COUNT];
uniform vec3 u_spotlightColors[MAX_SPOTLIGHT_COUNT];
uniform vec3 u_ambientLightingColor;
uniform vec3 u_directionalLightingColor;
uniform vec3 u_directionalLightingPosition;
uniform vec3 u_cameraPosition;
uniform vec3 u_color;
uniform vec3 u_fogColor;
uniform vec3 u_wireframeColor;
uniform vec3 u_shadowLookat;

uniform vec2 u_rippleOffset;

uniform float u_pointlightIntensities[MAX_POINTLIGHT_COUNT];
uniform float u_spotlightIntensities[MAX_SPOTLIGHT_COUNT];
uniform float u_spotlightAngles[MAX_SPOTLIGHT_COUNT];
uniform float u_spotlightDistances[MAX_SPOTLIGHT_COUNT];
uniform float u_ambientLightingIntensity;
uniform float u_directionalLightingIntensity;
uniform float u_specularShininess;
uniform float u_specularIntensity;
uniform float u_cameraNear;
uniform float u_cameraFar;
uniform float u_minFogDistance;
uniform float u_maxFogDistance;
uniform float u_fogThickness;
uniform float u_maxDepth;
uniform float u_shadowSize;
uniform float u_shadowLightness;
uniform float u_shadowBias;
uniform float u_lightness;
uniform float u_distortionSize;
uniform float u_distortionFactor;

uniform int u_pointlightShapes[MAX_POINTLIGHT_COUNT];
uniform int u_pointlightCount;
uniform int u_spotlightCount;
uniform int u_shadowPcfCount;

uniform bool u_isReflectionsEnabled;
uniform bool u_isRefractionsEnabled;
uniform bool u_isEdged;
uniform bool u_isWireframed;
uniform bool u_isAmbientLightingEnabled;
uniform bool u_isDirectionalLightingEnabled;
uniform bool u_isFogEnabled;
uniform bool u_isSpecular;
uniform bool u_isReflective;
uniform bool u_isRefractive;
uniform bool u_hasReflectionMap;
uniform bool u_hasRefractionMap;
uniform bool u_hasDudvMap;
uniform bool u_hasNormalMap;
uniform bool u_isShadowCircleEnabled;
uniform bool u_isShadowsEnabled;

layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

float convertDepthToPerspective(float depth)
{
    float z = ((depth * 2.0f) - 1.0f);

    return ((2.0f * u_cameraNear * u_cameraFar) / (u_cameraFar + u_cameraNear - z * (u_cameraFar - u_cameraNear)));
}

float calculateSpecularLighting(vec3 lightDirection, vec3 normal)
{
    if(u_isDirectionalLightingEnabled && u_isSpecular && (u_cameraPosition.y > f_worldSpacePos.y))
    {
        vec3 viewDirection = normalize(u_cameraPosition - f_worldSpacePos);
        vec3 halfWayDirection = normalize(lightDirection + viewDirection);

		float result = 0.0f;
        float specular = pow(clamp(dot(normal, halfWayDirection), 0.0f, 1.0f), u_specularShininess);

        result += specular;
		result *= u_specularIntensity;

        return result;
    }
    else
    {
        return 0.0f;
    }
}

vec2 calculateDudvMapping()
{
    if(u_hasNormalMap)
    {
		vec2 dudvMapColor = texture(u_dudvMap, (f_uv + u_rippleOffset)).rg;
		vec2 dudv = (dudvMapColor * u_distortionSize);

		return dudv;
    }
    else
    {
        return vec2(0.0f);
    }
}

vec3 calculateNormalMapping(vec2 dudv)
{
    if(u_hasNormalMap)
    {
		vec3 normalMapColor = texture(u_normalMap, (f_uv + dudv)).rgb;
		vec3 normal = normalize(vec3(((normalMapColor.r * 2.0f) - 1.0f), normalMapColor.b, ((normalMapColor.g * 2.0f) - 1.0f)));

		return normal;
    }
    else
    {
        return vec3(0.0f, 1.0f, 0.0f);
    }
}

vec4 calculateDiffuseColor(vec2 dudv, vec3 normal)
{
	vec2 ndc = (f_clipSpacePos.xy / f_clipSpacePos.w);

	ndc /= 2.0f;
	ndc += 0.5f;

	vec2 reflectionUv = vec2(ndc.x, -ndc.y);
	vec2 refractionUv = vec2(ndc.x, ndc.y);

	float opacity = 1.0f;

	if(u_isEdged)
	{
		float objectDistance = convertDepthToPerspective(texture(u_edgeMap, refractionUv).r);
		float waterDistance = convertDepthToPerspective(gl_FragCoord.z);
		float depth = (objectDistance - waterDistance);

		opacity = (depth / u_maxDepth);
		opacity = clamp(opacity, 0.0f, 1.0f);
	}

	if(u_hasDudvMap)
	{
		vec2 distortedNdcUv = texture(u_dudvMap, (f_uv + dudv)).rg;

		distortedNdcUv *= 2.0f;
		distortedNdcUv -= 1.0f;
		distortedNdcUv *= u_distortionFactor;

		reflectionUv += distortedNdcUv;
		refractionUv += distortedNdcUv;

		reflectionUv.x = clamp(reflectionUv.x, 0.001f, 0.999f);
		reflectionUv.y = clamp(reflectionUv.y, -0.999f, -0.001f);
		refractionUv.x = clamp(refractionUv.x, 0.001f, 0.999f);
		refractionUv.y = clamp(refractionUv.y, 0.001f, 0.999f);
	}

	vec3 finalColor;

	if(u_isReflectionsEnabled && u_hasReflectionMap && u_isReflective)
	{
		vec3 reflectionColor = texture(u_reflectionMap, reflectionUv).rgb;
		vec3 viewDirection = normalize(u_cameraPosition - f_worldSpacePos);

		float fresnelMixValue = dot(viewDirection, normal);

		finalColor = mix(reflectionColor, (reflectionColor * 0.05f), fresnelMixValue);
	}
	else if(u_isRefractionsEnabled && u_hasRefractionMap && u_isRefractive)
	{
		finalColor = texture(u_refractionMap, refractionUv).rgb;
	}
	else
	{
		finalColor = vec3(1.0f);
	}

	return vec4(finalColor, opacity);
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

void calculateAmbientLighting(in float shadowLighting, out vec3 ambient)
{
	if(u_isAmbientLightingEnabled)
	{
		ambient = vec3(1.0f);

		ambient *= shadowLighting;
		ambient *= u_ambientLightingColor;
		ambient *= u_ambientLightingIntensity;
	}
	else
	{
		ambient = vec3(0.0f);
	}
}

void calculateDirectionalLighting(in vec3 normal, in float shadowLighting, out vec3 diffuse, out vec3 specular)
{
	if(u_isDirectionalLightingEnabled)
	{
		vec3 lightDirection = normalize(u_directionalLightingPosition - f_worldSpacePos);

		diffuse = vec3(clamp(dot(normal, lightDirection), 0.0f, 1.0f));
		specular = vec3(calculateSpecularLighting(lightDirection, normal));

		diffuse *= shadowLighting;
        diffuse *= u_directionalLightingColor;
        diffuse *= u_directionalLightingIntensity;

		specular *= (shadowLighting * shadowLighting);
        specular *= u_directionalLightingColor;
        specular *= u_directionalLightingIntensity;
	}
	else
	{
		diffuse = vec3(0.0f);
		specular = vec3(0.0f);
	}
}

void calculatePointLighting(in vec3 normal, out vec3 resultDiffuse, out vec3 resultSpecular)
{
	resultDiffuse = vec3(0.0f);
	resultSpecular = vec3(0.0f);
		
	for (int index = 0; index < u_pointlightCount; index++)
	{
		vec3 lightDirection = normalize(u_pointlightPositions[index] - f_worldSpacePos);
		vec3 currentDiffuse = vec3(clamp(dot(normal, lightDirection), 0.0f, 1.0f));
		vec3 currentSpecular = vec3(calculateSpecularLighting(lightDirection, normal));

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

		currentDiffuse *= u_pointlightColors[index];
		currentDiffuse *= u_pointlightIntensities[index];
		currentDiffuse *= (attenuation * attenuation);

		currentSpecular *= u_pointlightColors[index];
		currentSpecular *= u_pointlightIntensities[index];
		currentSpecular *= (attenuation * attenuation);

		resultDiffuse += currentDiffuse;
		resultSpecular += currentSpecular;
	}
}

void calculateSpotLighting(in vec3 normal, out vec3 resultDiffuse, out vec3 resultSpecular)
{
	resultDiffuse = vec3(0.0f);
	resultSpecular = vec3(0.0f);

	for (int index = 0; index < u_spotlightCount; index++)
	{
		vec3 lightDirection = normalize(u_spotlightPositions[index] - f_worldSpacePos);
		vec3 currentDiffuse = vec3(clamp(dot(normal, lightDirection), 0.0f, 1.0f));
		vec3 currentSpecular = vec3(calculateSpecularLighting(lightDirection, normal));

		float spot = dot(lightDirection, normalize(-u_spotlightFronts[index]));
		float smoothingAngle = (u_spotlightAngles[index] * (1.0f - SPOTLIGHT_SMOOTHING_MULTIPLIER));
		float intensity = clamp(((spot - (u_spotlightAngles[index] * SPOTLIGHT_SMOOTHING_MULTIPLIER)) / smoothingAngle), 0.0f, 1.0f);  
		float fragmentDistance = distance(u_spotlightPositions[index], f_worldSpacePos);
		float distanceMultiplier = (1.0f - clamp((fragmentDistance / u_spotlightDistances[index]), 0.0f, 1.0f));

		currentDiffuse *= intensity;
		currentDiffuse *= u_spotlightColors[index];
		currentDiffuse *= u_spotlightIntensities[index];
		currentDiffuse *= distanceMultiplier;

		currentSpecular *= intensity;
		currentSpecular *= u_spotlightColors[index];
		currentSpecular *= u_spotlightIntensities[index];
		currentSpecular *= distanceMultiplier;

		resultDiffuse += currentDiffuse;
		resultSpecular += currentSpecular;
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
	vec2 dudvMapping = calculateDudvMapping();
	vec3 normalMapping = calculateNormalMapping(dudvMapping);
	vec4 diffuseColor = calculateDiffuseColor(dudvMapping, normalMapping);

	float shadowLighting = calculateShadows();

	vec3 ambientLighting;
	vec3 diffuseDirectionalLighting;
	vec3 diffusePointLighting;
	vec3 diffuseSpotLighting;
	vec3 specularDirectionalLighting;
	vec3 specularPointLighting;
	vec3 specularSpotLighting;

	calculateAmbientLighting(shadowLighting, ambientLighting);
	calculateDirectionalLighting(normalMapping, shadowLighting, diffuseDirectionalLighting, specularDirectionalLighting);
	calculatePointLighting(normalMapping, diffusePointLighting, specularPointLighting);
	calculateSpotLighting(normalMapping, diffuseSpotLighting, specularSpotLighting);

	primaryColor += diffuseColor.rgb;
	primaryColor *= u_color;
	primaryColor *= u_lightness;
	primaryColor *= (ambientLighting + diffuseDirectionalLighting + diffusePointLighting + diffuseSpotLighting);
	primaryColor += (specularDirectionalLighting + specularPointLighting + specularSpotLighting);
	primaryColor = calculateFog(primaryColor);
	primaryColor = clamp(primaryColor, vec3(0.0f), vec3(1.0f));
	primaryColor = pow(primaryColor, vec3(1.0f / GAMMA_VALUE));

	o_primaryColor = vec4(primaryColor, diffuseColor.a);
	o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}