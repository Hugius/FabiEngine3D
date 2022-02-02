#include "base_renderer.hpp"

void BaseRenderer::inject(shared_ptr<ShaderBuffer> shader)
{
	_shader = shader;
}

void BaseRenderer::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}