#pragma once

#include "base_entity_manager.hpp"

class SkyEntityManager final : public BaseEntityManager
{
public:
	SkyEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	shared_ptr<SkyEntity> getEntity(const string& ID);
	shared_ptr<SkyEntity> getSelectedMainSky();
	shared_ptr<SkyEntity> getSelectedMixSky();

	const unordered_map<string, shared_ptr<SkyEntity>>& getEntities();

	void createEntity(const string& ID);
	void selectMainSky(const string& ID);
	void selectMixSky(const string& ID);
	void update() override;
	void setExposureIntensity(float intensity);
	void setExposureSpeed(float speed);

	float getSkyExposureIntensity();
	float getSkyExposureSpeed();

private:
	const shared_ptr<RenderBuffer> _renderBuffer;

	string _selectedMainID = "";
	string _selectedMixID = "";

	float _exposureIntensity = 0.0f;
	float _exposureSpeed = 0.0f;
};