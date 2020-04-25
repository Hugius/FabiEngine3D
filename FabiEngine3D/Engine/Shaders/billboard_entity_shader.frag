#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
in vec2 f_uv;

// Textures
layout(location = 0) uniform sampler2D   u_sampler_diffuseMap;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Uniforms
uniform bool u_isAlphaObject;
uniform vec3 u_color;

// Calculate final fragment color
void main()
{
	// Calculating the texel color
	vec4 texColor = texture(u_sampler_diffuseMap, f_uv);

	// Removing white alpha background
	if(u_isAlphaObject)
	{
		if(texColor.a <= 0.1f)
		{
			discard;
		}
	}

	o_finalColor = vec4(texColor.rgb * u_color, texColor.a);
}