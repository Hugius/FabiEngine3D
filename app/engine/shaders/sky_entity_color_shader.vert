#version 330 core
#extension GL_ARB_explicit_uniform_location : require

layout (location = 0) in vec3 v_position;

uniform mat4 u_rotationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

out vec3 f_uv;

void main()
{
	gl_Position = (u_projectionMatrix * u_viewMatrix * u_rotationMatrix * vec4(v_position, 1.0f));
    f_uv = vec3(v_position.x, -v_position.y, v_position.z);
}