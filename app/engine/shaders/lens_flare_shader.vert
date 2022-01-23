#version 460 core

layout (location = 0) in vec2 v_position;
layout (location = 1) in vec2 v_uv;

layout (location = 0) uniform sampler2D u_depthMap;

uniform vec3 u_cameraPosition;
uniform vec3 u_flareSourcePosition;
uniform vec2 u_flareSourceUv;

uniform float u_farDistance;
uniform float u_nearDistance;
uniform float u_lensFlareIntensity;
uniform float u_lensFlareOpacity;

uniform bool u_isLensFlareEnabled;

out vec2 f_uv;
out float f_flareVisibility;

float convertDepthToPerspective(float depth);
float calculateFlareVisibility();

void main()
{
	gl_Position = vec4(v_position, 0.0f, 1.0f);
	f_uv = v_uv; 
    f_flareVisibility = calculateFlareVisibility();
}

float calculateFlareVisibility()
{
    if (u_isLensFlareEnabled && (u_lensFlareIntensity > 0.0f) && (u_lensFlareOpacity > 0.0f))
    {
        float flareDepth = texture(u_depthMap, u_flareSourceUv).r;
        float flareFragmentDepth = (convertDepthToPerspective(flareDepth) / u_farDistance);

        float flareDistance = distance(u_cameraPosition, u_flareSourcePosition);
        
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