#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 v_uv;
layout(location = 2) in vec3 v_normal;
layout(location = 4) in vec3 v_offset;

// Matrix 44 uniforms
uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projMatrix;

// Vec2 uniforms
uniform vec2 u_uvAdder;
uniform vec2 u_uvMultiplier;

// Float uniforms
uniform float u_currentY;
uniform float u_minHeight;
uniform float u_maxHeight;
uniform float u_clippingY;

// Boolean uniforms
uniform bool u_isInstanced;
uniform bool u_isBillboard;
uniform bool u_isUnderWater;

// Out variables
out vec2 f_uv;

void main()
{
	// In variables
	vec4 worldSpacePos = (u_modelMatrix * vec4(v_pos, 1.0f)) + (u_isInstanced == true ? vec4(v_offset, 0.0f) : vec4(0.0f));
	vec4 viewSpacePos  = u_viewMatrix * worldSpacePos;
	vec4 clipSpacePos  = u_projMatrix * viewSpacePos;

	// GLSL variables
	gl_Position = clipSpacePos;
	gl_ClipDistance[0] = dot(worldSpacePos, vec4(0.0f,  1.0f, 0.0f, -(u_currentY + u_minHeight)));
	gl_ClipDistance[1] = dot(worldSpacePos, vec4(0.0f, -1.0f, 0.0f, u_currentY + u_maxHeight));
	gl_ClipDistance[2] = dot(worldSpacePos, vec4(0.0f, u_isUnderWater ? -1.0f : 1.0f, 0.0f, u_isUnderWater ? u_clippingY : -u_clippingY));

	// Out variables
    if(u_isBillboard)
    {
        f_uv = vec2(u_uvAdder.x + (v_uv.x*u_uvMultiplier.x), u_uvAdder.y + (-v_uv.y*u_uvMultiplier.y));
    }
    else
    {
		f_uv = vec2(v_uv.x, -v_uv.y);
    }
}