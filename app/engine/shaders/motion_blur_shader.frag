#version 460 core

in vec2 f_uv;

layout (location = 0) uniform sampler2D u_sceneMap;
layout (location = 1) uniform sampler2D u_motionBlurMap;

uniform float u_mixValue;

uniform bool u_isMotionBlurEnabled;

layout (location = 0) out vec4 o_finalColor;

void main()
{
	if(!u_isMotionBlurEnabled)
	{
        o_finalColor.rgb = texture(u_sceneMap, f_uv).rgb;
		o_finalColor.a = 1.0f;

		return;
    }

	vec3 worldColor = texture(u_sceneMap, f_uv).rgb;
	vec3 motionColor = texture(u_motionBlurMap, f_uv).rgb;

	o_finalColor.rgb = mix(worldColor, motionColor, clamp(u_mixValue, 0.0f, 1.0f));
	o_finalColor.a = 1.0f;
}