#version 460 core

#define KERNEL_SIZE 5

in vec2 f_worldSpacePos;
in vec2 f_uv;

layout (location = 0) uniform sampler2D u_diffuseMap;

uniform float u_intensity;

uniform bool u_isHorizontal;

layout (location = 0) out vec4 o_finalColor;

void main()
{
    float kernel[KERNEL_SIZE];

	kernel[0] = 0.227027f;
	kernel[1] = 0.1945946f;
	kernel[2] = 0.1216216f;
	kernel[3] = 0.054054f;
	kernel[4] = 0.016216f;

    vec2 uvOffset = (1.0f / textureSize(u_diffuseMap, 0));
    vec3 blurredColor = (texture(u_diffuseMap, f_uv).rgb * kernel[0] * u_intensity);

    if(u_isHorizontal)
    {
        for (int index = 1; index < KERNEL_SIZE; index++)
        {
            vec2 leftUv = f_uv - vec2(uvOffset.x * index, 0.0f);

            if(leftUv.x >= 0.0f && leftUv.x <= 1.0f)
            {
                blurredColor += (texture(u_diffuseMap, leftUv).rgb * kernel[index] * u_intensity);
            }
            else
            {
                blurredColor += (texture(u_diffuseMap, f_uv).rgb * kernel[index] * u_intensity);
            }

            vec2 rightUv = f_uv + vec2(uvOffset.x * index, 0.0f);

            if(rightUv.x >= 0.0f && rightUv.x <= 1.0f)
            {
                blurredColor += (texture(u_diffuseMap, rightUv).rgb * kernel[index] * u_intensity);
            }
            else
            {
                blurredColor += (texture(u_diffuseMap, f_uv).rgb * kernel[index] * u_intensity);
            }

        }
    }
    else
    {
        for (int index = 1; index < KERNEL_SIZE; index++)
        {
            vec2 bottomUv = f_uv - vec2(0.0f, uvOffset.y * index);

            if(bottomUv.y >= 0.0f && bottomUv.y <= 1.0f)
            {
                blurredColor += texture(u_diffuseMap, bottomUv).rgb * kernel[index] * u_intensity;
            }
            else
            {
                blurredColor += (texture(u_diffuseMap, f_uv).rgb * kernel[index] * u_intensity);
            }

            vec2 topUv = f_uv + vec2(0.0f, uvOffset.y * index);

            if(topUv.y >= 0.0f && topUv.y <= 1.0f)
            {
           	    blurredColor += texture(u_diffuseMap, topUv).rgb * kernel[index] * u_intensity;
            }
            else
            {
                blurredColor += (texture(u_diffuseMap, f_uv).rgb * kernel[index] * u_intensity);
            }

        }
    }

    o_finalColor = vec4(blurredColor, 1.0f);
}