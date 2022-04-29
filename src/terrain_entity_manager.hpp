#pragma once

#include "image_loader.hpp"
#include "terrain_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class TerrainManager final
{
public:
	void inject(shared_ptr<ImageLoader> imageLoader);
	void createTerrain(const string & terrainId, const string & heightMapPath);
	void deleteTerrain(const string & terrainId);
	void deleteTerrains();
	void loadTerrainVertexBuffer(const string & terrainId);
	void selectTerrain(const string & terrainId);

	const unordered_map<string, shared_ptr<Terrain>> & getTerrains() const;

	const shared_ptr<Terrain> getTerrain(const string & terrainId) const;
	const shared_ptr<Terrain> getSelectedTerrain() const;

	const float getTerrainPixelHeight(const string & terrainId, float x, float z);

	const bool isTerrainExisting(const string & terrainId) const;
	const bool isTerrainsExisting() const;
	const bool isInside(const string & terrainId, float x, float z);

private:
	void _loadTerrainVertexBuffer(shared_ptr<Terrain> entity, float size, float maxHeight, const vector<float> & pixels);

	float _getTerrainPixelHeight(float x, float z, float size, float maxHeight, const vector<float> & pixels);

	static inline constexpr float MAX_TERRAIN_SIZE = 1024.0f;

	unordered_map<string, shared_ptr<Terrain>> _terrains = {};

	shared_ptr<ImageLoader> _imageLoader = nullptr;

	string _selectedTerrainId = "";
};