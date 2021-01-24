#pragma once

#include "base_entity_manager.hpp"

class TerrainEntityManager final : public BaseEntityManager
{
public:
	TerrainEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus);
	~TerrainEntityManager() = default;

	shared_ptr<TerrainEntity> getEntity(const string& ID);
	shared_ptr<TerrainEntity> getSelectedTerrain();

	const unordered_map<string, shared_ptr<TerrainEntity>>& getEntities();

	void selectTerrain(const string& ID);
	void addTerrain(const string& ID);
	void generateModel(const string& ID);
	void loadNormalMapping(const string& ID);
	void update() override;

	float getPixelHeight(const string& ID, float x, float z);

	bool isInside(const string& ID, float x, float z);

private:
	float _getPixelHeight(float x, float z, float size, float maxHeight, const vector<float>& pixelColors);

	string _selectedID = "";
};