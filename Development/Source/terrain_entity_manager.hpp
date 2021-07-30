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
	void createEntity(const string& ID);
	void loadMesh(const string& ID);
	void update() override;

	float getPixelHeight(const string& ID, float x, float z);

	bool isInside(const string& ID, float x, float z);

private:
	void _loadNormalMapping(const string& ID);
	void _unloadNormalMapping(const string& ID);
	float _getPixelHeight(float x, float z, float size, float maxHeight, const vector<float>& pixelColors);

	string _selectedID = "";
};