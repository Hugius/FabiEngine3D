#pragma once
#include "EntityManager.hpp"

class SkyEntityManager final : public EntityManager
{
public:
	SkyEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus);
	~SkyEntityManager() = default;

	SkyEntity * getEntity(const string & ID) override;
	SkyEntity * getSelectedSky();

	void selectSky(const string & ID);

	void addSkyEntity
	(
		const string & ID, float rotationSpeed, TextureLoader& texLoader
	);

	void update(float delta) override;

private:
	void _updateRotation(float delta);
	void _updateBrightness(float delta);
	void _updateEyeAdaption(float delta);

	string _selectedID = "";
};