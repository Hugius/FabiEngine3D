#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
in vec2 f_uv;

// Textures
uniform sampler2D u_sampler_diffuseMap;

// Boolean uniforms
uniform bool u_isAlphaObject;

void main()
{
	// Texture sampling for possible alpha
	vec4 texelColor = texture(u_sampler_diffuseMap, f_uv);

	if(u_isAlphaObject)
	{
		if(texelColor.a < 0.25f) 
		{
			discard;
		}
	}
}  