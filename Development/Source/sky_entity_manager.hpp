#pragma once

#include "base_entity_manager.hpp"

class SkyEntityManager final : public BaseEntityManager
{
public:
	SkyEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus);
	~SkyEntityManager() = default;

	SkyEntity * getEntity(const string& ID) override;
	SkyEntity * getSelectedSky();

	const vector<SkyEntity*> getEntities();

	void selectSky(const string& ID);
	void addSkyEntity(const string& ID);
	void update() override;
	void setBrightnessFactor(float brightnessFactor);

	float getBrightnessFactor();

private:
	void _updateRotation();
	void _updateEyeAdaption();

	float _hdrBrightnessFactor = 0.0f;

	string _selectedID = "";
};