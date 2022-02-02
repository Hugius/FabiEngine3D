#pragma once

#include "shader_buffer.hpp"
#include "render_storage.hpp"

class BaseRenderer
{
public:
	void inject(shared_ptr<ShaderBuffer> shader);
	void inject(shared_ptr<RenderStorage> renderStorage);

	virtual void bind() = 0;
	virtual void unbind() = 0;

protected:
	shared_ptr<ShaderBuffer> _shader = nullptr;
	shared_ptr<RenderStorage> _renderStorage = nullptr;
};