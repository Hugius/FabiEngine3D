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
	void addSkyEntity(const string& ID);
	void update() override;
	void setSkyExposureFactor(float skyExposureFactor);

	float getSkyExposureFactor();

private:
	void _updateRotation();
	void _updateEyeAdaption();

	float _skyExposureFactor = 0.0f;

	string _selectedMainID = "";
	string _selectedMixID = "";
};