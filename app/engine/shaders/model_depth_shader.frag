#version 460 core

in vec2 f_uv;

layout (location = 0) uniform sampler2D u_diffuseMap;

uniform float u_minAlpha;

void main()
{
	vec4 diffuseMapColor = texture(u_diffuseMap, f_uv);

	if(diffuseMapColor.a < u_minAlpha)
	{
		discard;
	}

	gl_FragDepth = gl_FragCoord.z;
}