#include "base_renderer.hpp"

void BaseRenderer::inject(shared_ptr<ShaderBuffer> shader)
{
	_shader = shader;
}

void BaseRenderer::inject(shared_ptr<RenderBus> renderBus)
{
	_renderBus = renderBus;
}