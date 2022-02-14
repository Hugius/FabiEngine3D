#pragma once

#include "engine_interface.hpp"

class World final
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void createCustomWorld(const string& id);
	void addLightingToCustomWorld();
	void addGraphicsToCustomWorld();
	void addSkyToCustomWorld();
	void addTerrainToCustomWorld();
	void addWaterToCustomWorld();
	void addModelToCustomWorld(const string& id);
	void addQuad3dToCustomWorld(const string& id);
	void addText3dToCustomWorld(const string& id);
	void addAabbToCustomWorld(const string& id);
	void addSoundToCustomWorld(const string& id);
	void addPointlightToCustomWorld(const string& id);
	void addSpotlightToCustomWorld(const string& id);
	void addReflectionToCustomWorld(const string& id);
	void unloadCustomWorld();

	const bool loadCustomWorldFromFile(const string& fileName);
	const bool saveCustomWorldToFile();
	const bool copyTemplateSky(const string& newId, const string& templateId);
	const bool copyTemplateTerrain(const string& newId, const string& templateId);
	const bool copyTemplateWater(const string& newId, const string& templateId);
	const bool copyTemplateModel(const string& newId, const string& templateId);
	const bool copyTemplateQuad3d(const string& newId, const string& templateId);
	const bool copyTemplateText3d(const string& newId, const string& templateId);
	const bool copyTemplateSound(const string& newId, const string& templateId);

private:
	shared_ptr<EngineInterface> _fe3d = nullptr;

	vector<string> _customWorldModelIds;
	vector<string> _customWorldQuadIds;
	vector<string> _customWorldTextIds;
	vector<string> _customWorldAabbIds;
	vector<string> _customWorldPointlightIds;
	vector<string> _customWorldSpotlightIds;
	vector<string> _customWorldReflectionIds;
	vector<string> _customWorldSoundIds;

	string _customWorldId = "";

	bool _hasCustomWorldLighting = false;
	bool _hasCustomWorldGraphics = false;
	bool _hasCustomWorldSky = false;
	bool _hasCustomWorldTerrain = false;
	bool _hasCustomWorldWater = false;
};