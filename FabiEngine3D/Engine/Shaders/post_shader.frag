#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
in vec2 f_uv;

// Textures
layout(location = 0) uniform sampler2D u_sampler_scene;
layout(location = 1) uniform sampler2D u_sampler_bloom;
layout(location = 2) uniform sampler2D u_sampler_dof;
layout(location = 3) uniform sampler2D u_sampler_blur;

// Float uniforms
uniform float u_nearZ;
uniform float u_farZ;
uniform float u_dofMinDistance;

// Boolean uniforms
uniform bool  u_bloomEnabled;
uniform bool  u_dofEnabled;

// Out variables
layout (location = 0) out vec4 o_finalColor;

float convertDepthToColor(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * u_nearZ * u_farZ) / (u_farZ + u_nearZ - z * (u_farZ - u_nearZ));
}

void main()
{
	// Texture mapping
	float depth         = texture(u_sampler_dof, f_uv).r;
	float fragmentDepth = convertDepthToColor(depth) / u_farZ;
	vec3 sceneColor     = texture(u_sampler_scene, f_uv).rgb;
	vec3 bloomColor     = texture(u_sampler_bloom, f_uv).rgb;
	vec3 blurColor      = texture(u_sampler_blur, f_uv).rgb;

	// Bloom
	if(u_bloomEnabled)
	{
		o_finalColor.rgb = sceneColor + bloomColor;
	}
	else
	{
		o_finalColor.rgb = sceneColor;
	}
	
	// DOF
	if(u_dofEnabled)
	{
		if(fragmentDepth > u_dofMinDistance)
		{
			o_finalColor.rgb = blurColor + bloomColor;
		}
	}

	// Alpha value
	o_finalColor.a = 1.0f;
}