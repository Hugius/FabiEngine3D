#include "base_entity_renderer.hpp"

BaseEntityRenderer::BaseEntityRenderer(const string& vertexFile, const string& fragmentFile, RenderBus& renderBus) :
	_shader(vertexFile, fragmentFile),
	_renderBus(renderBus)
{
	
}