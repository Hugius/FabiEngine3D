#pragma once
#include "EntityRenderer.hpp"
#include "GameEntity.hpp"
#include "LightEntity.hpp"

class GameEntityRenderer final : public EntityRenderer
{
public:
	using EntityRenderer::EntityRenderer;
	~GameEntityRenderer() = default;
	
	void bind()   override;
	void unbind() override;
	void placeLightEntity(const LightEntity * light);
	void render(const GameEntity * entity);

private:
	unsigned int _lightCounter = 0;
};