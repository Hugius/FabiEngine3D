#version 460 core

#define GAMMA_VALUE 2.2f

in vec4 f_clipSpacePos;
in vec3 f_worldSpacePos;
in vec2 f_uv;

layout (location = 0) uniform sampler2D u_reflectionMap;
layout (location = 1) uniform sampler2D u_refractionMap;
layout (location = 2) uniform sampler2D u_edgeMap;
layout (location = 3) uniform sampler2D u_dudvMap;
layout (location = 4) uniform sampler2D u_normalMap;

uniform vec3 u_ambientLightingColor;
uniform vec3 u_directionalLightingColor;
uniform vec3 u_directionalLightingPosition;
uniform vec3 u_cameraPosition;
uniform vec3 u_color;
uniform vec3 u_fogColor;
uniform vec3 u_wireframeColor;

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

layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

vec4 calculateWaterColor();
vec3 calculateAmbientLighting();
vec3 calculateDirectionalLighting(vec3 normal);
vec3 calculateFog(vec3 color);

float calculateSpecularLighting(vec3 lightDirection, vec3 normal);
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
	primaryColor = calculateFog(primaryColor);
	primaryColor = clamp(primaryColor, vec3(0.0f), vec3(1.0f));
	primaryColor = pow(primaryColor, vec3(1.0f / GAMMA_VALUE));

	o_primaryColor = vec4(primaryColor, waterColor.a);
	o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

vec4 calculateWaterColor()
{
	vec2 ndc = (f_clipSpacePos.xy / f_clipSpacePos.w);

	ndc /= 2.0f;
	ndc += 0.5f;

	vec2 defaultUv = f_uv;
	vec2 reflectionUv = vec2(ndc.x, -ndc.y);
	vec2 refractionUv = vec2(ndc.x, ndc.y);
	vec3 normal = vec3(0.0f, 1.0f, 0.0f);

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

	if(u_hasNormalMap)
	{
		vec3 normalMapColor = texture(u_normalMap, defaultUv).rgb;

		normal = vec3(((normalMapColor.r * 2.0f) - 1.0f), normalMapColor.b, ((normalMapColor.g * 2.0f) - 1.0f));
		normal = normalize(normal);
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

	finalColor *= (calculateAmbientLighting() + calculateDirectionalLighting(normal));

	return vec4(finalColor, opacity);
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
		vec3 lightDirection = normalize(u_directionalLightingPosition - f_worldSpacePos);

		float diffuse = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(lightDirection, normal);

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

float calculateSpecularLighting(vec3 lightDirection, vec3 normal)
{
    if(u_isSpecular && (u_cameraPosition.y > f_worldSpacePos.y))
    {
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

float convertDepthToPerspective(float depth)
{
    float z = ((depth * 2.0f) - 1.0f);

    return ((2.0f * u_cameraNear * u_cameraFar) / (u_cameraFar + u_cameraNear - z * (u_cameraFar - u_cameraNear)));
}