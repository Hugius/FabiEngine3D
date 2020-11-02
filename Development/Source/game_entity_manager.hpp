#pragma once

#include "base_entity_manager.hpp"

class GameEntityManager final :  public BaseEntityManager
{
public:
	GameEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus);
	~GameEntityManager() = default;

	shared_ptr<GameEntity> getEntity(const string& ID);

	const vector<shared_ptr<GameEntity>> getEntities();

	void addGameEntity
	(
		const string& ID, const string& objName,
		vec3 T, vec3 R, vec3 S
	);
	void loadNormalMapping(const string& ID);
	void setLodDistance(float distance);
	void update() override;

	float getLodDistance();

private:
	float _lodDistance = 0.0f;
};