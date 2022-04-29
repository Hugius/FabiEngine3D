#pragma once

#include "base_renderer.hpp"
#include "quad3d_entity.hpp"

class Quad3dShadowRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(const shared_ptr<Quad3d> entity);
};