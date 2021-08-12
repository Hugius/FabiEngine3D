#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
in vec2 f_uv;

// Textures
layout (location = 0) uniform sampler2D u_depthMap;
layout (location = 1) uniform sampler2D u_sceneMap;
layout (location = 2) uniform sampler2D u_dofMap;

// Float uniforms
uniform float u_nearZ;
uniform float u_farZ;
uniform float u_dofMaxDistance;
uniform float u_dofBlurDistance;

// Boolean uniforms
uniform bool u_isDofEnabled;
uniform bool u_isDofDynamic;

// Out variables
layout (location = 0) out vec4 o_finalColor;

// Functions
float convertDepthToPerspective(float depth);

// Process fragment
void main()
{
    // Validate
	if (!u_isDofEnabled)
	{
        o_finalColor.rgb = texture(u_sceneMap, f_uv).rgb;
		o_finalColor.a = 1.0f;
		return;
    }

    // Texture mapping
	float currentDepth = texture(u_depthMap, f_uv).r;
    float middleDepth = texture(u_depthMap, vec2(0.5f)).r;
    vec3 blurColor = texture(u_dofMap, f_uv).rgb;

    // Calculate framgnet depths
    float currentFragmentDepth = (convertDepthToPerspective(currentDepth) / u_farZ);
    float middleFragmentDepth  = (convertDepthToPerspective(middleDepth) / u_farZ);

    // Calculate distance from camera to direct object
    float middleFragmentDistance = (middleFragmentDepth * u_farZ);
    float middleSmoothingDistance = (u_dofMaxDistance * 0.2f);

    // Check if camera is looking at a close object
    if (middleFragmentDistance < (u_dofMaxDistance + middleSmoothingDistance) || !u_isDofDynamic)
    {
        // Distance from camera to fragment in world space
        float fragmentDistance = (currentFragmentDepth * u_farZ);

        // Smooth blur overlap distance in world space
        float blurSmoothingDistance = u_dofBlurDistance * 0.5f;

        // Calculate DOF blur strength based on fragment distance
        float blurMixValue = (fragmentDistance - (u_dofBlurDistance - blurSmoothingDistance)) / blurSmoothingDistance;

        // Calculate DOF blur strength based on middle distance
        float distanceMixValue = ((u_dofMaxDistance + middleSmoothingDistance) - middleFragmentDistance) / middleSmoothingDistance;
            
        // Values must not go over 1
        blurMixValue = clamp(blurMixValue, 0.0f, 1.0f); 
        distanceMixValue = clamp(distanceMixValue, 0.0f, 1.0f);

        // Apply camera distance mix value
        blurMixValue = mix(0.0f, blurMixValue, u_isDofDynamic ? distanceMixValue : 1.0f);

        // Mix with blur color accordingly
        vec3 sceneColor = texture(u_sceneMap, f_uv).rgb;
        o_finalColor.rgb = mix(sceneColor, blurColor, blurMixValue);
        o_finalColor.a = 1.0f;
    }
    else
    {
        o_finalColor.rgb = texture(u_sceneMap, f_uv).rgb;
		o_finalColor.a = 1.0f;
    }
}

float convertDepthToPerspective(float depth)
{
    float z = ((depth * 2.0f) - 1.0f);
    return ((2.0f * u_nearZ * u_farZ) / (u_farZ + u_nearZ - z * (u_farZ - u_nearZ)));
}