#include "base_entity_renderer.hpp"

BaseEntityRenderer::BaseEntityRenderer(const string & vertexFile, const string & fragmentFile, ShaderBus& shaderBus) :
	_shader(vertexFile, fragmentFile),
	_shaderBus(shaderBus)
{
	
}