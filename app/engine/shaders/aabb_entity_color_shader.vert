#version 460 core

layout (location = 0) in vec3 v_position;

uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

out vec2 f_uv;

void main()
{
	vec4 worldSpacePosition = (u_transformationMatrix * vec4(v_position, 1.0f));
	vec4 viewSpacePosition  = (u_viewMatrix * worldSpacePosition);
	vec4 clipSpacePosition  = (u_projectionMatrix * viewSpacePosition);

	gl_Position = clipSpacePosition;
}