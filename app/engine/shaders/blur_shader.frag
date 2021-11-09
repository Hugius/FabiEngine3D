#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// Constants variables
#define KERNEL_SIZE 5

// In variables
in vec2 f_position;
in vec2 f_uv;

// Textures
layout (location = 0) uniform sampler2D u_diffuseMap;

// Float uniforms
uniform float u_intensity;

// Boolean uniforms
uniform bool u_isHorizontal;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Process fragment
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
    if (u_isHorizontal)
    {
        for (int i = 1; i < KERNEL_SIZE; i++)
        {
            // Left texel
            vec2 leftUV = f_uv - vec2(uvOffset.x * i, 0.0f);
            if (leftUV.x >= 0.0f && leftUV.x <= 1.0f)
            {
                result += (texture(u_diffuseMap, leftUV).rgb * kernel[i] * u_intensity);
            }
            else
            {
                result += (texture(u_diffuseMap, f_uv).rgb * kernel[i] * u_intensity);
            }

            // Right texel
            vec2 rightUV = f_uv + vec2(uvOffset.x * i, 0.0f);
            if (rightUV.x >= 0.0f && rightUV.x <= 1.0f)
            {
                result += (texture(u_diffuseMap, rightUV).rgb * kernel[i] * u_intensity);
            }
            else
            {
                result += (texture(u_diffuseMap, f_uv).rgb * kernel[i] * u_intensity);
            }

        }
    }
    else
    {
        for (int i = 1; i < KERNEL_SIZE; i++)
        {
            // Bottom texel
            vec2 bottomUV = f_uv - vec2(0.0f, uvOffset.y * i);
            if (bottomUV.y >= 0.0f && bottomUV.y <= 1.0f)
            {
                result += texture(u_diffuseMap, bottomUV).rgb * kernel[i] * u_intensity;
            }
            else
            {
                result += (texture(u_diffuseMap, f_uv).rgb * kernel[i] * u_intensity);
            }

            // Top texel
            vec2 topUV = f_uv + vec2(0.0f, uvOffset.y * i);
            if (topUV.y >= 0.0f && topUV.y <= 1.0f)
            {
           	    result += texture(u_diffuseMap, topUV).rgb * kernel[i] * u_intensity;
            }
             else
            {
                result += (texture(u_diffuseMap, f_uv).rgb * kernel[i] * u_intensity);
            }

        }
    }

    // Set final color
    o_finalColor = vec4(result, 1.0f);
}