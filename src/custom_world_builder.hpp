#pragma once

#include "engine_interface.hpp"

class CustomWorldBuilder final
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
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
	vector<string> _addedSkyIds = {};
	vector<string> _addedTerrainIds = {};
	vector<string> _addedWaterIds = {};
	vector<string> _addedModelIds = {};
	vector<string> _addedQuad3dIds = {};
	vector<string> _addedText3dIds = {};
	vector<string> _addedAabbIds = {};
	vector<string> _addedPointlightIds = {};
	vector<string> _addedSpotlightIds = {};
	vector<string> _addedSound3dIds = {};
	vector<string> _addedCaptorIds = {};
	vector<string> _loadedSkyIds = {};
	vector<string> _loadedTerrainIds = {};
	vector<string> _loadedWaterIds = {};
	vector<string> _loadedModelIds = {};
	vector<string> _loadedQuad3dIds = {};
	vector<string> _loadedText3dIds = {};
	vector<string> _loadedAabbIds = {};
	vector<string> _loadedPointlightIds = {};
	vector<string> _loadedSpotlightIds = {};
	vector<string> _loadedSound3dIds = {};
	vector<string> _loadedCaptorIds = {};

	shared_ptr<EngineInterface> _fe3d = nullptr;

	string _currentProjectId = "";
	string _loadedWorldId = "";

	bool _isGraphicsAdded = false;
	bool _isGraphicsLoaded = false;
};