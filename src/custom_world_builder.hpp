#pragma once

#include "engine_interface.hpp"

class CustomWorldBuilder final
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void resetWorldBuild();
	void addLighting();
	void addGraphics();
	void addSky(const string& id);
	void addTerrain(const string& id);
	void addWater(const string& id);
	void addModel(const string& id);
	void addQuad3d(const string& id);
	void addText(const string& id);
	void addAabb(const string& id);
	void addSound(const string& id);
	void addPointlight(const string& id);
	void addSpotlight(const string& id);
	void addReflection(const string& id);
	void clearLoadedWorld();

	const bool loadWorldFromFile(const string& fileName);
	const bool saveWorldToFile(const string& fileName);

private:
	shared_ptr<EngineInterface> _fe3d = nullptr;

	vector<string> _addedSkyIds;
	vector<string> _addedTerrainIds;
	vector<string> _addedWaterIds;
	vector<string> _addedModelIds;
	vector<string> _addedQuadIds;
	vector<string> _addedTextIds;
	vector<string> _addedAabbIds;
	vector<string> _addedPointlightIds;
	vector<string> _addedSpotlightIds;
	vector<string> _addedReflectionIds;
	vector<string> _addedSoundIds;
	vector<string> _loadedSkyIds;
	vector<string> _loadedTerrainIds;
	vector<string> _loadedWaterIds;
	vector<string> _loadedModelIds;
	vector<string> _loadedQuadIds;
	vector<string> _loadedTextIds;
	vector<string> _loadedAabbIds;
	vector<string> _loadedPointlightIds;
	vector<string> _loadedSpotlightIds;
	vector<string> _loadedReflectionIds;
	vector<string> _loadedSoundIds;

	bool _hasAddedLighting = false;
	bool _hasAddedGraphics = false;
};