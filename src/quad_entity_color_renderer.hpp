#pragma once

#include "base_renderer.hpp"
#include "quad_entity.hpp"

class Quad2dEntityColorRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(const shared_ptr<Quad2dEntity> entity);
};