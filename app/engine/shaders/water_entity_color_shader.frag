#version 460 core

#define MAX_LIGHT_COUNT 128

in vec3 f_position;
in vec2 f_uv;
in vec4 f_clip;

layout (location = 0) uniform sampler2D u_reflectionMap;
layout (location = 1) uniform sampler2D u_refractionMap;
layout (location = 2) uniform sampler2D u_depthMap;
layout (location = 3) uniform sampler2D u_dudvMap;
layout (location = 4) uniform sampler2D u_normalMap;

uniform vec3 u_pointlightPositions[MAX_LIGHT_COUNT];
uniform vec3 u_pointlightRadiuses[MAX_LIGHT_COUNT];
uniform vec3 u_pointlightColors[MAX_LIGHT_COUNT];
uniform vec3 u_directionalLightingColor;
uniform vec3 u_directionalLightPosition;
uniform vec3 u_cameraPosition;
uniform vec3 u_color;
uniform vec3 u_fogColor;
uniform vec3 u_wireframeColor;

uniform vec2 u_rippleOffset;

uniform float u_pointlightIntensities[MAX_LIGHT_COUNT];
uniform float u_directionalLightingIntensity;
uniform float u_specularShininess;
uniform float u_specularIntensity;
uniform float u_nearDistance;
uniform float u_farDistance;
uniform float u_opacity;
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogThickness;

uniform int u_pointlightShapes[MAX_LIGHT_COUNT];
uniform int u_lightCount;

uniform bool u_isReflectionsEnabled;
uniform bool u_isRefractionsEnabled;
uniform bool u_isWireframed;
uniform bool u_isDirectionalLightingEnabled;
uniform bool u_isFogEnabled;
uniform bool u_isSpecular;
uniform bool u_isReflective;
uniform bool u_isRefractive;
uniform bool u_hasReflectionMap;
uniform bool u_hasRefractionMap;
uniform bool u_hasDudvMap;
uniform bool u_hasNormalMap;

layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

vec4 calculateWaterColor();
vec3 calculateDirectionalLighting(vec3 normal);
vec3 calculateLights(vec3 normal);
vec3 calculateFog(vec3 color);
float calculateSpecularLighting(vec3 position, vec3 normal);
float convertDepthToPerspective(float depth);

