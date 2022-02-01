#version 460 core

layout (location = 0) in vec3 v_position;

uniform mat4 u_transformation;
uniform mat4 u_cameraView;
uniform mat4 u_cameraProjection;

out vec3 f_uv;

void main()
{
    f_uv = v_position;

	gl_Position = (u_cameraProjection * u_cameraView * u_transformation * vec4(v_position, 1.0f));
}