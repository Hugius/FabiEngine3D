#pragma once

#include "base_entity_manager.hpp"
#include "render_bus.hpp"
#include "sky_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class SkyEntityManager final : public BaseEntityManager
{
public:
	SkyEntityManager();

	void inject(shared_ptr<RenderBus> renderBus);
	void update();
	void createEntity(const string& ID);
	void deleteEntity(const string& ID);
	void deleteEntities();
	void selectMainSky(const string& ID);
	void selectMixSky(const string& ID);
	void setExposureIntensity(float value);
	void setExposureSpeed(float value);
	void setExposureEnabled(bool value);

	const float getExposureIntensity() const;
	const float getExposureSpeed() const;

	const bool isEntityExisting(const string& ID) const;
	const bool isExposureEnabled() const;

	const unordered_map<string, shared_ptr<SkyEntity>>& getEntities();
	shared_ptr<SkyEntity> getEntity(const string& ID);
	shared_ptr<SkyEntity> getSelectedMainSky();
	shared_ptr<SkyEntity> getSelectedMixSky();

private:
	string _selectedMainID = "";
	string _selectedMixID = "";

	float _exposureIntensity = 0.0f;
	float _exposureSpeed = 0.0f;

	bool _isExposureEnabled = false;

	const shared_ptr<VertexBuffer> _mesh;

	unordered_map<string, shared_ptr<SkyEntity>> _entities;

	shared_ptr<RenderBus> _renderBus = nullptr;
};