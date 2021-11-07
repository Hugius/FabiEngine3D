#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
in vec2 f_uv;

// Textures
layout (location = 0) uniform sampler2D u_diffuseMap;

// Vector uniforms
uniform vec3 u_color;
uniform vec2 u_windowSize;
uniform vec2 u_minPosition;
uniform vec2 u_maxPosition;

// Float uniforms
uniform float u_alpha;
uniform float u_nearDistance;
uniform float u_farDistance;

// Boolean uniforms
uniform bool u_isPerspectiveDepthEntity;
uniform bool u_hasDiffuseMap;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Functions
float convertDepthToPerspective(float depth);

// Process fragment
void main()
{
	// Calculate fragment position and convert to NDC
	vec2 normalizedPosition = (gl_FragCoord.xy / u_windowSize);
	vec2 ndcPosition = ((normalizedPosition * 2.0f) - vec2(1.0f));

	// Determine if fragment is outside of maximum bounds
	if ((ndcPosition.x > u_maxPosition.x) || (ndcPosition.y > u_maxPosition.y) || (ndcPosition.x < u_minPosition.x) || (ndcPosition.y < u_minPosition.y))
	{
		discard;
	}

	if (u_isPerspectiveDepthEntity) // Visualize depth map
	{
		float depth = texture(u_diffuseMap, f_uv).r;
		o_finalColor = vec4(vec3((convertDepthToPerspective(depth) / u_farDistance)), 1.0f);
		o_finalColor.rgb = pow(o_finalColor.rgb, vec3(1.0f / 2.2f));
	}
	else
	{
		if (u_hasDiffuseMap) // Render diffuse map
		{
			vec4 diffuseMapColor = texture(u_diffuseMap, f_uv);
			diffuseMapColor.rgb  = pow(diffuseMapColor.rgb, vec3(2.2f));
			diffuseMapColor.rgb *= u_color;
			diffuseMapColor.rgb  = pow(diffuseMapColor.rgb, vec3(1.0f / 2.2f));
			diffuseMapColor.a   *= u_alpha;
			o_finalColor = diffuseMapColor;
		}
		else // Render color only
		{
			o_finalColor = vec4(u_color, u_alpha);
			o_finalColor.rgb = pow(o_finalColor.rgb, vec3(1.0f / 2.2f));
		}
	}
}

float convertDepthToPerspective(float depth)
{
    float z = ((depth * 2.0f) - 1.0f);
    return ((2.0f * u_nearDistance * u_farDistance) / (u_farDistance + u_nearDistance - z * (u_farDistance - u_nearDistance)));
}