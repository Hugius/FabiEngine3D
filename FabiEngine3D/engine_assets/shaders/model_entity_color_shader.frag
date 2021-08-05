#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// Constant variables
#define MAX_POINT_LIGHT_COUNT 128

// In variables
in vec3 f_pos;
in vec2 f_uv;
in vec3 f_normal;
in vec4 f_shadowPos;
in vec4 f_clip;
in mat3 f_tbnMatrix;

// Textures
layout (location = 0) uniform sampler2D u_diffuseMap;
layout (location = 1) uniform sampler2D u_emissionMap;
layout (location = 2) uniform sampler2D u_reflectionMap;
layout (location = 3) uniform sampler2D u_normalMap;
layout (location = 4) uniform sampler2D u_sceneReflectionMap;
layout (location = 5) uniform sampler2D u_shadowMap;
layout (location = 6) uniform samplerCube u_mainSkyMap;
layout (location = 7) uniform samplerCube u_mixSkyMap;

// Matrix uniforms
uniform mat4 u_skyRotationMatrix;

// Vector3 uniforms
uniform vec3 u_pointLightPositions[MAX_POINT_LIGHT_COUNT];
uniform vec3 u_pointLightRadiuses[MAX_POINT_LIGHT_COUNT];
uniform vec3 u_pointLightColors[MAX_POINT_LIGHT_COUNT];
uniform vec3 u_cameraPosition;
uniform vec3 u_cameraFront;
uniform vec3 u_ambientLightColor;
uniform vec3 u_directionalLightColor;
uniform vec3 u_directionalLightPosition;
uniform vec3 u_spotLightColor;
uniform vec3 u_color;
uniform vec3 u_fogColor;
uniform vec3 u_shadowAreaCenter;
uniform vec3 u_mainSkyColor;
uniform vec3 u_mixSkyColor;

// Float uniforms
uniform float u_pointLightIntensities[MAX_POINT_LIGHT_COUNT];
uniform float u_ambientLightIntensity;
uniform float u_directionalLightIntensity;
uniform float u_specularLightFactor;
uniform float u_specularLightIntensity;
uniform float u_alpha;
uniform float u_minDiffuseMapAlpha;
uniform float u_lightness;
uniform float u_inversion;
uniform float u_shadowAreaSize;
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogThickness;
uniform float u_maxSpotlightAngle;
uniform float u_spotLightIntensity;
uniform float u_maxSpotLightDistance;
uniform float u_skyMixValue;
uniform float u_mainSkyLightness;
uniform float u_mixSkyLightness;
uniform float u_shadowLightness;

// Boolean uniforms
uniform bool u_isTransparent;
uniform bool u_isSkyReflective;
uniform bool u_isSceneReflective;
uniform bool u_isSpecularLighted;
uniform bool u_isShadowFrameRenderEnabled;
uniform bool u_isLightedShadowingEnabled;
uniform bool u_isAmbientLightEnabled;
uniform bool u_isDirectionalLightEnabled;
uniform bool u_isSpecularLightEnabled;
uniform bool u_isSpotLightEnabled;
uniform bool u_isPointLightEnabled;
uniform bool u_isFogEnabled;
uniform bool u_isShadowsEnabled;
uniform bool u_hasDiffuseMap;
uniform bool u_hasEmissionMap;
uniform bool u_hasNormalMap;
uniform bool u_hasReflectionMap;
uniform bool u_isBright;

// Integer uniforms
uniform int u_pointLightCount;

// Out variables
layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

// Functions
vec3 getNormalMapping();
vec3 getDiffuseMapping();
vec3 getEmissionMapping();
vec3 getAmbientLighting();
vec3 getDirectionalLighting(vec3 normal, bool noShadowOcclusion);
vec3 getPointLighting(vec3 normal);
vec3 getSpotLighting(vec3 normal);
vec3 getFog(vec3 color);
vec3 getSkyReflections(vec3 color, vec3 normal);
vec3 getSceneReflections(vec3 color);
float getShadows();
float getSpecularLighting(vec3 position, vec3 normal);

