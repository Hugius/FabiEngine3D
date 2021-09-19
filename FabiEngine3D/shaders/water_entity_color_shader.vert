#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_uv;

// Textures
layout (location = 5) uniform sampler2D u_displacementMap;

// Matrix uniforms
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

// Vector uniforms
uniform vec2 u_waveOffset;

// Float uniforms
uniform float u_heightOffset;
uniform float u_uvRepeat;
uniform float u_waveHeight;

// Boolean uniforms
uniform bool u_hasDisplacementMap;

// Out variables
out vec4 f_clip;
out vec2 f_uv;
out vec3 f_pos;

// Process vertex
void main()
{
	// Variable for position altering
	vec3 newPosition = v_pos;

	// Add dynamic position offset
	newPosition += vec3(0.0f, u_heightOffset, 0.0f);

	// Pre-calculate UV out variable
	f_uv = (v_uv * u_uvRepeat);

	// Vertex water waves
	if (u_hasDisplacementMap)
	{
		// Get size of 1 displacement map texel
		vec2 texelSize = (vec2(1.0f) / textureSize(u_displacementMap, 0));

		// Calculate height percentage
		float heightPercentage = texture(u_displacementMap, (f_uv + (u_waveOffset * texelSize))).r;

		// Add height to vertex Y
		newPosition.y += (heightPercentage * u_waveHeight);
	}

	// Camera spaces
	vec4 worldSpacePos = vec4(newPosition, 1.0f);
	vec4 clipSpacePos  = u_projectionMatrix * u_viewMatrix * vec4(newPosition, 1.0f);

	// GLSL variables
	gl_Position = clipSpacePos;

	// Out variables
	f_pos  = worldSpacePos.xyz;
	f_clip = clipSpacePos;
}