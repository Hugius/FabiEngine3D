#version 330 core
#extension GL_ARB_explicit_uniform_location : require

in vec2 f_uv;

layout (location = 0) uniform sampler2D u_diffuseMap;

uniform float u_minTextureTransparency;

void main()
{
	vec4 diffuseMapColor = texture(u_diffuseMap, f_uv);

	if (diffuseMapColor.a < u_minTextureTransparency) 
	{
		discard;
	}

	gl_FragDepth = gl_FragCoord.z;
} 