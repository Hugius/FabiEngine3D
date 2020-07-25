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

// Float uniforms
uniform float u_uvRepeat;
uniform float u_waveOffset;
uniform float u_waveHeight;

// Boolean uniforms
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
	if(u_isWaving)
	{
		// Get size of 1 texel of this texture
		float texelSize = 1.0f / textureSize(u_sampler_displacementMap, 0).x;

		// Floor and ceil to nearest texel
		float height1 = texture(u_sampler_displacementMap, f_uv + vec2(u_waveOffset - mod(u_waveOffset, 1.0f))).r;
		float height2 = texture(u_sampler_displacementMap, f_uv + vec2(u_waveOffset + mod(u_waveOffset, 1.0f))).r;

		// Calculate height in between texels
		float height = height1 + ((height2 - height1) / 2.0f);

		// Add height to vertex Y
		newPos.y += height * u_waveHeight;
	}

	// Camera spaces
	vec4 worldSpace = vec4(v_pos, 1.0);
	vec4 clipSpace  = u_projectionMatrix * u_viewMatrix * vec4(newPos, 1.0);

	// GLSL variables
	gl_Position = clipSpace;

	// Out variables
	f_pos  = worldSpace.xyz;
	f_clip = clipSpace;
}