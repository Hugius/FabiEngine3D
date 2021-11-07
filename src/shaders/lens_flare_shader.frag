#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
in vec2 f_uv;
in float f_flareVisibility;

// Textures
layout (location = 1) uniform sampler2D u_sceneMap;
layout (location = 2) uniform sampler2D u_flareMap;

// Float uniforms
uniform float u_lensFlareIntensity;
uniform float u_lensFlareAlpha;

// Boolean uniforms
uniform bool u_isLensFlareEnabled;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Process fragment
void main()
{
    // Validate
	if (!u_isLensFlareEnabled)
	{
        o_finalColor.rgb = texture(u_sceneMap, f_uv).rgb;
		o_finalColor.a = 1.0f;
		return;
    }

    // Texture mapping
    vec3 sceneColor = texture(u_sceneMap, f_uv).rgb;
    vec3 flareColor = texture(u_flareMap, vec2(f_uv.x, -f_uv.y)).rgb;

    // Final color
    o_finalColor.rgb = sceneColor;
    o_finalColor.rgb += (flareColor * u_lensFlareAlpha * u_lensFlareIntensity * f_flareVisibility);
	o_finalColor.a = 1.0f;
}