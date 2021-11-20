#pragma once

#include "shader_buffer.hpp"
#include "render_bus.hpp"

class BaseRenderer
{
public:
	BaseRenderer(const string& vertexFile, const string& fragmentFile, RenderBus& renderBus);

	// Voids
	virtual void bind() = 0;
	virtual void unbind() = 0;

protected:
	// Decimals
	static inline const float MIN_TEXTURE_TRANSPARENCY = 0.25f;

	// Miscellaneous
	ShaderBuffer _shader;
	RenderBus& _renderBus;
};