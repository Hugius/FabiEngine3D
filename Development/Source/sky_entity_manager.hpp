#pragma once

#include "base_entity_manager.hpp"

class SkyEntityManager final : public BaseEntityManager
{
public:
	SkyEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// Voids
	void createEntity(const string& ID);
	void selectMainSky(const string& ID);
	void selectMixSky(const string& ID);
	void update() override;
	void setExposureIntensity(float value);
	void setExposureSpeed(float value);
	void setExposureEnabled(bool value);

	// Instances
	shared_ptr<SkyEntity> getEntity(const string& ID);
	shared_ptr<SkyEntity> getSelectedMainSky();
	shared_ptr<SkyEntity> getSelectedMixSky();
	const unordered_map<string, shared_ptr<SkyEntity>>& getEntities();

	// Floats
	const float getExposureIntensity();
	const float getExposureSpeed();

	// Booleans
	const bool isExposureEnabled();

private:
	// Instances
	const shared_ptr<RenderBuffer> _renderBuffer;

	// Strings
	string _selectedMainID = "";
	string _selectedMixID = "";

	// Floats
	float _exposureIntensity = 0.0f;
	float _exposureSpeed = 0.0f;

	// Booleans
	bool _isExposureEnabled = false;
};