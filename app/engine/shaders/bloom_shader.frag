#version 460 core

in vec2 f_uv;

layout (location = 0) uniform sampler2D u_sceneMap;
layout (location = 1) uniform sampler2D u_bloomMap;

uniform bool u_isBloomEnabled;

layout (location = 0) out vec4 o_finalColor;

void main()
{
	if(!u_isBloomEnabled)
	{
        o_finalColor.rgb = texture(u_sceneMap, f_uv).rgb;
		o_finalColor.a = 1.0f;

		return;
    }

	vec3 worldColor = texture(u_sceneMap, f_uv).rgb;
	vec3 bloomColor = texture(u_bloomMap, f_uv).rgb;

    o_finalColor.rgb = (worldColor + bloomColor);
	o_finalColor.a = 1.0f;
}