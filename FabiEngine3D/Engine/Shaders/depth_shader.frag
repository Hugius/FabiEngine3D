#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
in vec2 f_uv;

// Textures
layout(location = 0) uniform sampler2D u_sampler_diffuseMap;

// Boolean uniforms
uniform bool u_isAlphaObject;

// Calculate final fragment color
void main()
{
	vec4 texColor = texture(u_sampler_diffuseMap, f_uv);

	if(u_isAlphaObject)
	{
		if(texColor.a <= 0.25f)
		{
			discard;
		}
	}

	// Set final depth
	gl_FragDepth = gl_FragCoord.z;
}