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

	void addSkyEntity(const string & ID, TextureLoader& texLoader, const vector<string> texturePaths);

	void update() override;

private:
	void _updateRotation();
	void _updateTextureMixing();
	void _updateEyeAdaption();

	string _selectedID = "";
};