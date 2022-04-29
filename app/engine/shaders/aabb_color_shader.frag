#version 460 core

in vec3 f_worldSpacePos;

uniform vec3 u_cameraPosition;
uniform vec3 u_color;
uniform vec3 u_fogColor;

uniform float u_minFogDistance;
uniform float u_maxFogDistance;
uniform float u_fogThickness;

uniform bool u_isFogEnabled;

layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

vec3 calculateFog(vec3 color);

void main()
{
	vec3 primaryColor = u_color;

	primaryColor = calculateFog(primaryColor);

	primaryColor = pow(primaryColor, vec3(1.0f / 2.2f));

	o_primaryColor = vec4(primaryColor, 1.0f);
	o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
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