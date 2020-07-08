#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

in vec3 f_uv;

layout (location = 0) out vec4 o_finalColor;

uniform samplerCube u_sampler_day;
uniform samplerCube u_sampler_night;
uniform float       u_mixValue;
uniform float       u_lightness;
uniform vec3		u_color;

void main()
{
	vec4 day   = texture(u_sampler_day, f_uv);
	vec4 night = texture(u_sampler_night, f_uv);
	o_finalColor = mix(day, night, u_mixValue);
	o_finalColor.rgb *= u_color;
	o_finalColor.rgb *= u_lightness;
	o_finalColor.a = 1.0f;
}