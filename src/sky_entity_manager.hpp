#pragma once

#include "base_entity_manager.hpp"

class SkyEntityManager final : public BaseEntityManager
{
public:
	SkyEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// Voids
	void update() override;
	void createEntity(const string& ID);
	void selectMainSky(const string& ID);
	void selectMixSky(const string& ID);
	void setExposureIntensity(float value);
	void setExposureSpeed(float value);
	void setExposureEnabled(bool value);

	// Decimals
	const float getExposureIntensity() const;
	const float getExposureSpeed() const;

	// Booleans
	const bool isExposureEnabled() const;

	// Miscellaneous
	const unordered_map<string, shared_ptr<SkyEntity>>& getEntities();
	shared_ptr<SkyEntity> getEntity(const string& ID);
	shared_ptr<SkyEntity> getSelectedMainSky();
	shared_ptr<SkyEntity> getSelectedMixSky();

private:
	// Strings
	string _selectedMainID = "";
	string _selectedMixID = "";

	// Decimals
	float _exposureIntensity = 0.0f;
	float _exposureSpeed = 0.0f;

	// Booleans
	bool _isExposureEnabled = false;

	// Miscellaneous
	const shared_ptr<RenderBuffer> _renderBuffer;
};