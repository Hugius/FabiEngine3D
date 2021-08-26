#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
layout (location = 0) in vec2 v_pos;
layout (location = 1) in vec2 v_uv;

// Textures
layout (location = 0) uniform sampler2D u_depthMap;

// Vector uniforms
uniform vec4 u_flareSourcePositionClipspace;

// Vector uniforms
uniform vec3 u_flareSourcePosition;
uniform vec3 u_cameraPosition;

// Float uniforms
uniform float u_farZ;
uniform float u_nearZ;

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
    if (u_isLensFlareEnabled && (u_flareSourcePositionClipspace.w > 0.0f))
    {
        // Convert to UV space
        vec2 lightSourceClipPosition = (u_flareSourcePositionClipspace.xy / u_flareSourcePositionClipspace.w);
        vec2 lightSourceUV = vec2((lightSourceClipPosition.x + 1.0f) / 2.0f, (lightSourceClipPosition.y + 1.0f) / 2.0f);

        // Calculate scene depth
        float flareDepth = texture(u_depthMap, lightSourceUV).r;
        float flareFragmentDepth = (convertDepthToPerspective(flareDepth) / u_farZ);

        // Calculate distance to light source
        float flareDistance = distance(u_cameraPosition, u_flareSourcePosition);
        
        // Check if lightsource is not occluded by an object
        if ((flareFragmentDepth * u_farZ) >= abs(flareDistance))
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