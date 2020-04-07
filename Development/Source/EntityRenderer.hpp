#pragma once
#include "Entity.hpp"
#include "OpenGLShader.hpp"
#include "SkyEntity.hpp"
#include "TerrainEntity.hpp"
#include "WaterEntity.hpp"
#include "LightEntity.hpp"
#include "GameEntity.hpp"
#include "GuiEntity.hpp"
#include "ShaderBus.hpp"

class EntityRenderer
{
public:
	EntityRenderer(const string & vertexFile, const string & fragmentFile, ShaderBus& shaderBus);
	virtual ~EntityRenderer() = default;

	virtual void bind()   = 0;
	virtual void unbind() = 0;

protected:
	OpenGLShader _shader;

	ShaderBus& _shaderBus;
};