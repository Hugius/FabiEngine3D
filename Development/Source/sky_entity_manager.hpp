#pragma once

#include "base_entity_manager.hpp"

class SkyEntityManager final : public BaseEntityManager
{
public:
	SkyEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus);
	~SkyEntityManager() = default;

	shared_ptr<SkyEntity> getEntity(const string& ID);
	shared_ptr<SkyEntity> getSelectedMainSky();
	shared_ptr<SkyEntity> getSelectedMixSky();

	const unordered_map<string, shared_ptr<SkyEntity>>& getEntities();

	void selectMainSky(const string& ID);
	void selectMixSky(const string& ID);
	void addSkyEntity(const string& ID);
	void update() override;
	void setBrightnessFactor(float brightnessFactor);

	float getBrightnessFactor();

private:
	void _updateRotation();
	void _updateEyeAdaption();

	float _hdrBrightnessFactor = 0.0f;

	string _selectedMainID = "";
	string _selectedMixID = "";
};