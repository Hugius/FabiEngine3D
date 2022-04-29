#pragma once

#include "base_renderer.hpp"
#include "quad2d.hpp"

class DofRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(const shared_ptr<Quad2d> entity);
};