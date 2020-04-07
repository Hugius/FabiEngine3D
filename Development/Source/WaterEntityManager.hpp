#pragma once
#include "EntityManager.hpp"

class WaterEntityManager final : public EntityManager
{
public:
	WaterEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus);
	~WaterEntityManager() = default;

	WaterEntity * getEntity(const string & ID) override;
	WaterEntity * getSelectedWater();

	void selectWater(const string & ID);

	void addWaterEntity
	(
		const string & ID, const string & assetName, vec3 pos, float size,
		float tileRepeat, float speed, bool waving, 
		bool rippling, vec3 color, float shininess
	);

	void update(float delta) override;

private:
	string p_selectedID = "";
};