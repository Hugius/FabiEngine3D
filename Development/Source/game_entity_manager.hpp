#pragma once

#include "base_entity_manager.hpp"

class GameEntityManager final :  public BaseEntityManager
{
public:
	GameEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus);
	~GameEntityManager() = default;

	shared_ptr<GameEntity> getEntity(const string& ID);

	const unordered_map<string, shared_ptr<GameEntity>>& getEntities();

	void addGameEntity(const string& ID, const string& meshPath, Vec3 T, Vec3 R, Vec3 S);
	void generateModel(const string& ID, const string& meshPath);
	void loadNormalMapping(const string& ID);
	void setLodDistance(float distance);
	void update() override;

	float getLodDistance();

private:
	float _lodDistance = 0.0f;
};