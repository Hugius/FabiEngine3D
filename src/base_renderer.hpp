#pragma once

#include "shader_buffer.hpp"
#include "render_bus.hpp"

class BaseRenderer
{
public:
	BaseRenderer(const string& vertexPath, const string& fragmentPath, RenderBus& renderBus);

	// VOID
	virtual void bind() = 0;
	virtual void unbind() = 0;

protected:
	// MISCELLANEOUS
	ShaderBuffer _shader;
	RenderBus& _renderBus;
};