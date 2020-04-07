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
		const string & ID, const string & dayDirectory, const string & nightDirectory, float rotationSpeed, TextureLoader& texLoader
	);

	void update(float delta) override;

private:
	void p_updateRotation(float delta);
	void p_updateBrightness(float delta);
	void p_updateEyeAdaption(float delta);

	string p_selectedID = "";
};