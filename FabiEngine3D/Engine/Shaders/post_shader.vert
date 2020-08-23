#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
layout(location = 0) in vec2 v_pos;
layout(location = 1) in vec2 v_uv;

layout(location = 2) uniform sampler2D u_sampler_depth;

// Matrix44 uniforms
uniform mat4 u_modelMatrix;

// Boolean uniforms
uniform bool u_mirrorHor;
uniform bool u_mirrorVer;
uniform float u_farZ;
uniform float u_nearZ;

// Vector4 uniforms
uniform vec4 u_directionalLightingPositionClipspace;

// Vector3 uniforms
uniform vec3 u_directionalLightingPosition;
uniform vec3 u_cameraPosition;

// Out variables
out vec2 f_uv;
out float f_flareOcclusion;

// Functions
float convertDepthToPerspective(float depth);
float calculateFlareOcclusion();

void main()
{
	gl_Position = u_modelMatrix * vec4(v_pos, 0.0f, 1.0f);
	f_uv.x = u_mirrorHor ? -v_uv.x : v_uv.x;
	f_uv.y = u_mirrorVer ?  v_uv.y : -v_uv.y; 
    f_flareOcclusion = calculateFlareOcclusion();
}

float calculateFlareOcclusion()
{
    if(u_directionalLightingPositionClipspace.w > 0.0f)
    {
        // Convert to UV space
        vec2 lightSourceClipPos = u_directionalLightingPositionClipspace.xy / u_directionalLightingPositionClipspace.w;
        vec2 lightSourceUV = vec2((lightSourceClipPos.x + 1.0f) / 2.0f, (lightSourceClipPos.y + 1.0f) / 2.0f);

        // Calculate scene depth
        float flareDepth         = texture(u_sampler_depth, lightSourceUV).r;
        float flareFragmentDepth = convertDepthToPerspective(flareDepth) / u_farZ;

        // Calculate distance to light source
        vec3 viewDirection       = (u_cameraPosition - u_directionalLightingPosition);
        float flareDistance      = length(viewDirection);

        // Check if lightsource is occluded by an object
        if(flareFragmentDepth * u_farZ >= flareDistance)
        {
            return 1.0f;
        }
    }

    return 0.0f;
}

float convertDepthToPerspective(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * u_nearZ * u_farZ) / (u_farZ + u_nearZ - z * (u_farZ - u_nearZ));
}