#version 460 core

#define GAMMA_VALUE 2.2f

in vec3 f_worldSpacePos;
in vec2 f_uv;

layout (location = 0) uniform sampler2D u_diffuseMap;
layout (location = 1) uniform sampler2D u_emissionMap;

uniform vec3 u_color;
uniform vec3 u_wireframeColor;
uniform vec3 u_cameraPosition;
uniform vec3 u_fogColor;

uniform float u_minFogDistance;
uniform float u_maxFogDistance;
uniform float u_fogThickness;
uniform float u_lightness;
uniform float u_minAlpha;
uniform float u_opacity;
uniform float u_emissionIntensity;

uniform bool u_isWireframed;
uniform bool u_isFogEnabled;
uniform bool u_hasDiffuseMap;
uniform bool u_isBright;
uniform bool u_hasEmissionMap;

layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

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

vec3 calculateFog(vec3 color)
{
	if(u_isFogEnabled)
	{
        float fragmentDistance = distance(f_worldSpacePos.xyz, u_cameraPosition);
		float distanceDifference = (u_maxFogDistance - u_minFogDistance);
		float distancePart = clamp(((fragmentDistance - u_minFogDistance) / distanceDifference), 0.0f, 1.0f);
		float mixValue = (distancePart * u_fogThickness);

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

	primaryColor += diffuseMapping;
	primaryColor += emissionMapping;
	primaryColor *= u_color;
	primaryColor *= u_lightness;
	primaryColor = calculateFog(primaryColor);
	primaryColor = clamp(primaryColor, vec3(0.0f), vec3(1.0f));
	primaryColor = pow(primaryColor, vec3(1.0f / GAMMA_VALUE));

	o_primaryColor = vec4(primaryColor, u_opacity);
	o_secondaryColor = vec4((((emissionMapping != vec3(0.0f)) || u_isBright) ? primaryColor : vec3(0.0f)), 1.0f);
}