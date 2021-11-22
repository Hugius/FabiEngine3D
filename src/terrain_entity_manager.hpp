#pragma once

#include "base_entity_manager.hpp"

class TerrainEntityManager final : public BaseEntityManager
{
public:
	TerrainEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// VOID
	void update() override;
	void createEntity(const string& ID, const string& heightMapPath);
	void loadMesh(const string& ID);
	void selectTerrain(const string& ID);

	// FLOAT
	const float getPixelHeight(const string& ID, float x, float z);

	// BOOL
	const bool isInside(const string& ID, float x, float z);

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<TerrainEntity>>& getEntities();
	shared_ptr<TerrainEntity> getEntity(const string& ID);
	shared_ptr<TerrainEntity> getSelectedTerrain();

	// UNSIGNED INT
	static inline const unsigned int MAX_SIZE = 1024;

private:
	// STRING
	string _selectedID = "";

	// FLOAT
	float _getPixelHeight(float x, float z, float size, float maxHeight, const vector<float>& pixels);
};