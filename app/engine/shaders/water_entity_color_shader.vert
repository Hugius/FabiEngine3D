#version 330 core
#extension GL_ARB_explicit_uniform_location : require

layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_uv;

layout (location = 5) uniform sampler2D u_displacementMap;

uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

uniform vec2 u_waveOffset;

uniform float u_height;
uniform float u_textureRepeat;
uniform float u_waveHeight;

uniform bool u_hasDisplacementMap;

out vec4 f_clip;
out vec2 f_uv;
out vec3 f_position;

void main()
{
	// Variable for position altering
	vec3 newPosition = v_pos;

	// Set height
	newPosition.y = u_height;

	// Pre-calculate UV out variable
	f_uv = (v_uv * u_textureRepeat);

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
	vec4 worldSpacePosition = vec4(newPosition, 1.0f);
	vec4 clipSpacePosition  = u_projectionMatrix * u_viewMatrix * vec4(newPosition, 1.0f);

	// GLSL variables
	gl_Position = clipSpacePosition;

	// Out variables
	f_position  = worldSpacePosition.xyz;
	f_clip = clipSpacePosition;
}