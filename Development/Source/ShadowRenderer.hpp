#pragma once

#include "EntityRenderer.hpp"
#include "GameEntity.hpp"
#include "TerrainEntity.hpp"

class ShadowRenderer final : public EntityRenderer
{
public:
	using EntityRenderer::EntityRenderer;
	~ShadowRenderer() = default;

	void bind()   override;
	void unbind() override;
	void renderGameEntity(const GameEntity * entity);
};