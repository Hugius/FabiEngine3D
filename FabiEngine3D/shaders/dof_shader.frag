#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// Constants
#define MIDDLE_SMOOTHING_MULTIPLIER 0.2f
#define FRAGMENT_SMOOTHING_MULTIPLIER 0.5f

// In variables
in vec2 f_uv;

// Textures
layout (location = 0) uniform sampler2D u_depthMap;
layout (location = 1) uniform sampler2D u_sceneMap;
layout (location = 2) uniform sampler2D u_dofMap;

// Float uniforms
uniform float u_nearDistance;
uniform float u_farDistance;
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

    // Calculate fragment depths
    float currentFragmentDistance = convertDepthToPerspective(currentDepth);
    float middleFragmentDistance = convertDepthToPerspective(middleDepth);

    // Calculate smoothing distances
    float middleSmoothingDistance = (u_dofMaxDistance * MIDDLE_SMOOTHING_MULTIPLIER);
    float fragmentSmoothingDistance = (u_dofBlurDistance * FRAGMENT_SMOOTHING_MULTIPLIER);

    // Calculate distance from camera to direct object
    bool isCloseToFragment = (middleFragmentDistance < (u_dofMaxDistance + middleSmoothingDistance));

    // Check if DOF blur is needed
    if (isCloseToFragment || !u_isDofDynamic)
    {
        // Calculate DOF blur strength based on fragment distance
        float blurMixValue = (currentFragmentDistance - (u_dofBlurDistance - fragmentSmoothingDistance)) / fragmentSmoothingDistance;

        // Calculate DOF blur strength based on middle distance
        float distanceMixValue = ((u_dofMaxDistance + middleSmoothingDistance) - middleFragmentDistance) / middleSmoothingDistance;

        // Clamp mix values
        blurMixValue = clamp(blurMixValue, 0.0f, 1.0f); 
        distanceMixValue = clamp(distanceMixValue, 0.0f, 1.0f);

        // Calculate final mix value (distant blur or dynamic DOF)
        float finalMixValue = mix(0.0f, blurMixValue, (u_isDofDynamic ? distanceMixValue : 1.0f));

        // Mix with blur color accordingly
        vec3 sceneColor = texture(u_sceneMap, f_uv).rgb;
        o_finalColor.rgb = mix(sceneColor, blurColor, finalMixValue);
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
    return ((2.0f * u_nearDistance * u_farDistance) / (u_farDistance + u_nearDistance - z * (u_farDistance - u_nearDistance)));
}