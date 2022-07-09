#pragma once

#include "base_renderer.hpp"
#include "model.hpp"

class ModelShadowRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(shared_ptr<Model> model);
};