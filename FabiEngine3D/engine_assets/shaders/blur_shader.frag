#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
in vec2 f_pos;
in vec2 f_uv;

// Textures
uniform sampler2D u_diffuseMap;

// Float uniforms
uniform float u_intensity;

// Boolean uniforms
uniform bool u_isHorizontal;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Local variables
#define KERNEL_SIZE 5

void main()
{
    // Compose blur kernel
    float kernel[KERNEL_SIZE];
	kernel[0] = 0.227027f;
	kernel[1] = 0.1945946f;
	kernel[2] = 0.1216216f;
	kernel[3] = 0.054054f;
	kernel[4] = 0.016216f;

    // Calculate UV offset
    vec2 uvOffset = (1.0f / textureSize(u_diffuseMap, 0));

    // Calculate center pixel
    vec3 result = (texture(u_diffuseMap, f_uv).rgb * kernel[0] * u_intensity);

    // Determine blur direction
    if(u_isHorizontal)
    {
        for (int i = 1; i < KERNEL_SIZE; i++)
        {
            result += (texture(u_diffuseMap, f_uv + vec2(uvOffset.x * i, 0.0f)).rgb * kernel[i] * u_intensity);
           	result += (texture(u_diffuseMap, f_uv - vec2(uvOffset.x * i, 0.0f)).rgb * kernel[i] * u_intensity);
        }
    }
    else
    {
        for (int i = 1; i < KERNEL_SIZE; i++)
        {
            result += texture(u_diffuseMap, f_uv + vec2(0.0f, uvOffset.y * i)).rgb * kernel[i] * u_intensity;
           	result += texture(u_diffuseMap, f_uv - vec2(0.0f, uvOffset.y * i)).rgb * kernel[i] * u_intensity;
        }
    }

    // Set final color
    o_finalColor = vec4(result, 1.0f);
}