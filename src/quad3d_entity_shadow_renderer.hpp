#pragma once

#include "base_renderer.hpp"
#include "quad3d_entity.hpp"

class Quad3dEntityShadowRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(const shared_ptr<Quad3dEntity> entity);

private:
	static inline constexpr float MIN_TEXTURE_OPACITY = 0.25f;
};