#version 460 core

in vec2 f_uv;

layout (location = 0) uniform sampler2D u_diffuseMap;

uniform vec3 u_color;
uniform vec2 u_windowSize;
uniform vec2 u_minPosition;
uniform vec2 u_maxPosition;
uniform vec3 u_wireframeColor;

uniform float u_transparency;
uniform float u_nearDistance;
uniform float u_farDistance;

uniform bool u_isPerspectiveDepthEntity;
uniform bool u_hasDiffuseMap;
uniform bool u_isWireframed;

layout (location = 0) out vec4 o_finalColor;

vec4 calculateDiffuseMapping();
float convertDepthToPerspective(float depth);

void main()
{
	if(u_isWireframed)
	{
		o_finalColor = vec4(u_wireframeColor, 1.0f);
		return;
	}

	vec2 normalizedPosition = (gl_FragCoord.xy / u_windowSize);
	vec2 ndcPosition = ((normalizedPosition * 2.0f) - vec2(1.0f));

	if ((ndcPosition.x > u_maxPosition.x) || (ndcPosition.y > u_maxPosition.y) || (ndcPosition.x < u_minPosition.x) || (ndcPosition.y < u_minPosition.y))
	{
		discard;
	}

	if (u_isPerspectiveDepthEntity)
	{
		float depth = texture(u_diffuseMap, f_uv).r;
		vec3 depthColor = vec3((convertDepthToPerspective(depth) / u_farDistance));
		depthColor = pow(depthColor, vec3(1.0f / 2.2f));

		o_finalColor = vec4(depthColor, 1.0f);
	}
	else
	{
		if (u_hasDiffuseMap)
		{
			vec4 diffuseMapping = calculateDiffuseMapping();
			diffuseMapping.rgb *= u_color;
			diffuseMapping.rgb  = pow(diffuseMapping.rgb, vec3(1.0f / 2.2f));
			diffuseMapping.a   *= u_transparency;

			o_finalColor = diffuseMapping;
		}
		else
		{
			vec3 color = pow(u_color, vec3(1.0f / 2.2f));

			o_finalColor = vec4(color, u_transparency);
		}
	}
}

float convertDepthToPerspective(float depth)
{
    float z = ((depth * 2.0f) - 1.0f);

    return ((2.0f * u_nearDistance * u_farDistance) / (u_farDistance + u_nearDistance - z * (u_farDistance - u_nearDistance)));
}

vec4 calculateDiffuseMapping()
{
	if (u_hasDiffuseMap)
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