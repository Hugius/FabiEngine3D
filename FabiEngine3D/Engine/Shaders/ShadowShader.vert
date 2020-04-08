#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_uv;
layout (location = 3) in vec3 v_offset;

out vec3 f_pos;
out vec2 f_uv;

uniform mat4  u_lightSpaceMatrix;
uniform mat4  u_modelMatrix;
uniform bool  u_isInstanced;
uniform float u_maxY;

void main()
{
	vec4 worldSpacePos = (u_modelMatrix * vec4(v_pos, 1.0f)) + (u_isInstanced == true ? vec4(v_offset, 0.0f) : vec4(0.0f));
	vec4 lightSpacePos = u_lightSpaceMatrix * worldSpacePos;

	gl_Position = lightSpacePos;
	gl_ClipDistance[1] = dot(worldSpacePos, vec4(0.0f, -1.0f, 0.0f, u_maxY));
	
	f_uv = vec2(v_uv.x, -v_uv.y);
	f_pos = v_pos;
}