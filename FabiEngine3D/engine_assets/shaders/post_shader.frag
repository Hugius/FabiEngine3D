#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
in vec2 f_uv;
in float f_flareOcclusion;

// Textures
layout(location = 0) uniform sampler2D u_sampler_scene;
layout(location = 1) uniform sampler2D u_sampler_bloom;
layout(location = 2) uniform sampler2D u_sampler_depth;
layout(location = 3) uniform sampler2D u_sampler_blur;
layout(location = 4) uniform sampler2D u_sampler_flare;

// Float uniforms
uniform float u_nearZ;
uniform float u_farZ;
uniform float u_dofMaxDistance;
uniform float u_dofBlurDistance;
uniform float u_lensFlareAlpha;
uniform float u_lensFlareIntensity;

// Boolean uniforms
uniform bool u_isBloomEnabled;
uniform bool u_isDofEnabled;
uniform bool u_isDofDynamic;
uniform bool u_isLensFlareEnabled;

// Out variables
layout (location = 0) out vec4 o_finalColor;

float convertDepthToPerspective(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * u_nearZ * u_farZ) / (u_farZ + u_nearZ - z * (u_farZ - u_nearZ));
}

void main()
{
	// Texture mapping
	float currentDepth         = texture(u_sampler_depth, f_uv).r;
	float currentFragmentDepth = convertDepthToPerspective(currentDepth) / u_farZ;
    float middleDepth          = texture(u_sampler_depth, vec2(0.5f)).r;
    float middleFragmentDepth  = convertDepthToPerspective(middleDepth) / u_farZ;
	vec3 sceneColor            = texture(u_sampler_scene, f_uv).rgb;
	vec3 bloomColor            = texture(u_sampler_bloom, f_uv).rgb;
	vec3 blurColor             = texture(u_sampler_blur, f_uv).rgb;
    vec3 flareColor            = texture(u_sampler_flare, vec2(f_uv.x, -f_uv.y)).rgb;

    // Default scene
    o_finalColor.rgb = sceneColor;

	// Bloom
	o_finalColor.rgb += (bloomColor * float(u_isBloomEnabled));
	
	// DOF
	if(u_isDofEnabled)
	{
        // Distance from camera to direct object
        float middleFragmentDistance = (middleFragmentDepth * u_farZ);
        float middleSmoothingDistance = (u_dofMaxDistance * 0.2f);

        // Check if camera is looking at a close object
        if(middleFragmentDistance < (u_dofMaxDistance + middleSmoothingDistance) || !u_isDofDynamic)
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

            // Add bloom
            vec3 dofColor = blurColor + bloomColor;

            // Mix with blur color accordingly
            o_finalColor.rgb = mix(o_finalColor.rgb, dofColor, blurMixValue);
        }
	}

    // Lens flare
    o_finalColor.rgb += (flareColor * u_lensFlareAlpha * u_lensFlareIntensity * float(u_isLensFlareEnabled) * f_flareOcclusion);

	// Alpha value
	o_finalColor.a = 1.0f;
}