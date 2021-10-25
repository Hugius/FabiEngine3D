#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
layout (location = 0) in vec2 v_pos;
layout (location = 1) in vec2 v_uv;

// Textures
layout (location = 0) uniform sampler2D u_depthMap;

// Vector uniforms
uniform vec3 u_cameraPosition;
uniform vec3 u_flareSourcePosition;
uniform vec2 u_flareSourceUV;

// Float uniforms
uniform float u_farDistance;
uniform float u_nearDistance;
uniform float u_lensFlareIntensity;
uniform float u_lensFlareAlpha;

// Boolean uniforms
uniform bool u_isLensFlareEnabled;

// Out variables
out vec2 f_uv;
out float f_flareVisibility;

// Functions
float convertDepthToPerspective(float depth);
float calculateFlareVisibility();

// Process vertex
void main()
{
	gl_Position = vec4(v_pos, 0.0f, 1.0f);
	f_uv = v_uv; 
    f_flareVisibility = calculateFlareVisibility();
}

float calculateFlareVisibility()
{
    if (u_isLensFlareEnabled && (u_lensFlareIntensity > 0.0f) && (u_lensFlareAlpha > 0.0f))
    {
        // Calculate scene depth
        float flareDepth = texture(u_depthMap, u_flareSourceUV).r;
        float flareFragmentDepth = (convertDepthToPerspective(flareDepth) / u_farDistance);

        // Calculate distance to light source
        float flareDistance = distance(u_cameraPosition, u_flareSourcePosition);
        
        // Check if lightsource is not occluded by an object
        if ((flareFragmentDepth * u_farDistance) >= abs(flareDistance))
        {
            return 1.0f;
        }
        else
        {
            return 0.0f;
        }
    }
    else
    {
        return 0.0f;
    }
}

float convertDepthToPerspective(float depth)
{
    float z = ((depth * 2.0f) - 1.0f);
    return ((2.0f * u_nearDistance * u_farDistance) / (u_farDistance + u_nearDistance - z * (u_farDistance - u_nearDistance)));
}