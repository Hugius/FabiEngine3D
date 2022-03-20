#pragma once

#include "shader_buffer.hpp"
#include "render_storage.hpp"
#include "camera.hpp"

class BaseRenderer
{
public:
	virtual void bind() = 0;
	virtual void unbind() = 0;

	void inject(shared_ptr<ShaderBuffer> shaderBuffer);
	void inject(shared_ptr<RenderStorage> renderStorage);
	void inject(shared_ptr<Camera> camera);

protected:
	shared_ptr<ShaderBuffer> _shaderBuffer = nullptr;
	shared_ptr<RenderStorage> _renderStorage = nullptr;
	shared_ptr<Camera> _camera = nullptr;
};