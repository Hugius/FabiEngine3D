#pragma once

#include "base_entity_manager.hpp"

class TerrainEntityManager final : public BaseEntityManager
{
public:
	TerrainEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus);
	
	// Voids
	void createEntity(const string& ID, const string& heightMapPath);
	void loadMesh(const string& ID);
	void selectTerrain(const string& ID);
	void update() override;

	// Instances
	shared_ptr<TerrainEntity> getEntity(const string& ID);
	shared_ptr<TerrainEntity> getSelectedTerrain();
	const unordered_map<string, shared_ptr<TerrainEntity>>& getEntities();

	// Floats
	float getPixelHeight(const string& ID, float x, float z);

	// Booleans
	bool isInside(const string& ID, float x, float z);

	// Integers
	static inline const unsigned int MAX_SIZE = 1024;

private:
	// Strings
	string _selectedID = "";

	// Floats
	float _getPixelHeight(float x, float z, float size, float maxHeight, const vector<float>& pixelColors);
};