#version 460 core

in vec2 f_uv;

layout (location = 0) uniform sampler2D u_diffuseMap;

uniform vec3 u_color;
uniform vec2 u_windowSize;
uniform vec2 u_minClippingPosition;
uniform vec2 u_maxClippingPosition;
uniform vec3 u_wireframeColor;

uniform float u_opacity;

uniform bool u_hasDiffuseMap;
uniform bool u_isWireframed;

layout (location = 0) out vec4 o_finalColor;

vec4 calculateDiffuseMapping();

void main()
{
	if(u_isWireframed)
	{
		o_finalColor = vec4(u_wireframeColor, 1.0f);
		return;
	}

	vec2 normalizedPosition = (gl_FragCoord.xy / u_windowSize);
	vec2 ndcPosition = ((normalizedPosition * 2.0f) - vec2(1.0f));

	if((ndcPosition.x > u_maxClippingPosition.x) || (ndcPosition.y > u_maxClippingPosition.y) || (ndcPosition.x < u_minClippingPosition.x) || (ndcPosition.y < u_minClippingPosition.y))
	{
		discard;
	}

	if(u_hasDiffuseMap)
	{
		vec4 diffuseMapping = calculateDiffuseMapping();
		diffuseMapping.rgb *= u_color;
		diffuseMapping.rgb  = pow(diffuseMapping.rgb, vec3(1.0f / 2.2f));
		diffuseMapping.a   *= u_opacity;

		o_finalColor = diffuseMapping;
	}
	else
	{
		vec3 color = pow(u_color, vec3(1.0f / 2.2f));

		o_finalColor = vec4(color, u_opacity);
	}
}

vec4 calculateDiffuseMapping()
{
	if(u_hasDiffuseMap)
	{
		vec4 diffuseMapColor = texture(u_diffuseMap, f_uv);
		diffuseMapColor.rgb = pow(diffuseMapColor.rgb, vec3(2.2f));

		return diffuseMapColor;
	}
	else
	{
		return vec4(1.0f);
	}
}