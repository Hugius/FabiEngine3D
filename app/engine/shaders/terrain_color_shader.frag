#version 460 core

#define MAX_POINTLIGHT_COUNT 64
#define MAX_SPOTLIGHT_COUNT 64
#define SPOTLIGHT_SMOOTHING_MULTIPLIER 0.95f
#define SHADOW_BIAS 0.001f
#define GAMMA_VALUE 2.2f

in vec4 f_shadowSpacePos;
in vec3 f_worldSpacePos;
in vec2 f_uv;
in vec3 f_normal;
in mat3 f_tbn;

layout (location = 0) uniform sampler2D u_shadowMap;
layout (location = 1) uniform sampler2D u_diffuseMap;
layout (location = 2) uniform sampler2D u_normalMap;
layout (location = 3) uniform sampler2D u_blendMap;
layout (location = 4) uniform sampler2D u_redDiffuseMap;
layout (location = 5) uniform sampler2D u_greenDiffuseMap;
layout (location = 6) uniform sampler2D u_blueDiffuseMap;
layout (location = 7) uniform sampler2D u_redNormalMap;
layout (location = 8) uniform sampler2D u_greenNormalMap;
layout (location = 9) uniform sampler2D u_blueNormalMap;

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
uniform vec3 u_shadowLookat;
uniform vec3 u_fogColor;
uniform vec3 u_wireframeColor;
uniform vec3 u_color;

uniform float u_pointlightIntensities[MAX_POINTLIGHT_COUNT];
uniform float u_spotlightIntensities[MAX_SPOTLIGHT_COUNT];
uniform float u_spotlightAngles[MAX_SPOTLIGHT_COUNT];
uniform float u_spotlightDistances[MAX_SPOTLIGHT_COUNT];
uniform float u_lightness;
uniform float u_ambientLightingIntensity;
uniform float u_directionalLightingIntensity;
uniform float u_shadowSize;
uniform float u_minFogDistance;
uniform float u_maxFogDistance;
uniform float u_fogThickness;
uniform float u_specularShininess;
uniform float u_specularIntensity;
uniform float u_shadowLightness;

uniform int u_pointlightShapes[MAX_POINTLIGHT_COUNT];
uniform int u_pointlightCount;
uniform int u_spotlightCount;
uniform int u_textureRepeat;
uniform int u_redTextureRepeat;
uniform int u_greenTextureRepeat;
uniform int u_blueTextureRepeat;

uniform bool u_isWireframed;
uniform bool u_isSpecular;
uniform bool u_isAmbientLightingEnabled;
uniform bool u_isDirectionalLightingEnabled;
uniform bool u_isFogEnabled;
uniform bool u_isShadowsEnabled;
uniform bool u_isShadowCircleEnabled;
uniform bool u_hasDiffuseMap;
uniform bool u_hasNormalMap;
uniform bool u_hasBlendMap;
uniform bool u_hasRedDiffuseMap;
uniform bool u_hasGreenDiffuseMap;
uniform bool u_hasBlueDiffuseMap;
uniform bool u_hasRedNormalMap;
uniform bool u_hasGreenNormalMap;
uniform bool u_hasBlueNormalMap;

layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

vec3 calculateDiffuseMapping();
vec3 calculateNormalMapping();
vec3 calculateAmbientLighting();
vec3 calculateDirectionalLighting(vec3 normal);
vec3 calculatePointlights(vec3 normal);
vec3 calculateSpotlights(vec3 normal);
vec3 calculateFog(vec3 color);

float calculateSpecularLighting(vec3 lightPosition, vec3 normal);
float calculateShadows();

void main()
{
	if(u_isWireframed)
	{
		o_primaryColor = vec4(u_wireframeColor, 1.0f);
		o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);

		return;
	}

    float shadowLighting = calculateShadows();
	float shadowOcclusion = ((shadowLighting - u_shadowLightness) / (1.0f - u_shadowLightness));

	vec3 normalMapping = calculateNormalMapping();
	vec3 ambientLighting = (calculateAmbientLighting() * shadowLighting);
	vec3 directionalLighting = (calculateDirectionalLighting(normalMapping) * shadowOcclusion);
	vec3 pointlights = calculatePointlights(normalMapping);
	vec3 spotlights	= calculateSpotlights(normalMapping);

	vec3 primaryColor = vec3(0.0f);

	primaryColor += calculateDiffuseMapping();
	primaryColor *= u_color;
	primaryColor *= u_lightness;
	primaryColor = clamp(primaryColor, vec3(0.0f), vec3(1.0f));

	vec3 lighting = vec3(0.0f);

	lighting += ambientLighting;
	lighting += directionalLighting;
	lighting += pointlights;
	lighting += spotlights;

	primaryColor *= lighting;
	primaryColor = calculateFog(primaryColor);
	primaryColor = pow(primaryColor, vec3(1.0f / GAMMA_VALUE));

	o_primaryColor = vec4(primaryColor, 1.0f);
	o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

