#pragma once

#include "base_entity.hpp"
#include "opengl_shader.hpp"
#include "sky_entity.hpp"
#include "terrain_entity.hpp"
#include "water_entity.hpp"
#include "light_entity.hpp"
#include "game_entity.hpp"
#include "gui_entity.hpp"
#include "shader_bus.hpp"

class BaseEntityRenderer
{
public:
	BaseEntityRenderer(const string& vertexFile, const string& fragmentFile, ShaderBus& shaderBus);
	virtual ~BaseEntityRenderer() = default;

	virtual void bind()   = 0;
	virtual void unbind() = 0;

protected:
	OpenGLShader _shader;

	ShaderBus& _shaderBus;
};