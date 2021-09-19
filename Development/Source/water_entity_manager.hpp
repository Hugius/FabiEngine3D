#pragma once

#include "base_entity_manager.hpp"

class WaterEntityManager final : public BaseEntityManager
{
public:
	WaterEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	shared_ptr<WaterEntity> getEntity(const string& ID);
	shared_ptr<WaterEntity> getSelectedWater();

	const unordered_map<string, shared_ptr<WaterEntity>>& getEntities();

	void createEntity(const string& ID);
	void loadMesh(const string& ID);
	void selectWater(const string& ID);
	void update() override;

	static inline const unsigned int MAX_SIZE = 1024;

private:
	string _selectedID = "";
};