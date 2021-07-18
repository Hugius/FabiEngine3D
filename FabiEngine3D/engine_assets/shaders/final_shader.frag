#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
in vec2 f_uv;

// Textures
layout (location = 0) uniform sampler2D u_sceneMap;
layout (location = 1) uniform sampler2D u_motionBlurMap;

// Uniforms
uniform float u_mixValue;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Process fragment
void main()
{
	vec4 scene = texture(u_sceneMap, f_uv);
	vec4 motion = texture(u_motionBlurMap, f_uv);
	float mixValue = clamp(u_mixValue, 0.0f, 1.0f);
	o_finalColor.rgb = mix(scene.rgb, motion.rgb, mixValue);
	o_finalColor.a = 1.0f;
}