#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
in vec2 f_uv;

// Textures
layout (location = 0) uniform sampler2D u_diffuseMap;

// Float uniforms
uniform float u_minTextureAlpha;

// Process fragment
void main()
{
	// Calculate diffuse map color
	vec4 diffuseMapColor = texture(u_diffuseMap, f_uv);

	// Check if transparent
	if (diffuseMapColor.a < u_minTextureAlpha)
	{
		discard;
	}

	// Set final depth
	gl_FragDepth = gl_FragCoord.z;
}