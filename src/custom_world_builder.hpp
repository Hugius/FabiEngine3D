#pragma once

#include "engine_interface.hpp"

class CustomWorldBuilder final
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void setCurrentProjectId(const string & currentProjectId);
	void resetWorldBuild();
	void addSky(const string & id);
	void addTerrain(const string & id);
	void addWater(const string & id);
	void addModel(const string & id);
	void addQuad3d(const string & id);
	void addText(const string & id);
	void addAabb(const string & id);
	void addPointlight(const string & id);
	void addSpotlight(const string & id);
	void addCaptor(const string & id);
	void addSound(const string & id);
	void addGraphics();
	void clearLoadedWorld();

	const string & getLoadedWorldId() const;

	const bool loadWorldFromFile(const string & fileName);
	const bool saveWorldToFile(const string & fileName) const;
	const bool isSkyAdded(const string & id) const;
	const bool isTerrainAdded(const string & id) const;
	const bool isWaterAdded(const string & id) const;
	const bool isModelAdded(const string & id) const;
	const bool isQuad3dAdded(const string & id) const;
	const bool isText3dAdded(const string & id) const;
	const bool isAabbAdded(const string & id) const;
	const bool isPointlightAdded(const string & id) const;
	const bool isSpotlightAdded(const string & id) const;
	const bool isCaptorAdded(const string & id) const;
	const bool isSound3dAdded(const string & id) const;
	const bool isGraphicsAdded() const;

private:
	vector<string> _addedSkyIds = {};
	vector<string> _addedTerrainIds = {};
	vector<string> _addedWaterIds = {};
	vector<string> _addedModelIds = {};
	vector<string> _addedQuad3dIds = {};
	vector<string> _addedText3dIds = {};
	vector<string> _addedAabbIds = {};
	vector<string> _addedPointlightIds = {};
	vector<string> _addedSpotlightIds = {};
	vector<string> _addedCaptorIds = {};
	vector<string> _addedSound3dIds = {};
	vector<string> _loadedSkyIds = {};
	vector<string> _loadedTerrainIds = {};
	vector<string> _loadedWaterIds = {};
	vector<string> _loadedModelIds = {};
	vector<string> _loadedQuad3dIds = {};
	vector<string> _loadedText3dIds = {};
	vector<string> _loadedAabbIds = {};
	vector<string> _loadedPointlightIds = {};
	vector<string> _loadedSpotlightIds = {};
	vector<string> _loadedCaptorIds = {};
	vector<string> _loadedSound3dIds = {};

	shared_ptr<EngineInterface> _fe3d = nullptr;

	string _currentProjectId = "";
	string _loadedWorldId = "";

	bool _isGraphicsAdded = false;
	bool _isGraphicsLoaded = false;
};