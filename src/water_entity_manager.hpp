#pragma once

#include "base_entity_manager.hpp"

class WaterEntityManager final : public BaseEntityManager
{
public:
	WaterEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// VOID
	void update() override;
	void createEntity(const string& ID);
	void loadMesh(const string& ID);
	void selectWater(const string& ID);

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<WaterEntity>>& getEntities();
	shared_ptr<WaterEntity> getEntity(const string& ID);
	shared_ptr<WaterEntity> getSelectedWater();

	// UNSIGNED INT
	static inline const unsigned int MAX_SIZE = 1024;

private:
	// STRING
	string _selectedID = "";
};