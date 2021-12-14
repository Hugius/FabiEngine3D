#pragma once

#include <unordered_map>

using std::unordered_map;

class SkyEntityManager final
{
public:
	SkyEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// VOID
	void update();
	void createEntity(const string& ID);
	void deleteEntity(const string& ID);
	void deleteEntities();
	void selectMainSky(const string& ID);
	void selectMixSky(const string& ID);
	void setExposureIntensity(float value);
	void setExposureSpeed(float value);
	void setExposureEnabled(bool value);

	// FLOAT
	const float getExposureIntensity() const;
	const float getExposureSpeed() const;

	// BOOL
	const bool isEntityExisting(const string& ID);
	const bool isExposureEnabled() const;

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<SkyEntity>>& getEntities();
	shared_ptr<SkyEntity> getEntity(const string& ID);
	shared_ptr<SkyEntity> getSelectedMainSky();
	shared_ptr<SkyEntity> getSelectedMixSky();

private:
	// STRING
	string _selectedMainID = "";
	string _selectedMixID = "";

	// FLOAT
	float _exposureIntensity = 0.0f;
	float _exposureSpeed = 0.0f;

	// BOOL
	bool _isExposureEnabled = false;

	// MISCELLANEOUS
	const shared_ptr<RenderBuffer> _renderBuffer;
	unordered_map<string, shared_ptr<SkyEntity>> _entities;
};