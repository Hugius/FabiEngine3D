#pragma once

#include "base_renderer.hpp"
#include "aabb.hpp"

class AabbDepthRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(shared_ptr<Aabb> aabb);
};