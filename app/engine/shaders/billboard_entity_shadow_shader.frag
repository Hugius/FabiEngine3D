#version 330 core
#extension GL_ARB_explicit_uniform_location : require

in vec2 f_uv;

layout (location = 0) uniform sampler2D u_diffuseMap;

uniform float u_minTextureTransparency;

void main()
{
	// Calculate diffuse map color
	vec4 diffuseMapColor = texture(u_diffuseMap, f_uv);

	// Check if transparent
	if (diffuseMapColor.a < u_minTextureTransparency)
	{
		discard;
	}

	// Set final depth
	gl_FragDepth = gl_FragCoord.z;
}