// Process fragment
void main()
{
    // Calculate emission mapping
    vec3 emissionMapColor = getEmissionMapping();

    // Calculate normal mapping
    vec3 normal = getNormalMapping();

	// Calculate lighting
	bool isBright = ((emissionMapColor != vec3(0.0f)) || u_isBright);
	float shadowLighting	 = getShadows();
	vec3 ambientLighting	 = getAmbientLighting();
	vec3 directionalLighting = getDirectionalLighting(normal, (u_isLightedShadowingEnabled ? true : (shadowLighting == 1.0f)));
	vec3 pointLighting		 = getPointLighting(normal);
	vec3 spotLighting		 = getSpotLighting(normal);

	// Calculate base color
	vec3 primaryColor = vec3(0.0f);
	primaryColor += getDiffuseMapping();
	primaryColor += emissionMapColor;
	primaryColor  = getSkyReflections(primaryColor, normal);
	primaryColor  = getSceneReflections(primaryColor);
	primaryColor *= u_color;
	primaryColor *= u_lightness;
	primaryColor  = clamp(primaryColor, vec3(0.0f), vec3(1.0f));
	primaryColor  = mix(primaryColor, (vec3(1.0f) - primaryColor), clamp(u_inversion, 0.0f, 1.0f));
	
	// Apply lighting
	if(!isBright)
	{
		vec3 lighting = vec3(0.0f);
		lighting += ambientLighting;
		lighting += directionalLighting;
		lighting *= shadowLighting;
		lighting += pointLighting;
		lighting += spotLighting;
		primaryColor *= lighting;
	}

	// Apply fog
	primaryColor = getFog(primaryColor);

	// Apply gamma correction
    primaryColor = pow(primaryColor, vec3(1.0f / 2.2f));

	// Set final colors
	o_primaryColor = vec4(primaryColor, u_alpha);
	o_secondaryColor = vec4((isBright ? primaryColor : vec3(0.0f)), 1.0f);
}

vec3 getNormalMapping()
{
    if(u_hasNormalMap)
    {
        // Calculate new normal vector
        vec3 normal = texture(u_normalMap, f_uv).rgb;
        normal = ((normal * 2.0f) - 1.0f);
        normal = normalize(f_tbnMatrix * normal);

        // Return
        return normal;
    }
    else
    {
        return f_normal;
    }
}

vec3 getDiffuseMapping()
{
	if(!u_hasDiffuseMap)
	{
		return vec3(1.0f);
	}
	else
	{
		// Calculate diffuse map color
		vec4 diffuseMapColor = texture(u_diffuseMap, f_uv);
		diffuseMapColor.rgb = pow(diffuseMapColor.rgb, vec3(2.2f));

		// Removing alpha background
		if(u_isTransparent)
		{
			if(diffuseMapColor.a < u_minDiffuseMapAlpha)
			{
				discard;
			}
		}

		// Return
		return diffuseMapColor.rgb;
	}
}

