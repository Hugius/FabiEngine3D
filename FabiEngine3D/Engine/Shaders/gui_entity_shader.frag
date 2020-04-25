#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

in vec2 f_uv;

uniform sampler2D u_sampler_diffuse;
uniform vec3      u_color;
uniform vec2 	  u_windowSize;
uniform vec2 	  u_minPosition;
uniform vec2 	  u_maxPosition;
uniform float 	  u_alpha;
uniform float     u_nearZ;
uniform float     u_farZ;
uniform bool      u_isDepthEntity;
uniform bool      u_noTexture;

// Out variables
layout (location = 0) out vec4 o_finalColor;

float convertDepthToColor(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * u_nearZ * u_farZ) / (u_farZ + u_nearZ - z * (u_farZ - u_nearZ));
}

void main()
{
	vec2 normalizedPos = gl_FragCoord.xy / u_windowSize;
	vec2 ndcPos = (normalizedPos * 2.0f) - vec2(1.0f);
	if(ndcPos.x > u_maxPosition.x || ndcPos.y > u_maxPosition.y || ndcPos.x < u_minPosition.x || ndcPos.y < u_minPosition.y)
	{
		discard;
	}

	if(u_isDepthEntity)
	{
		float depth = texture(u_sampler_diffuse, f_uv).r;
		o_finalColor  = vec4(vec3((convertDepthToColor(depth) / u_farZ)), 1.0f);
		//o_finalColor  = vec4(vec3(depth), 1.0f);
	}
	else
	{
		if(u_noTexture)
		{
			o_finalColor = vec4(u_color, u_alpha);
		}
		else
		{
			vec4 texColor = texture(u_sampler_diffuse, f_uv);
			o_finalColor = vec4(texColor.rgb * u_color, texColor.a * u_alpha);
		}
	}
}