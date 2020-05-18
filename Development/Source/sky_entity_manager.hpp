#pragma once
#include "base_entity_manager.hpp"

class SkyEntityManager final : public BaseEntityManager
{
public:
	SkyEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus);
	~SkyEntityManager() = default;

	SkyEntity * getEntity(const string & ID) override;
	SkyEntity * getSelectedSky();

	void selectSky(const string & ID);

	void addSkyEntity(const string & ID, float rotationSpeed, TextureLoader& texLoader, const vector<string> texturePaths);

	void update(float delta) override;

private:
	void _updateRotation(float delta);
	void _updateTextureMixing(float delta);
	void _updateEyeAdaption(float delta);

	string _selectedID = "";
};