#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
in vec2 f_uv;

// Textures
uniform sampler2D u_sampler_scene;
uniform sampler2D u_sampler_motionblur;

// Uniforms
uniform float u_mixValue;

// Out variables
layout (location = 0) out vec4 o_finalColor;

void main()
{
	vec4 scene = texture(u_sampler_scene, f_uv);
	vec4 motion = texture(u_sampler_motionblur, f_uv);
	float mixValue = clamp(u_mixValue, 0.0f, 1.0f);
	o_finalColor.rgb = mix(scene.rgb, motion.rgb, mixValue);
	o_finalColor.a = 1.0f;
}