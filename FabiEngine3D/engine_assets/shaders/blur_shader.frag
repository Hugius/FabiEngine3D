#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
in vec2 f_pos;
in vec2 f_uv;

// Textures
uniform sampler2D u_sampler_diffuse;

// Float uniforms
uniform float u_radius;
uniform float u_intensity;

// Boolean uniforms
uniform bool u_horizontal;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Blur kernel
#define WEIGHT_AMOUNT 5
float kernel[WEIGHT_AMOUNT];

void main()
{
	kernel[0] = 0.227027f;
	kernel[1] = 0.1945946f;
	kernel[2] = 0.1216216f;
	kernel[3] = 0.054054f;
	kernel[4] = 0.016216f;

    vec2 tex_offset = (1.0 / textureSize(u_sampler_diffuse, 0)) * u_radius; 
    vec3 result = texture(u_sampler_diffuse, f_uv).rgb * kernel[0] * u_intensity;
    if(u_horizontal)
    {
        for (int i = 1; i < WEIGHT_AMOUNT; ++i)
        {
            result += texture(u_sampler_diffuse, f_uv + vec2(tex_offset.x * i, 0.0f)).rgb * kernel[i] * u_intensity;
           	result += texture(u_sampler_diffuse, f_uv - vec2(tex_offset.x * i, 0.0f)).rgb * kernel[i] * u_intensity;
        }
    }
    else
    {
        for (int i = 1; i < WEIGHT_AMOUNT; ++i)
        {
            result += texture(u_sampler_diffuse, f_uv + vec2(0.0f, tex_offset.y * i)).rgb * kernel[i] * u_intensity;
           	result += texture(u_sampler_diffuse, f_uv - vec2(0.0f, tex_offset.y * i)).rgb * kernel[i] * u_intensity;
        }
    }

    o_finalColor = vec4(result, 1.0f);
}