#version 460 core

#define MAX_POINTLIGHT_COUNT 64
#define MAX_SPOTLIGHT_COUNT 64
#define SPOTLIGHT_SMOOTHING_MULTIPLIER 0.95f

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

uniform float u_pointlightIntensities[MAX_POINTLIGHT_COUNT];
uniform float u_spotlightIntensities[MAX_SPOTLIGHT_COUNT];
uniform float u_spotlightAngles[MAX_SPOTLIGHT_COUNT];
uniform float u_spotlightDistances[MAX_SPOTLIGHT_COUNT];
uniform float u_lightness;
uniform float u_ambientLightingIntensity;
uniform float u_directionalLightingIntensity;
uniform float u_textureRepeat;
uniform float u_redTextureRepeat;
uniform float u_greenTextureRepeat;
uniform float u_blueTextureRepeat;
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

    vec3 normal = calculateNormalMapping();

    float shadowLighting	 = calculateShadows();
	float shadowOcclusion	 = ((shadowLighting - u_shadowLightness) / (1.0f - u_shadowLightness));
	vec3 ambientLighting	 = (calculateAmbientLighting() * shadowLighting);
	vec3 directionalLighting = (calculateDirectionalLighting(normal) * shadowOcclusion);
	vec3 pointlights	     = calculatePointlights(normal);
	vec3 spotlights		     = calculateSpotlights(normal);

	vec3 primaryColor = vec3(0.0f);
	primaryColor += calculateDiffuseMapping();
	primaryColor *= u_lightness;
	primaryColor  = clamp(primaryColor, vec3(0.0f), vec3(1.0f));

	vec3 lighting = vec3(0.0f);
	lighting += ambientLighting;
	lighting += directionalLighting;
	lighting += pointlights;
	lighting += spotlights;
	primaryColor *= lighting;

	primaryColor = calculateFog(primaryColor);

	primaryColor = pow(primaryColor, vec3(1.0f / 2.2f));

	o_primaryColor = vec4(primaryColor, 1.0f);
	o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

vec3 calculateDiffuseMapping()
{
	if(u_hasBlendMap)
	{
		vec2 blendUv = (f_uv / u_textureRepeat);

		vec4 blendMapColor = texture(u_blendMap, blendUv);

		vec3 diffuseMapColor = vec3(0.0f);
		if(u_hasDiffuseMap)
		{
			float blendMultiplier = (1.0f - blendMapColor.r - blendMapColor.g - blendMapColor.b);
			diffuseMapColor = (texture(u_diffuseMap, f_uv).rgb * blendMultiplier);
			diffuseMapColor = pow(diffuseMapColor, vec3(2.2f));
		}

		vec3 rColor = (u_hasRedDiffuseMap ? (texture(u_redDiffuseMap, (blendUv * u_redTextureRepeat)).rgb * blendMapColor.r) : vec3(0.0f));
		vec3 gColor = (u_hasGreenDiffuseMap ? (texture(u_greenDiffuseMap, (blendUv * u_greenTextureRepeat)).rgb * blendMapColor.g) : vec3(0.0f));
		vec3 bColor = (u_hasBlueDiffuseMap ? (texture(u_blueDiffuseMap, (blendUv * u_blueTextureRepeat)).rgb * blendMapColor.b) : vec3(0.0f));
		rColor = pow(rColor, vec3(2.2f));
		gColor = pow(gColor, vec3(2.2f));
		bColor = pow(bColor, vec3(2.2f));

		vec3 newColor = (diffuseMapColor + rColor + gColor + bColor);
        
		return newColor;
	}
	else if(u_hasDiffuseMap)
	{
		vec3 newColor = texture(u_diffuseMap, vec2(-f_uv.x, f_uv.y)).rgb;
		newColor = pow(newColor, vec3(2.2f));

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
			vec2 blendUv = (f_uv / u_textureRepeat);
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
				vec3 normal = texture(u_redNormalMap, (blendUv * u_redTextureRepeat)).rgb;
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
				vec3 normal = texture(u_greenNormalMap, (blendUv * u_greenTextureRepeat)).rgb;
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
				vec3 normal = texture(u_blueNormalMap, (blendUv * u_blueTextureRepeat)).rgb;
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
        vec3 result = vec3(0.0f);
        vec3 direction = normalize(u_directionalLightingPosition - f_worldSpacePos);
		float diffuse = clamp(dot(normal, direction), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(u_directionalLightingPosition, normal);

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

vec3 calculatePointlights(vec3 normal)
{
	vec3 result = vec3(0.0f);
		
	for (int i = 0; i < u_pointlightCount; i++)
	{
		vec3 direction = normalize(u_pointlightPositions[i] - f_worldSpacePos);
		float diffuse = clamp(dot(normal, direction), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(u_pointlightPositions[i], normal);

		float attenuation;
		if(u_pointlightShapes[i] == 0)
		{
			float fragmentDistance = distance(u_pointlightPositions[i], f_worldSpacePos);
			float averageRadius = ((u_pointlightRadiuses[i].x + u_pointlightRadiuses[i].y + u_pointlightRadiuses[i].z) / 3.0f);
			attenuation = max(0.0f, (1.0f - (fragmentDistance / averageRadius)));
		}
		else
		{
			vec3 fragmentDistance = abs(u_pointlightPositions[i] - f_worldSpacePos);
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

vec3 calculateSpotlights(vec3 normal)
{
	vec3 result = vec3(0.0f);

	for (int i = 0; i < u_spotlightCount; i++)
	{
		vec3 direction = normalize(u_spotlightPositions[i] - f_worldSpacePos);
		float spot = dot(direction, normalize(-u_spotlightFronts[i]));
		float diffuse = clamp(dot(normal, direction), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(u_spotlightPositions[i], normal);
		float smoothingAngle = (u_spotlightAngles[i] * (1.0f - SPOTLIGHT_SMOOTHING_MULTIPLIER));
		float intensity = clamp(((spot - (u_spotlightAngles[i] * SPOTLIGHT_SMOOTHING_MULTIPLIER)) / smoothingAngle), 0.0f, 1.0f);  

		float fragmentDistance = distance(u_spotlightPositions[i], f_worldSpacePos);
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

float calculateSpecularLighting(vec3 lightPosition, vec3 normal)
{
    if(u_isSpecular)
    {
        vec3 lightDirection   = normalize(lightPosition - f_worldSpacePos);
        vec3 viewDirection    = normalize(u_cameraPosition - f_worldSpacePos);
        vec3 halfWayDirection = normalize(lightDirection + viewDirection);
        float result          = pow(clamp(dot(normal, halfWayDirection), 0.0f, 1.0f), u_specularShininess);

        return (result * u_specularIntensity);
    }
    else
    {
        return 0.0f;
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
			float shadow = 0.0f;
			vec3 projCoords = (((f_shadowSpacePos.xyz / f_shadowSpacePos.w) * 0.5f) + 0.5f);
			float currentDepth = projCoords.z;
			vec2 texelSize = (vec2(1.0f) / textureSize(u_shadowMap, 0));

			if(projCoords.z > 1.0f)
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