void main()
{
	if(u_isWireframed)
	{
		o_primaryColor = vec4(u_wireframeColor, 1.0f);
		o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
		return;
	}

	vec4 waterColor = calculateWaterColor();

	vec3 primaryColor = vec3(0.0f);
	primaryColor += waterColor.rgb;
	primaryColor  = calculateFog(primaryColor);
	primaryColor  = clamp(primaryColor, vec3(0.0f), vec3(1.0f));
	primaryColor  = pow(primaryColor, vec3(1.0f / 2.2f));

	o_primaryColor   = vec4(primaryColor, waterColor.a);
	o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

vec4 calculateWaterColor()
{
	vec2 ndc = (f_clip.xy / f_clip.w);
	ndc /= 2.0f;
	ndc += 0.5f;

	vec2 defaultUv = f_uv;
	vec2 reflectionUv = vec2(ndc.x, -ndc.y);
	vec2 refractionUv = vec2(ndc.x, ndc.y);
	vec3 normal = vec3(0.0f, 1.0f, 0.0f);

	float opacity = 1.0f;
	if (u_isRefractionsEnabled && (u_opacity < 1.0f))
	{
		float depth = texture(u_depthMap, refractionUv).r;
		float floorDistance = convertDepthToPerspective(depth);
		float waterDistance = convertDepthToPerspective(gl_FragCoord.z);
		float waterDepth = (floorDistance - waterDistance);

		opacity = clamp(waterDepth / ((1.0f - u_opacity) * 10.0f), 0.0f, 1.0f);
	}

	if (u_hasDudvMap)
	{
		vec2 distortedMapUv = texture(u_dudvMap, (defaultUv + u_rippleOffset)).rg;
		distortedMapUv *= 0.1f;
		defaultUv += distortedMapUv;

		vec2 distortedNdcUv = texture(u_dudvMap, defaultUv).rg;
		distortedNdcUv *= 2.0f;
		distortedNdcUv -= 1.0f;
		distortedNdcUv *= 0.025f;

		reflectionUv += distortedNdcUv;
		refractionUv += distortedNdcUv;

		reflectionUv.x = clamp(reflectionUv.x, 0.001f, 0.999f);
		reflectionUv.y = clamp(reflectionUv.y, -0.999f, -0.001f);
		refractionUv.x = clamp(refractionUv.x, 0.001f, 0.999f);
		refractionUv.y = clamp(refractionUv.y, 0.001f, 0.999f);
	}

	if (u_hasNormalMap)
	{
		vec3 normalMapColor = texture(u_normalMap, defaultUv).rgb;
		normal = vec3(((normalMapColor.r * 2.0f) - 1.0f), normalMapColor.b, ((normalMapColor.g * 2.0f) - 1.0f));
		normal = normalize(normal);
	}

	vec3 finalColor;
	if (u_isReflectionsEnabled && u_hasReflectionMap && u_isReflective)
	{
		vec3 reflectionColor = texture(u_reflectionMap, reflectionUv).rgb;
		vec3 viewDirection = normalize(u_cameraPosition - f_position);
		float fresnelMixValue = dot(viewDirection, normal);

		finalColor = mix(reflectionColor, (reflectionColor * 0.05f), fresnelMixValue);
		finalColor *= u_color;
	}
	else if (u_isRefractionsEnabled && u_hasRefractionMap && u_isRefractive)
	{
		finalColor = texture(u_refractionMap, refractionUv).rgb;
		finalColor *= u_color;
	}
	else
	{
		finalColor = u_color;
	}

	if (u_isSpecular)
	{
		finalColor += calculateDirectionalLighting(normal);
		finalColor += calculateLights(normal);
	}

	return vec4(finalColor, opacity);
}

vec3 calculateLights(vec3 normal)
{
	vec3 result = vec3(0.0f);
		
	for (int i = 0; i < u_lightCount; i++)
	{
		vec3 lightDirection = normalize(u_pointlightPositions[i] - f_position);
		float diffuse = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(u_pointlightPositions[i], normal);

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

vec3 calculateDirectionalLighting(vec3 normal)
{
	if (u_isDirectionalLightingEnabled)
	{
		vec3 lightDirection = normalize(u_directionalLightPosition - f_position);
		vec3 viewDirection = normalize(f_position - u_cameraPosition);
		vec3 reflectDirection = reflect(normalize(lightDirection), normal);
		float specular = pow(clamp(dot(reflectDirection, viewDirection), 0.0f, 1.0f), u_specularShininess);
		specular *= u_directionalLightingIntensity;
		specular *= u_specularIntensity;
		vec3 result = vec3(specular);
		result *= u_directionalLightingColor;
		return result;
	}
	else
	{
		return vec3(0.0f);
	}
}

float calculateSpecularLighting(vec3 position, vec3 normal)
{
    if (u_isSpecular)
    {
        vec3 lightDirection   = normalize(position - f_position);
        vec3 viewDirection    = normalize(u_cameraPosition - f_position);
        vec3 halfWayDirection = normalize(lightDirection + viewDirection);
        float result          = pow(clamp(dot(normal, halfWayDirection), 0.0f, 1.0f), u_specularShininess);

        return (result * u_specularIntensity);
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
		float fragmentDistance = distance(f_position.xyz, u_cameraPosition);

		float distanceDifference = (u_fogMaxDistance - u_fogMinDistance);
		float distancePart = clamp(((fragmentDistance - u_fogMinDistance) / distanceDifference), 0.0f, 1.0f);
		float thickness = clamp(u_fogThickness, 0.0f, 1.0f);
		float mixValue = (distancePart * thickness);

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
    return ((2.0f * u_nearDistance * u_farDistance) / (u_farDistance + u_nearDistance - z * (u_farDistance - u_nearDistance)));
}