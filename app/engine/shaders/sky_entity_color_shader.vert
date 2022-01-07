#version 460 core

layout (location = 0) in vec3 v_position;

uniform mat4 u_rotationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

out vec3 f_uv;

void main()
{
	gl_Position = (u_projectionMatrix * u_viewMatrix * u_rotationMatrix * vec4(v_position, 1.0f));
    f_uv = v_position;
}