#pragma once

#include "shader_buffer.hpp"
#include "render_bus.hpp"

class BaseRenderer
{
public:
	BaseRenderer(const string& vertexFile, const string& fragmentFile, RenderBus& renderBus);

	virtual void bind() = 0;
	virtual void unbind() = 0;

protected:
	ShaderBuffer _shader;

	RenderBus& _renderBus;

	static inline const float MIN_TEXTURE_ALPHA = 0.25f;
};