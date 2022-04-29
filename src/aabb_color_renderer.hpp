#pragma once

#include "base_renderer.hpp"
#include "aabb.hpp"

class AabbColorRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(const shared_ptr<Aabb> entity);
};