#pragma once

#include "base_entity_manager.hpp"

class GameEntityManager final :  public BaseEntityManager
{
public:
	GameEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus);
	~GameEntityManager() = default;

	GameEntity * getEntity(const string& ID) override;

	const vector<GameEntity*> getEntities();

	void addGameEntity
	(
		const string& ID, const string& objName,
		vec3 T, vec3 R, vec3 S
	);
	void loadNormalMapping(const string& ID);

	void update() override;
};