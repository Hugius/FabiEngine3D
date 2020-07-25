#pragma once

#include "base_entity_renderer.hpp"
#include "game_entity.hpp"
#include "light_entity.hpp"

class GameEntityRenderer final : public BaseEntityRenderer
{
public:
	using BaseEntityRenderer::BaseEntityRenderer;
	~GameEntityRenderer() = default;
	
	void bind()   override;
	void unbind() override;
	void renderLightEntities(const vector<LightEntity*>& entities);
	void render(const GameEntity * entity);
};