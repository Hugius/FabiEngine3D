#version 330 core
#extension GL_ARB_explicit_uniform_location : require

in vec2 f_uv;

layout (location = 0) uniform sampler2D u_worldMap;
layout (location = 1) uniform sampler2D u_motionBlurMap;

uniform float u_mixValue;

uniform bool u_isMotionBlurEnabled;

layout (location = 0) out vec4 o_finalColor;

void main()
{
    // Validate
	if (!u_isMotionBlurEnabled)
	{
        o_finalColor.rgb = texture(u_worldMap, f_uv).rgb;
		o_finalColor.a = 1.0f;
		return;
    }

	// Texture mapping
	vec3 world = texture(u_worldMap, f_uv).rgb;
	vec3 motion = texture(u_motionBlurMap, f_uv).rgb;

	// Final color
	o_finalColor.rgb = mix(world, motion, clamp(u_mixValue, 0.0f, 1.0f));
	o_finalColor.a = 1.0f;
}