#version 460 core

#define MIDDLE_SMOOTHING_MULTIPLIER 0.2f
#define FRAGMENT_SMOOTHING_MULTIPLIER 0.5f

in vec2 f_uv;

layout (location = 0) uniform sampler2D u_depthMap;
layout (location = 1) uniform sampler2D u_sceneMap;
layout (location = 2) uniform sampler2D u_dofMap;

uniform float u_cameraNear;
uniform float u_cameraFar;
uniform float u_dofDynamicDistance;
uniform float u_dofBlurDistance;

uniform bool u_isDofEnabled;
uniform bool u_isDofDynamic;

layout (location = 0) out vec4 o_finalColor;

float convertDepthToPerspective(float depth)
{
    float z = ((depth * 2.0f) - 1.0f);

    return ((2.0f * u_cameraNear * u_cameraFar) / (u_cameraFar + u_cameraNear - z * (u_cameraFar - u_cameraNear)));
}

void main()
{
	if(!u_isDofEnabled)
	{
        o_finalColor.rgb = texture(u_sceneMap, f_uv).rgb;
		o_finalColor.a = 1.0f;

		return;
    }

	float currentDepth = texture(u_depthMap, f_uv).r;
    float middleDepth = texture(u_depthMap, vec2(0.5f)).r;
    float currentFragmentDistance = convertDepthToPerspective(currentDepth);
    float middleFragmentDistance = convertDepthToPerspective(middleDepth);
    float middleSmoothingDistance = (u_dofDynamicDistance * MIDDLE_SMOOTHING_MULTIPLIER);
    float fragmentSmoothingDistance = (u_dofBlurDistance * FRAGMENT_SMOOTHING_MULTIPLIER);

    bool isCloseToFragment = (middleFragmentDistance < (u_dofDynamicDistance + middleSmoothingDistance));

    if(isCloseToFragment || !u_isDofDynamic)
    {
        float blurMixValue = (currentFragmentDistance - (u_dofBlurDistance - fragmentSmoothingDistance)) / fragmentSmoothingDistance;
        float distanceMixValue = ((u_dofDynamicDistance + middleSmoothingDistance) - middleFragmentDistance) / middleSmoothingDistance;

        blurMixValue = clamp(blurMixValue, 0.0f, 1.0f); 
        distanceMixValue = clamp(distanceMixValue, 0.0f, 1.0f);

        float finalMixValue = mix(0.0f, blurMixValue, (u_isDofDynamic ? distanceMixValue : 1.0f));

        vec3 worldColor = texture(u_sceneMap, f_uv).rgb;
        vec3 blurColor = texture(u_dofMap, f_uv).rgb;

        o_finalColor.rgb = mix(worldColor, blurColor, finalMixValue);
        o_finalColor.a = 1.0f;
    }
    else
    {
        o_finalColor.rgb = texture(u_sceneMap, f_uv).rgb;
		o_finalColor.a = 1.0f;
    }
}