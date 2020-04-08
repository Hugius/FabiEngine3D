#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

in vec2 f_uv;

uniform sampler2D u_sampler_diffuseMap;
uniform bool      u_alphaObject;

void main()
{
	// Texture sampling for possible alpha
	vec4 texelColor = texture(u_sampler_diffuseMap, f_uv);

	if(u_alphaObject)
	{
		if(texelColor.a <= 0.25f) 
		{
			discard;
		}
	}
}  