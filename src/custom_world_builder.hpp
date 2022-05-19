#pragma once

#include "engine_interface.hpp"
#include "duplicator.hpp"

class CustomWorldBuilder final
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void inject(shared_ptr<Duplicator> duplicator);
	void setCurrentProjectId(const string & currentProjectId);
	void reset();
	void addSky(const string & skyId);
	void addTerrain(const string & terrainId);
	void addWater(const string & waterId);
	void addModel(const string & modelId);
	void addQuad3d(const string & quad3dId);
	void addText3d(const string & text3dId);
	void addAabb(const string & aabbId);
	void addPointlight(const string & pointlightId);
	void addSpotlight(const string & spotlightId);
	void addSound3d(const string & sound3dId);
	void addCaptor(const string & captorId);
	void addGraphics();
	void clearLoadedWorld();
	void saveWorldToFile(const string & fileName);

	const string & getLoadedWorldId() const;

	const bool loadWorldFromFile(const string & fileName);
	const bool isSkyAdded(const string & skyId) const;
	const bool isTerrainAdded(const string & terrainId) const;
	const bool isWaterAdded(const string & waterId) const;
	const bool isModelAdded(const string & modelId) const;
	const bool isQuad3dAdded(const string & quad3dId) const;
	const bool isText3dAdded(const string & text3dId) const;
	const bool isAabbAdded(const string & aabbId) const;
	const bool isPointlightAdded(const string & pointlightId) const;
	const bool isSpotlightAdded(const string & spotlightId) const;
	const bool isSound3dAdded(const string & sound3dId) const;
	const bool isCaptorAdded(const string & captorId) const;
	const bool isGraphicsAdded() const;

private:
	vector<pair<string, string>> _addedSkyIds = {};
	vector<pair<string, string>> _loadedSkyIds = {};
	vector<pair<string, string>> _addedTerrainIds = {};
	vector<pair<string, string>> _loadedTerrainIds = {};
	vector<pair<string, string>> _addedWaterIds = {};
	vector<pair<string, string>> _loadedWaterIds = {};
	vector<pair<string, string>> _addedModelIds = {};
	vector<pair<string, string>> _loadedModelIds = {};
	vector<pair<string, string>> _addedQuad3dIds = {};
	vector<pair<string, string>> _loadedQuad3dIds = {};
	vector<pair<string, string>> _addedText3dIds = {};
	vector<pair<string, string>> _loadedText3dIds = {};
	vector<pair<string, string>> _addedAabbIds = {};
	vector<pair<string, string>> _loadedAabbIds = {};
	vector<pair<string, string>> _addedPointlightIds = {};
	vector<pair<string, string>> _loadedPointlightIds = {};
	vector<pair<string, string>> _addedSpotlightIds = {};
	vector<pair<string, string>> _loadedSpotlightIds = {};
	vector<pair<string, string>> _addedSound3dIds = {};
	vector<pair<string, string>> _loadedSound3dIds = {};
	vector<string> _addedCaptorIds = {};
	vector<string> _loadedCaptorIds = {};

	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<Duplicator> _duplicator = nullptr;

	string _currentProjectId = "";
	string _loadedWorldId = "";

	bool _isGraphicsAdded = false;
	bool _isGraphicsLoaded = false;
};