vec3 getAmbientLighting()
{
	if(u_isAmbientLightEnabled)
	{
		return (u_ambientLightColor * u_ambientLightIntensity);
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 getDirectionalLighting(vec3 normal, bool noShadowOcclusion)
{
	if(u_isDirectionalLightEnabled)
	{
        // Calculate lighting strength
        vec3 result = vec3(0.0f);
		vec3 lightDirection = normalize(u_directionalLightPosition - f_pos);
		float diffuse = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
		float specular = getSpecularLighting(u_directionalLightPosition, normal);

        // Apply
        result += vec3(diffuse * float(noShadowOcclusion)); // Diffuse
        result += vec3(specular * float(noShadowOcclusion)); // Specular
        result *= u_directionalLightColor; // Color
        result *= u_directionalLightIntensity; // Intensity

        // Return
        return result;
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 getPointLighting(vec3 normal)
{
	if(u_isPointLightEnabled)
	{
		vec3 result = vec3(0.0f);
		
        // For every pointLight
		for (int i = 0; i < u_pointLightCount; i++)
		{
            // Calculate light strength
			vec3 lightDirection = normalize(u_pointLightPositions[i] - f_pos);
			float diffuse = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
			float specular = getSpecularLighting(u_pointLightPositions[i], normal);

			// Calculate light attenuation
			vec3 distance = abs(u_pointLightPositions[i] - f_pos);
			float attenuation = max(0.0f, 1.0f - (distance.x / u_pointLightRadiuses[i].x));
			attenuation = min(attenuation, max(0.0f, 1.0f - (distance.y / u_pointLightRadiuses[i].y)));
			attenuation = min(attenuation, max(0.0f, 1.0f - (distance.z / u_pointLightRadiuses[i].z)));

            // Apply
            vec3 current = vec3(0.0f);
			current += vec3(diffuse); // Diffuse
			current += vec3(specular); // Specular
            current *= u_pointLightColors[i]; // Color
            current *= (attenuation * attenuation); // Distance
            current *= u_pointLightIntensities[i]; // Intensity

            // Add to total lighting value
            result += current;
		}

        // Return
		return result;
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 getSpotLighting(vec3 normal)
{
    if(u_isSpotLightEnabled)
    {
    	// Calculate distance
        float fragmentDistance = abs(length(u_cameraPosition - f_pos));
        float distanceFactor = fragmentDistance / u_maxSpotLightDistance;
        distanceFactor = clamp(distanceFactor, 0.0f, 1.0f);
        distanceFactor = 1.0f - distanceFactor;

        // Calculate lighting strength
        vec3 lightDirection = normalize(u_cameraPosition - f_pos);
        float smoothingFactor = 0.9f;
        float spotTheta = dot(lightDirection, normalize(-u_cameraFront));
        float epsilon   = u_maxSpotlightAngle - u_maxSpotlightAngle * smoothingFactor;
        float intensity = clamp((spotTheta - u_maxSpotlightAngle * smoothingFactor) / epsilon, 0.0f, 1.0f);
		float diffuse = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
        float specular = getSpecularLighting(u_cameraPosition, normal);

        // Apply lighting calculations
		vec3 result = vec3(0.0f);
        result += vec3(diffuse * intensity); // Diffuse
        result += vec3(specular * intensity); // Specular
        result *= u_spotLightColor; // Color
        result *= u_spotLightIntensity; // Intensity

        // Return
        return (result * distanceFactor);
    }
    else
    {
        return vec3(0.0f);
    }
}

vec3 getEmissionMapping()
{
	if(u_hasEmissionMap)
	{
		return texture(u_emissionMap, f_uv).rgb;
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 getFog(vec3 color)
{
	if(u_isFogEnabled)
	{
		// Calculate
        float distance = length(f_pos.xyz - u_cameraPosition);
		float difference = u_fogMaxDistance - u_fogMinDistance;
		float part = (distance - u_fogMinDistance) / difference;
		part = clamp(part, 0.0f, 1.0f);
		float thickness = clamp(u_fogThickness, 0.0f, 1.0f);
		float mixValue = part * thickness;

		// Return
		return mix(color, u_fogColor, mixValue);
	}
	else
	{
		return color;
	}
}

vec3 getSkyReflections(vec3 color, vec3 normal)
{
	if(u_isSkyReflective)
	{
		// Calculation reflection color
		vec3 reflectionMapColor = (u_hasReflectionMap ? texture(u_reflectionMap, f_uv).rgb : vec3(0.0f));
		
		// Check if current texel allows for reflection
		if(reflectionMapColor != vec3(0.0f))
		{
			// Calculate
			float mixValue        = clamp(u_skyMixValue, 0.0, 1.0f);
			float lightness       = mix(u_mainSkyLightness, u_mixSkyLightness, mixValue);
			vec3 viewDirection    = normalize(u_cameraPosition - f_pos);
			vec3 reflectDirection = reflect(viewDirection, normal);
			vec3 mainSkyColor     = texture(u_mainSkyMap, vec3(u_skyRotationMatrix * vec4(reflectDirection, 1.0f))).rgb;
			vec3 mixSkyColor      = texture(u_mixSkyMap, vec3(u_skyRotationMatrix * vec4(reflectDirection, 1.0f))).rgb;
			mainSkyColor 		  = pow(mainSkyColor, vec3(2.2f));
			mixSkyColor 		  = pow(mixSkyColor, vec3(2.2f));
			mainSkyColor 		 *= u_mainSkyColor;
			mixSkyColor 		 *= u_mixSkyColor;
			vec3 reflectColor     = mix(mainSkyColor, mixSkyColor, mixValue) * lightness;
			vec3 mixedColor       = mix(color, reflectColor, 0.5f);

			// Return
			return mixedColor.rgb;
		}

		// Return
		return color;
	}
	else
	{
		return color;
	}
}

vec3 getSceneReflections(vec3 color)
{
	if(u_isSceneReflective)
	{
		// Calculation reflection color
		vec3 reflectionMapColor = u_hasReflectionMap ? texture(u_reflectionMap, f_uv).rgb : vec3(0.0f);
		
		// Check if current texel allows for reflection
		if(reflectionMapColor != vec3(0.0f))
		{
			// Calculate
			vec2 ndc             = (((f_clip.xy / f_clip.w) / 2.0f) + 0.5f);
			vec2 texCoords       = vec2(ndc.x, -ndc.y);
			vec3 reflectionColor = texture(u_sceneReflectionMap, vec2(texCoords.x,  texCoords.y)).rgb;
			vec3 mixedColor      = mix(color.rgb, reflectionColor, 0.5f);
        
        	// Return
			return mixedColor.rgb;
		}

		return color;
	}
	else
	{
		return color;
	}
}

float getSpecularLighting(vec3 position, vec3 normal)
{
    if(u_isSpecularLightEnabled && u_isSpecularLighted)
    {
    	// Calculate
        vec3 lightDirection   = normalize(position - f_pos);
        vec3 viewDirection    = normalize(u_cameraPosition - f_pos);
        vec3 halfWayDirection = normalize(lightDirection + viewDirection);
        float result          = pow(clamp(dot(normal, halfWayDirection), 0.0f, 1.0f), u_specularLightFactor);

        // Return
        return (result * u_specularLightIntensity);
    }
    else
    {
        return 0.0f;
    }
}

float getShadows()
{
	if(u_isShadowsEnabled)
	{
        float halfSize = u_shadowAreaSize / 2.0f;

        // Check if fragment is within shadow area
		if
		(
			abs(f_pos.x - u_shadowAreaCenter.x) <= (halfSize) && 
			abs(f_pos.z - u_shadowAreaCenter.z) <= (halfSize)
		)
		{
			// Variables
			vec2 texelSize = (vec2(1.0f) / textureSize(u_shadowMap, 0));
			float shadow = 0.0f;
			vec3 projCoords = (((f_shadowPos.xyz / f_shadowPos.w) * 0.5f) + 0.5f);
			float currentDepth = projCoords.z;
			float bias = 0.00075f;

			// Skip fragments outside of the depth map
			if (projCoords.z > 1.0f)
			{
				return 1.0f;
			}

			// Calculate PCF shadows
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					float pcfDepth = texture(u_shadowMap, projCoords.xy + (vec2(x, y) * texelSize)).r; 
					shadow += ((currentDepth - texelSize.x) > pcfDepth) ? u_shadowLightness : 1.0f;        
				}    
			}
            
			// Calculate final shadow value
			shadow /= 9.0f;
			
			// Limit shadows
			if(shadow > 1.0f)
			{
				shadow = 1.0f;
			}

			// Long-distance shadows fading
			float maxDistance = max(abs(f_pos.x - u_shadowAreaCenter.x), abs(f_pos.z - u_shadowAreaCenter.z)); // Max distance to center
			float alpha = maxDistance - (halfSize * 0.9f); // Only for the outer 10% of the shadowed area
			alpha = clamp(alpha, 0.0f, halfSize * 0.1f); // Cannot be negative
			alpha /= (halfSize * 0.1f); // Convert value to 0.0 - 1.0 range

			// Debug area frame rendering
			if(u_isShadowFrameRenderEnabled)
			{
				if((maxDistance - (halfSize * 0.99f)) > 0.0f)
				{
					return 0.0f;
				}
			}

			// Return
			return mix(shadow, 1.0f, alpha);
		}

		// No shadow
		return 1.0f;
	}
	else
	{
		// No shadow
		return 1.0f;
	}
}