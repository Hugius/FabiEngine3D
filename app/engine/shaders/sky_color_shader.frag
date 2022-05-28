#version 460 core

#define GAMMA_VALUE 2.2f

in vec3 f_uv;

layout (location = 0) uniform samplerCube u_cubeMap;

uniform float u_lightness;

uniform vec3 u_wireframeColor;
uniform vec3 u_color;

uniform bool u_hasCubeMap;
uniform bool u_isWireframed;

layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

vec3 calculateCubeMapping()
{
	if(u_hasCubeMap)
	{
		vec4 cubeMapColor = texture(u_cubeMap, f_uv);

		cubeMapColor.rgb = pow(cubeMapColor.rgb, vec3(GAMMA_VALUE));

		return cubeMapColor.rgb;
	}
	else
	{
		return vec3(1.0f);
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
	vec3 cubeMapping = calculateCubeMapping();

	primaryColor += cubeMapping;
	primaryColor *= u_color;
	primaryColor *= u_lightness;
	primaryColor = clamp(primaryColor, vec3(0.0f), vec3(1.0f));
	primaryColor = pow(primaryColor, vec3(1.0f / GAMMA_VALUE));

	o_primaryColor = vec4(primaryColor, 1.0f);
	o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}