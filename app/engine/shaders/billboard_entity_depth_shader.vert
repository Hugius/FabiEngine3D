#version 330 core
#extension GL_ARB_explicit_uniform_location : require

layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_uv;

uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

uniform vec2 u_adderUV;
uniform vec2 u_multiplierUV;

uniform float u_minHeight;
uniform float u_maxHeight;
uniform float u_clippingY;
uniform float u_textureRepeat;

uniform bool u_isUnderWater;

out vec2 f_uv;

void main()
{
	vec4 worldSpacePosition = (u_transformationMatrix * vec4(v_pos, 1.0f));
	vec4 viewSpacePosition  = (u_viewMatrix * worldSpacePosition);
	vec4 clipSpacePosition  = (u_projectionMatrix * viewSpacePosition);

	gl_Position = clipSpacePosition;
	gl_ClipDistance[0] = dot(worldSpacePosition, vec4(0.0f,  1.0f, 0.0f, -u_minHeight));
	gl_ClipDistance[1] = dot(worldSpacePosition, vec4(0.0f, -1.0f, 0.0f,  u_maxHeight));
	gl_ClipDistance[2] = dot(worldSpacePosition, vec4(0.0f, u_isUnderWater ? -1.0f : 1.0f, 0.0f, u_isUnderWater ? u_clippingY : -u_clippingY));

    f_uv.x = ((u_adderUV.x + (v_uv.x * u_multiplierUV.x)) * u_textureRepeat);
	f_uv.y = ((u_adderUV.y + (v_uv.y * u_multiplierUV.y)) * u_textureRepeat);
}