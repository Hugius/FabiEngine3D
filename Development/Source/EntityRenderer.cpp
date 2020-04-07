#include "EntityRenderer.hpp"

EntityRenderer::EntityRenderer(const string & vertexFile, const string & fragmentFile, ShaderBus& shaderBus) :
	_shader(vertexFile, fragmentFile),
	_shaderBus(shaderBus)
{
	
}