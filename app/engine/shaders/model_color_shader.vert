#version 460 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_uv;
layout (location = 2) in vec3 v_normal;
layout (location = 3) in vec3 v_tangent;

uniform mat4 u_transformation;
uniform mat4 u_cameraView;
uniform mat4 u_cameraProjection;
uniform mat4 u_shadowView;
uniform mat4 u_shadowProjection;

uniform mat3 u_normalTransformation;

uniform float u_minX;
uniform float u_minY;
uniform float u_minZ;
uniform float u_maxX;
uniform float u_maxY;
uniform float u_maxZ;

uniform int u_textureRepeat;

uniform bool u_hasNormalMap;

out vec4 f_shadowSpacePos;
out vec3 f_worldSpacePos;
out vec4 f_clipSpacePos;
out vec2 f_uv;
out vec3 f_normal;
out mat3 f_tbn;

mat3 calculateTbn();

void main()
{
	vec4 worldSpacePosition = (u_transformation * vec4(v_position, 1.0f));
	vec4 viewSpacePosition = (u_cameraView * worldSpacePosition);
	vec4 clipSpacePosition = (u_cameraProjection * viewSpacePosition);

	f_shadowSpacePos = (u_shadowProjection * u_shadowView * worldSpacePosition);
	f_worldSpacePos = worldSpacePosition.xyz;
	f_clipSpacePos = clipSpacePosition;
	f_uv = (v_uv * float(u_textureRepeat));
	f_normal = normalize(u_normalTransformation * v_normal);
    f_tbn = calculateTbn();

	gl_Position = clipSpacePosition;
	gl_ClipDistance[0] = dot(worldSpacePosition, vec4( 1.0f,  0.0f,  0.0f, -u_minX));
	gl_ClipDistance[1] = dot(worldSpacePosition, vec4(-1.0f,  0.0f,  0.0f,  u_maxX));
	gl_ClipDistance[2] = dot(worldSpacePosition, vec4( 0.0f,  1.0f,  0.0f, -u_minY));
	gl_ClipDistance[3] = dot(worldSpacePosition, vec4( 0.0f, -1.0f,  0.0f,  u_maxY));
	gl_ClipDistance[4] = dot(worldSpacePosition, vec4( 0.0f,  0.0f,  1.0f, -u_minZ));
	gl_ClipDistance[5] = dot(worldSpacePosition, vec4( 0.0f,  0.0f, -1.0f,  u_maxZ));
}

mat3 calculateTbn()
{
    if(u_hasNormalMap)
    {
        vec3 tangent = normalize(u_normalTransformation * v_tangent);

		tangent = normalize(tangent - (dot(tangent, f_normal) * f_normal));

        vec3 bitangent = cross(tangent, f_normal);

        return mat3(tangent, bitangent, f_normal);
    }
    else
    {
        return mat3(1.0f);
    }
}