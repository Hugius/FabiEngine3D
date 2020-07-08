#pragma once
#include "base_entity_manager.hpp"

class TerrainEntityManager final : public BaseEntityManager
{
public:
	TerrainEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus);
	~TerrainEntityManager() = default;

	TerrainEntity * getEntity(const string & ID) override;
	TerrainEntity * getSelectedTerrain();

	void selectTerrain(const string & ID);

	float getPixelHeight(float x, float z);

	bool isInside(float x, float z);

	void addTerrainEntity
	(
		const string& ID, const string& heightmapPath, const string& textureName,
		vec3 pos, float size, float maxHeight, float uvRepeat, float lightness
	);

	void addBlendingToTerrain
	(
		const string& ID,
		const string& blendMap, const string& blendMapR, const string& blendMapG, const string& blendMapB,
		float blendRepeatR, float blendRepeatG, float blendRepeatB
	);

	void update() override {}

private:
	float _getPixelHeight(float x, float z, float size, float maxHeight, const vector<float>& pixelColors);

	string _selectedID = "";
};