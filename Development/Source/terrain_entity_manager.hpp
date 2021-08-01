#pragma once

#include "base_entity_manager.hpp"

class TerrainEntityManager final : public BaseEntityManager
{
public:
	TerrainEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus);

	shared_ptr<TerrainEntity> getEntity(const string& ID);
	shared_ptr<TerrainEntity> getSelectedTerrain();

	const unordered_map<string, shared_ptr<TerrainEntity>>& getEntities();

	void selectTerrain(const string& ID);
	void createEntity(const string& ID, const string& heightMapPath);
	void loadMesh(const string& ID, const string& heightMapPath);
	void update() override;

	float getPixelHeight(const string& ID, float x, float z);

	bool isInside(const string& ID, float x, float z);

private:
	// Voids
	void _loadNormalMapping(const string& ID);
	void _unloadNormalMapping(const string& ID);

	// Strings
	string _selectedID = "";

	// Floats
	float _getPixelHeight(float x, float z, float size, float maxHeight, const vector<float>& pixelColors);
	static inline const unsigned int MAX_HEIGHT_MAP_RESOLUTION = 1024;
};