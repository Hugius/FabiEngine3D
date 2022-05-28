#version 460 core

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

uniform vec3 u_ambientLightingColor;
uniform vec3 u_directionalLightingColor;
uniform vec3 u_directionalLightingPosition;
uniform vec3 u_cameraPosition;
uniform vec3 u_color;
uniform vec3 u_fogColor;
uniform vec3 u_wireframeColor;
uniform vec3 u_shadowLookat;

uniform vec2 u_rippleOffset;

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

vec2 calculateDudvMapping()
{
    if(u_hasNormalMap)
    {
		vec2 dudvMapColor = texture(u_dudvMap, (f_uv + u_rippleOffset)).rg;
		vec2 dudv = (dudvMapColor * 0.1f);

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
		distortedNdcUv *= 0.05f;

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
		finalColor *= u_color;
	}
	else if(u_isRefractionsEnabled && u_hasRefractionMap && u_isRefractive)
	{
		finalColor = texture(u_refractionMap, refractionUv).rgb;
		finalColor *= u_color;
	}
	else
	{
		finalColor = u_color;
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

vec3 calculateDirectionalDiffuseLighting(vec3 normal)
{
	if(u_isDirectionalLightingEnabled)
	{
        vec3 lighting = vec3(0.0f);
		vec3 lightDirection = normalize(u_directionalLightingPosition - f_worldSpacePos);

		float diffuse = clamp(dot(normal, lightDirection), 0.0f, 1.0f);

        lighting += vec3(diffuse);
        lighting *= u_directionalLightingColor;
        lighting *= u_directionalLightingIntensity;

        return lighting;
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 calculateDirectionalSpecularLighting(vec3 normal)
{
    if(u_isDirectionalLightingEnabled && u_isSpecular && (u_cameraPosition.y > f_worldSpacePos.y))
    {
		vec3 lighting = vec3(0.0f);
		vec3 lightDirection = normalize(u_directionalLightingPosition - f_worldSpacePos);
        vec3 viewDirection = normalize(u_cameraPosition - f_worldSpacePos);
        vec3 halfWayDirection = normalize(lightDirection + viewDirection);

        float specular = pow(clamp(dot(normal, halfWayDirection), 0.0f, 1.0f), u_specularShininess);

        lighting += vec3(specular);
        lighting *= u_directionalLightingColor;
        lighting *= u_directionalLightingIntensity;
		lighting *= u_specularIntensity;

        return lighting;
    }
    else
    {
        return vec3(0.0f);
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

	vec2 dudvMapping = calculateDudvMapping();
	vec3 normalMapping = calculateNormalMapping(dudvMapping);
	vec4 diffuseColor = calculateDiffuseColor(dudvMapping, normalMapping);

	float shadowLighting = calculateShadows();
	float shadowOcclusion = ((shadowLighting - u_shadowLightness) / (1.0f - u_shadowLightness));

	vec3 ambientLighting = (calculateAmbientLighting() * shadowLighting);
	vec3 directionalDiffuseLighting = (calculateDirectionalDiffuseLighting(normalMapping) * shadowOcclusion);
	vec3 directionalSpecularLighting = (calculateDirectionalSpecularLighting(normalMapping) * shadowOcclusion);
	vec3 primaryColor = vec3(0.0f);

	primaryColor += diffuseColor.rgb;
	primaryColor *= (ambientLighting + directionalDiffuseLighting);
	primaryColor += directionalSpecularLighting;
	primaryColor = calculateFog(primaryColor);
	primaryColor = clamp(primaryColor, vec3(0.0f), vec3(1.0f));
	primaryColor = pow(primaryColor, vec3(1.0f / GAMMA_VALUE));

	o_primaryColor = vec4(primaryColor, diffuseColor.a);
	o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}