vec3 calculateDiffuseMapping()
{
	if(u_hasBlendMap)
	{
		vec2 blendUv = (f_uv / float(u_textureRepeat));
		vec4 blendMapColor = texture(u_blendMap, blendUv);

		vec3 diffuseMapColor = vec3(0.0f);

		if(u_hasDiffuseMap)
		{
			float blendMultiplier = (1.0f - blendMapColor.r - blendMapColor.g - blendMapColor.b);

			diffuseMapColor = (texture(u_diffuseMap, f_uv).rgb * blendMultiplier);
			diffuseMapColor = pow(diffuseMapColor, vec3(GAMMA_VALUE));
		}

		vec3 rColor = (u_hasRedDiffuseMap ? (texture(u_redDiffuseMap, (blendUv * float(u_redTextureRepeat))).rgb * blendMapColor.r) : vec3(0.0f));
		vec3 gColor = (u_hasGreenDiffuseMap ? (texture(u_greenDiffuseMap, (blendUv * float(u_greenTextureRepeat))).rgb * blendMapColor.g) : vec3(0.0f));
		vec3 bColor = (u_hasBlueDiffuseMap ? (texture(u_blueDiffuseMap, (blendUv * float(u_blueTextureRepeat))).rgb * blendMapColor.b) : vec3(0.0f));

		rColor = pow(rColor, vec3(GAMMA_VALUE));
		gColor = pow(gColor, vec3(GAMMA_VALUE));
		bColor = pow(bColor, vec3(GAMMA_VALUE));
        
		return (diffuseMapColor + rColor + gColor + bColor);
	}
	else if(u_hasDiffuseMap)
	{
		vec3 newColor = texture(u_diffuseMap, vec2(-f_uv.x, f_uv.y)).rgb;
		newColor = pow(newColor, vec3(GAMMA_VALUE));

		return newColor;
	}
	else
	{
		return vec3(1.0f);
	}
}

vec3 calculateNormalMapping()
{
    if(u_hasNormalMap || u_hasRedNormalMap || u_hasGreenNormalMap || u_hasBlueNormalMap)
    {
		if(u_hasBlendMap)
		{
			vec2 blendUv = (f_uv / float(u_textureRepeat));
			vec4 blendMapColor = texture(u_blendMap, blendUv);

			float diffuseIntensity = (1.0f - blendMapColor.r - blendMapColor.g - blendMapColor.b);
			float rIntensity = blendMapColor.r;
			float gIntensity = blendMapColor.g;
			float bIntensity = blendMapColor.b;

			vec3 totalNormal;

			if(u_hasNormalMap)
			{
				vec3 normal = texture(u_normalMap, f_uv).rgb;

				normal *= 2.0f;
				normal -= 1.0f;
				totalNormal += (normalize(f_tbn * normal) * diffuseIntensity);
			}
			else
			{
				totalNormal += f_normal * diffuseIntensity;
			}
			
			if(u_hasRedNormalMap)
			{
				vec3 normal = texture(u_redNormalMap, (blendUv * float(u_redTextureRepeat))).rgb;

				normal *= 2.0f;
				normal -= 1.0f;
				totalNormal += (normalize(f_tbn * normal) * rIntensity);
			}
			else
			{
				totalNormal += f_normal * rIntensity;
			}

			if(u_hasGreenNormalMap)
			{
				vec3 normal = texture(u_greenNormalMap, (blendUv * float(u_greenTextureRepeat))).rgb;

				normal *= 2.0f;
				normal -= 1.0f;
				totalNormal += (normalize(f_tbn * normal) * gIntensity);
			}
			else
			{
				totalNormal += f_normal * gIntensity;
			}

			if(u_hasBlueNormalMap)
			{
				vec3 normal = texture(u_blueNormalMap, (blendUv * float(u_blueTextureRepeat))).rgb;

				normal *= 2.0f;
				normal -= 1.0f;
				totalNormal += (normalize(f_tbn * normal) * bIntensity);
			}
			else
			{
				totalNormal += f_normal * bIntensity;
			}

			return totalNormal;
		}
		else
		{
			if(u_hasNormalMap)
			{
				vec3 normal = texture(u_normalMap, f_uv).rgb;

				normal *= 2.0f;
				normal -= 1.0f;
				normal = normalize(f_tbn * normal);

				return normal;
			}
			else
			{
				return f_normal;
			}
		}        
    }
    else
    {
        return f_normal;
    }
}

