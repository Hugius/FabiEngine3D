#pragma once

#include "base_renderer.hpp"
#include "quad2d_entity.hpp"

class Quad2dEntityColorRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(const shared_ptr<Quad2d> entity);
};