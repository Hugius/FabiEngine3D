#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
in vec2 f_uv;

// Textures
layout (location = 0) uniform sampler2D u_sceneMap;
layout (location = 1) uniform sampler2D u_motionBlurMap;

// Float uniforms
uniform float u_mixValue;

// Boolean uniforms
uniform bool u_isMotionBlurEnabled;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Process fragment
void main()
{
    // Validate
	if (!u_isMotionBlurEnabled)
	{
        o_finalColor.rgb = texture(u_sceneMap, f_uv).rgb;
		o_finalColor.a = 1.0f;
		return;
    }

	// Texture mapping
	vec3 scene = texture(u_sceneMap, f_uv).rgb;
	vec3 motion = texture(u_motionBlurMap, f_uv).rgb;

	// Final color
	o_finalColor.rgb = mix(scene, motion, clamp(u_mixValue, 0.0f, 1.0f));
	o_finalColor.a = 1.0f;
}