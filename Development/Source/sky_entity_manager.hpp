#pragma once

#include "base_entity_manager.hpp"

class SkyEntityManager final : public BaseEntityManager
{
public:
	SkyEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus);

	shared_ptr<SkyEntity> getEntity(const string& ID);
	shared_ptr<SkyEntity> getSelectedMainSky();
	shared_ptr<SkyEntity> getSelectedMixSky();

	const unordered_map<string, shared_ptr<SkyEntity>>& getEntities();

	void selectMainSky(const string& ID);
	void selectMixSky(const string& ID);
	void createEntity(const string& ID);
	void update() override;
	void setExposureFactor(float skyExposureFactor);
	void setExposureSpeed(float speed);

	float getSkyExposureFactor();
	float getSkyExposureSpeed();

private:
	string _selectedMainID = "";
	string _selectedMixID = "";

	float _exposureFactor = 0.0f;
	float _exposureSpeed = 0.0f;
};