#pragma once

#include "base_entity_manager.hpp"

class SkyEntityManager final : public BaseEntityManager
{
public:
	SkyEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus);
	~SkyEntityManager() = default;

	SkyEntity * getEntity(const string& ID) override;
	SkyEntity * getSelectedSky();

	void selectSky(const string& ID);
	void addSkyEntity(const string& ID);
	void update() override;
	void saveHDRState(float brightnessFactor);

private:
	void _updateRotation();
	void _updateEyeAdaption();

	float _hdrBrightnessFactor = 0.0f;
	float _originalHdrSkyLightness = 0.0f;

	string _selectedID = "";
};