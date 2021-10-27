#include "base_renderer.hpp"

BaseRenderer::BaseRenderer(const string& vertexFile, const string& fragmentFile, RenderBus& renderBus)
	:
	_shader(vertexFile, fragmentFile),
	_renderBus(renderBus)
{

}