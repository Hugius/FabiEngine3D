#pragma once

#include "base_renderer.hpp"
#include "aabb_entity.hpp"

class AabbEntityColorRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(const shared_ptr<Aabb> entity);
};