vec3 calculateAmbientLighting()
{
	if(u_isAmbientLightingEnabled)
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
	if(u_isDirectionalLightingEnabled)
	{
        vec3 lighting = vec3(0.0f);
        vec3 direction = normalize(u_directionalLightingPosition - f_worldSpacePos);

		float diffuse = clamp(dot(normal, direction), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(u_directionalLightingPosition, normal);

        lighting += vec3(diffuse);
        lighting += vec3(specular);
        lighting *= u_directionalLightingColor;
        lighting *= u_directionalLightingIntensity;

        return lighting;
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 calculatePointlights(vec3 normal)
{
	vec3 lighting = vec3(0.0f);
		
	for (int index = 0; index < u_pointlightCount; index++)
	{
		vec3 direction = normalize(u_pointlightPositions[index] - f_worldSpacePos);

		float diffuse = clamp(dot(normal, direction), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(u_pointlightPositions[index], normal);

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

		vec3 current = vec3(0.0f);

		current += vec3(diffuse);
		current += vec3(specular);
		current *= u_pointlightColors[index];
		current *= (attenuation * attenuation);
		current *= u_pointlightIntensities[index];

		lighting += current;
	}

	return lighting;
}

vec3 calculateSpotlights(vec3 normal)
{
	vec3 lighting = vec3(0.0f);

	for (int index = 0; index < u_spotlightCount; index++)
	{
		vec3 direction = normalize(u_spotlightPositions[index] - f_worldSpacePos);

		float spot = dot(direction, normalize(-u_spotlightFronts[index]));
		float diffuse = clamp(dot(normal, direction), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(u_spotlightPositions[index], normal);
		float smoothingAngle = (u_spotlightAngles[index] * (1.0f - SPOTLIGHT_SMOOTHING_MULTIPLIER));
		float intensity = clamp(((spot - (u_spotlightAngles[index] * SPOTLIGHT_SMOOTHING_MULTIPLIER)) / smoothingAngle), 0.0f, 1.0f);  

		float fragmentDistance = distance(u_spotlightPositions[index], f_worldSpacePos);
		float distanceMultiplier = (fragmentDistance / u_spotlightDistances[index]);

		distanceMultiplier = clamp(distanceMultiplier, 0.0f, 1.0f);
		distanceMultiplier = (1.0f - distanceMultiplier);

		vec3 current = vec3(0.0f);

		current += vec3(diffuse * intensity);
		current += vec3(specular * intensity);
		current *= u_spotlightColors[index];
		current *= u_spotlightIntensities[index];
		current *= distanceMultiplier;

		lighting += current;
	}

	return lighting;
}

vec3 calculateFog(vec3 color)
{
	if(u_isFogEnabled)
	{
		float fragmentDistance = distance(f_worldSpacePos.xyz, u_cameraPosition);
		float distanceDifference = (u_maxFogDistance - u_minFogDistance);
		float fragmentPart = clamp(((fragmentDistance - u_minFogDistance) / distanceDifference), 0.0f, 1.0f);
		float thickness = clamp(u_fogThickness, 0.0f, 1.0f);
		float mixValue = (fragmentPart * thickness);

		return mix(color, u_fogColor, mixValue);
	}
	else
	{
		return color;
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

			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					vec2 uvOffset = (vec2(x, y) * texelSize);

					float depth = texture(u_shadowMap, (uvCoords.xy + uvOffset)).r;
					float lightness = (((uvCoords.z - SHADOW_BIAS) > depth) ? u_shadowLightness : 1.0f);

					shadow += lightness;         
				}    
			}
            
			shadow /= 9.0f;
			
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

float calculateSpecularLighting(vec3 lightPosition, vec3 normal)
{
    if(u_isSpecular)
    {
        vec3 lightDirection = normalize(lightPosition - f_worldSpacePos);
        vec3 viewDirection = normalize(u_cameraPosition - f_worldSpacePos);
        vec3 halfWayDirection = normalize(lightDirection + viewDirection);

        float lighting = pow(clamp(dot(normal, halfWayDirection), 0.0f, 1.0f), u_specularShininess);

        return (lighting * u_specularIntensity);
    }
    else
    {
        return 0.0f;
    }
}