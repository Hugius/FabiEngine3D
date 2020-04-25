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
	void placeLightEntity(const LightEntity * light);
	void render(const GameEntity * entity);

private:
	unsigned int _lightCounter = 0;
};