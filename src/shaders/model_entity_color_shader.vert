#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// In variables
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_uv;
layout (location = 2) in vec3 v_normal;
layout (location = 3) in vec3 v_tangent;
layout (location = 4) in vec3 v_offset;

// Matrix uniforms
uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform mat4 u_shadowMatrix;
uniform mat3 u_normalTransformationMatrix;

// Vector uniforms
uniform vec4 u_clippingPlane;

// Float uniforms
uniform float u_positionY;
uniform float u_minHeight;
uniform float u_maxHeight;
uniform float u_textureRepeat;

// Boolean uniforms
uniform bool u_isInstanced;
uniform bool u_hasNormalMap;

// Out variables
out vec3 f_position;
out vec2 f_uv;
out vec3 f_normal;
out vec4 f_shadowPosition;
out vec4 f_clip;
out mat3 f_tbnMatrix;

// Declarations
mat3 calculateTbnMatrix();

// Process vertex
void main()
{
	// In variables
	vec4 worldSpacePosition = (u_transformationMatrix * vec4(v_pos, 1.0f)) + ((u_isInstanced == true) ? vec4(v_offset, 0.0f) : vec4(0.0f));
	vec4 viewSpacePosition  = (u_viewMatrix * worldSpacePosition);
	vec4 clipSpacePosition  = (u_projectionMatrix * viewSpacePosition);

	// GLSL variables
	gl_Position = clipSpacePosition;
	gl_ClipDistance[0] = dot(worldSpacePosition, vec4(0.0f,  1.0f, 0.0f, -(u_positionY + u_minHeight)));
	gl_ClipDistance[1] = dot(worldSpacePosition, vec4(0.0f, -1.0f, 0.0f,  (u_positionY + u_maxHeight)));
	gl_ClipDistance[2] = dot(worldSpacePosition, u_clippingPlane);
	
	// Out variables
	f_position       = worldSpacePosition.xyz;
	f_uv        = (vec2(v_uv.x, -v_uv.y) * u_textureRepeat);
	f_normal    = normalize(u_normalTransformationMatrix * v_normal);
	f_shadowPosition = u_shadowMatrix * worldSpacePosition;
	f_clip      = clipSpacePosition;
    f_tbnMatrix = calculateTbnMatrix();
}

mat3 calculateTbnMatrix()
{
    // Normal mapping matrix
    if (u_hasNormalMap)
    {
        vec3 tangent = normalize(mat3(u_normalTransformationMatrix) * v_tangent);
			 tangent = normalize(tangent - dot(tangent, f_normal) * f_normal);
        vec3 bitangent = cross(f_normal, tangent);
        return mat3(tangent, bitangent, f_normal);
    }
    else
    {
        return mat3(1.0f);
    }
}