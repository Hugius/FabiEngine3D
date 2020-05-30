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
	void addWaterEntity(const string & ID, vec3 pos, float size);
	void update() override;

private:
	string _selectedID = "";
};