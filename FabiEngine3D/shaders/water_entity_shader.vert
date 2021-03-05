#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec2 v_uv;

// Textures
layout(location = 5) uniform sampler2D u_sampler_displacementMap;

// Matrix44 uniforms
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

// Vec3 uniforms
uniform vec3 u_customPositionOffset;

// Vec2 uniforms
uniform vec2 u_waveOffset;

// Float uniforms
uniform float u_uvRepeat;
uniform float u_waveHeightFactor;

// Boolean uniforms
uniform bool u_isEffectsEnabled;
uniform bool u_isWaving;

// Out variables
out vec4 f_clip;
out vec2 f_uv;
out vec3 f_pos;

// Main function
void main()
{
	// Variable for position altering
	vec3 newPos = v_pos;

	// Add dynamic position offset
	newPos += u_customPositionOffset;

	// Pre-calculate UV out variable
	f_uv = vec2(v_uv.x / 2.0 + 0.5, v_uv.y / 2.0 + 0.5) * u_uvRepeat;

	// Vertex water waves
	if(u_isEffectsEnabled && u_isWaving)
	{
		// Get size of 1 texel of this texture
		float texelSize = 1.0f / textureSize(u_sampler_displacementMap, 0).x;

		// Floor and ceil to nearest texels
		float minX = u_waveOffset.x - mod(u_waveOffset.x, 1.0f);
		float maxX = u_waveOffset.x + mod(u_waveOffset.x, 1.0f);
		float minZ = u_waveOffset.y - mod(u_waveOffset.y, 1.0f);
		float maxZ = u_waveOffset.y + mod(u_waveOffset.y, 1.0f);
		float height1 = texture(u_sampler_displacementMap, f_uv + vec2(minX, minZ)).r;
		float height2 = texture(u_sampler_displacementMap, f_uv + vec2(maxX, maxZ)).r;

		// Calculate height in between texels
		float height = height1 + ((height2 - height1) / 2.0f);

		// Add height to vertex Y
		newPos.y += height * u_waveHeightFactor;
	}

	// Camera spaces
	vec4 worldSpacePos = vec4(newPos, 1.0f);
	vec4 clipSpacePos  = u_projectionMatrix * u_viewMatrix * vec4(newPos, 1.0f);

	// GLSL variables
	gl_Position = clipSpacePos;

	// Out variables
	f_pos  = worldSpacePos.xyz;
	f_clip = clipSpacePos;
}