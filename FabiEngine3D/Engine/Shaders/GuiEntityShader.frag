#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

in vec2 f_uv;

uniform sampler2D u_sampler_diffuse;
uniform vec3      u_color;
uniform float     u_nearZ;
uniform float     u_farZ;
uniform bool      u_isDepthEntity;

// Out variables
layout (location = 0) out vec4 o_finalColor;

float convertDepthToColor(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * u_nearZ * u_farZ) / (u_farZ + u_nearZ - z * (u_farZ - u_nearZ));
}

void main()
{
	if(u_isDepthEntity)
	{
		float depth = texture(u_sampler_diffuse, f_uv).r;
		o_finalColor  = vec4(vec3((convertDepthToColor(depth) / u_farZ)), 1.0f);
		//o_finalColor  = vec4(vec3(depth), 1.0f);
	}
	else
	{
		vec4 texColor = texture(u_sampler_diffuse, f_uv);
		o_finalColor = vec4(texColor.rgb * u_color, texColor.a);
	}
}