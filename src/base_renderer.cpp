#include "base_renderer.hpp"

BaseRenderer::BaseRenderer(const string& vertexPath, const string& fragmentPath, RenderBus& renderBus)
	:
	_shader(vertexPath, fragmentPath),
	_renderBus(renderBus)
{

}