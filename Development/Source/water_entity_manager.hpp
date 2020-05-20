#pragma once
#include "base_entity_manager.hpp"

class WaterEntityManager final : public BaseEntityManager
{
public:
	WaterEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus);
	~WaterEntityManager() = default;

	WaterEntity * getEntity(const string & ID) override;
	WaterEntity * getSelectedWater();

	void selectWater(const string & ID);

	void addWaterEntity
	(
		const string & ID, const string& dudvMapPath, const string& normalMapPath, vec3 pos, float size,
		float tileRepeat, float speed, bool waving, 
		bool rippling, vec3 color, float shininess
	);

	void update(float delta) override;

private:
	string _selectedID = "";
};