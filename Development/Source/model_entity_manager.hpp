#pragma once

#include "base_entity_manager.hpp"

class ModelEntityManager final :  public BaseEntityManager
{
public:
	ModelEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus);

	shared_ptr<ModelEntity> getEntity(const string& ID);

	const unordered_map<string, shared_ptr<ModelEntity>>& getEntities();

	void addModelEntity(const string& ID, const string& meshPath, Vec3 T, Vec3 R, Vec3 S);
	void loadMesh(const string& ID, const string& meshPath);
	void setLodDistance(float distance);
	void update() override;

	float getLodDistance();

private:
	void _loadNormalMapping(const string& ID);
	void _unloadNormalMapping(const string& ID);

	float _lodDistance = 0.0f;
};