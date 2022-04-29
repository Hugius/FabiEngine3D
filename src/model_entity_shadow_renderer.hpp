#pragma once

#include "base_renderer.hpp"
#include "model_entity.hpp"

class ModelShadowRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(const shared_ptr<Model> entity);
};