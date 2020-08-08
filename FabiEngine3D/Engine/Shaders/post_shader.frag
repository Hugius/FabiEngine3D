#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
in vec2 f_uv;

// Textures
layout(location = 0) uniform sampler2D u_sampler_scene;
layout(location = 1) uniform sampler2D u_sampler_bloom;
layout(location = 2) uniform sampler2D u_sampler_depth;
layout(location = 3) uniform sampler2D u_sampler_blur;
layout(location = 4) uniform sampler2D u_sampler_flare;

// Float uniforms
uniform float u_nearZ;
uniform float u_farZ;
uniform float u_dofMinDistance;
uniform float u_lensFlareAlpha;

// Boolean uniforms
uniform bool u_bloomEnabled;
uniform bool u_dofEnabled;
uniform bool u_lensFlareEnabled;

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
	float depth         = texture(u_sampler_depth, f_uv).r;
	float fragmentDepth = convertDepthToColor(depth) / u_farZ;
	vec3 sceneColor     = texture(u_sampler_scene, f_uv).rgb;
	vec3 bloomColor     = texture(u_sampler_bloom, f_uv).rgb;
	vec3 blurColor      = texture(u_sampler_blur, f_uv).rgb;
    vec3 flareColor     = texture(u_sampler_flare, f_uv).rgb;

    // Default scene
    o_finalColor.rgb = sceneColor;

	// Bloom
	o_finalColor.rgb += (bloomColor * float(u_bloomEnabled));
	
	// DOF
	if(u_dofEnabled)
	{
		if((fragmentDepth * u_farZ) > u_dofMinDistance)
		{
			o_finalColor.rgb = blurColor + bloomColor;
		}
	}

    // Lens flare
    o_finalColor.rgb += (flareColor * u_lensFlareAlpha * float(u_lensFlareEnabled));

	// Alpha value
	o_finalColor.a = 1.0f;
}