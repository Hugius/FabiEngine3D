#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
in vec2 f_uv;

// Textures
layout (location = 0) uniform sampler2D u_sceneMap;
layout (location = 1) uniform sampler2D u_bloomMap;

// Boolean uniforms
uniform bool u_isBloomEnabled;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Process fragment
void main()
{
    // Validate
	if (!u_isBloomEnabled)
	{
        o_finalColor.rgb = texture(u_sceneMap, f_uv).rgb;
		o_finalColor.a = 1.0f;
		return;
    }

	// Texture mapping
	vec3 sceneColor = texture(u_sceneMap, f_uv).rgb;
	vec3 bloomColor = texture(u_bloomMap, f_uv).rgb;

	// Final color
    o_finalColor.rgb = (sceneColor + bloomColor);
	o_finalColor.a = 1.0f;
}