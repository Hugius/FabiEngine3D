#version 460 core

layout (location = 0) in vec2 v_position;
layout (location = 1) in vec2 v_uv;

layout (location = 0) uniform sampler2D u_depthMap;

uniform vec3 u_cameraPosition;
uniform vec3 u_flareSourcePosition;
uniform vec2 u_flareSourceUv;

uniform float u_cameraFar;
uniform float u_cameraNear;
uniform float u_lensFlareIntensity;
uniform float u_lensFlareOpacity;

uniform bool u_isLensFlareEnabled;

out vec2 f_uv;
out float f_visibility;

float calculateFlareVisibility();
float convertDepthToPerspective(float depth);

void main()
{
	f_uv = v_uv; 
    f_visibility = calculateFlareVisibility();

	gl_Position = vec4(v_position, 0.0f, 1.0f);
}

float calculateFlareVisibility()
{
    if(u_isLensFlareEnabled && (u_lensFlareIntensity > 0.0f) && (u_lensFlareOpacity > 0.0f))
    {
        float fragmentDepth = convertDepthToPerspective(texture(u_depthMap, u_flareSourceUv).r);
        float flareDepth = distance(u_cameraPosition, u_flareSourcePosition);
        
        if(fragmentDepth > abs(flareDepth))
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

    return ((2.0f * u_cameraNear * u_cameraFar) / (u_cameraFar + u_cameraNear - z * (u_cameraFar - u_cameraNear)));
}