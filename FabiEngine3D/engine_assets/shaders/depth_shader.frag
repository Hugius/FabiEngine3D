#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
in vec2 f_uv;

// Textures
layout (location = 0) uniform sampler2D u_diffuseMap;

// Float uniforms
uniform float u_minAlpha;

// Boolean uniforms
uniform bool u_isAlphaObject;

// Process fragment
void main()
{
	vec4 diffuseMapColor = texture(u_diffuseMap, f_uv);

	if(u_isAlphaObject)
	{
		if(diffuseMapColor.a < u_minAlpha)
		{
			discard;
		}
	}

	// Set final depth
	gl_FragDepth = gl_FragCoord.z;
}