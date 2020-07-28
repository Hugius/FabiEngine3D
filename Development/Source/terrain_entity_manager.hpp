#pragma once

#include "base_entity_manager.hpp"

class TerrainEntityManager final : public BaseEntityManager
{
public:
	TerrainEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus);
	~TerrainEntityManager() = default;

	TerrainEntity * getEntity(const string& ID) override;
	TerrainEntity * getSelectedTerrain();

	void selectTerrain(const string& ID);
	void addTerrain(const string& ID);
	void generateModel(const string& ID);
	void update() override {}

	float getPixelHeight(const string& ID, float x, float z);

	bool isInside(const string& ID, float x, float z);

private:
	float _getPixelHeight(float x, float z, float size, float maxHeight, const vector<float>& pixelColors);

	string _selectedID = "";
};