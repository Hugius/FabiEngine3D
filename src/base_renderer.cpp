#include "base_renderer.hpp"

void BaseRenderer::inject(shared_ptr<ShaderBuffer> shaderBuffer)
{
	_shaderBuffer = shaderBuffer;
}

void BaseRenderer::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

void BaseRenderer::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}