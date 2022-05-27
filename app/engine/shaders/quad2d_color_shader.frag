#version 460 core

#define GAMMA_VALUE 2.2f

in vec2 f_uv;

layout (location = 0) uniform sampler2D u_diffuseMap;

uniform vec3 u_color;
uniform vec3 u_wireframeColor;

uniform float u_opacity;

uniform bool u_hasDiffuseMap;
uniform bool u_isWireframed;

layout (location = 0) out vec4 o_finalColor;

vec4 calculateDiffuseMapping()
{
	if(u_hasDiffuseMap)
	{
		vec4 diffuseMapColor = texture(u_diffuseMap, f_uv);

		diffuseMapColor.rgb = pow(diffuseMapColor.rgb, vec3(GAMMA_VALUE));

		return diffuseMapColor;
	}
	else
	{
		return vec4(1.0f);
	}
}

void main()
{
	if(u_isWireframed)
	{
		o_finalColor = vec4(u_wireframeColor, 1.0f);

		return;
	}

	vec4 diffuseMapping = calculateDiffuseMapping();
	vec4 primaryColor = vec4(0.0f);

	primaryColor.rgb += diffuseMapping.rgb;
	primaryColor.rgb *= u_color;
	primaryColor.rgb = clamp(primaryColor.rgb, vec3(0.0f), vec3(1.0f));
	primaryColor.rgb = pow(primaryColor.rgb, vec3(1.0f / GAMMA_VALUE));
	primaryColor.a += diffuseMapping.a;
	primaryColor.a *= u_opacity;

	o_finalColor = primaryColor;
}