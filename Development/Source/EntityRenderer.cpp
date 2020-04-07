#include <WE3D/EntityRenderer.hpp>

EntityRenderer::EntityRenderer(const string & vertexFile, const string & fragmentFile, ShaderBus& shaderBus) :
	p_shader(vertexFile, fragmentFile),
	p_shaderBus(shaderBus)
{
	
}