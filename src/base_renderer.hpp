#pragma once

#include "shader_buffer.hpp"
#include "render_bus.hpp"

class BaseRenderer
{
public:
	virtual void inject(shared_ptr<ShaderBuffer> shader);
	virtual void inject(shared_ptr<RenderBus> renderBus);

	virtual void bind() = 0;
	virtual void unbind() = 0;

protected:
	shared_ptr<ShaderBuffer> _shader = nullptr;
	shared_ptr<RenderBus> _renderBus = nullptr;
};