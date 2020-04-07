#pragma once
#include "EntityManager.hpp"

class TerrainEntityManager final : public EntityManager
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
		const string& ID, const string& heightmapName, const string& textureName,
		vec3 pos, float size, float maxHeight, float uvRepeat
	);

	void addBlendingToTerrain
	(
		const string& ID,
		const string& blendMap, const string& blendMapR, const string& blendMapG, const string& blendMapB,
		float blendRepeatR, float blendRepeatG, float blendRepeatB
	);

	void update(float delta) override {}

private:
	float p_getPixelHeight(float x, float z, float size, float height, const vector<float>& pixelColors);

	string p_selectedID = "";
};