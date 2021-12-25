#pragma once

#include "texture_loader.hpp"
#include "terrain_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class TerrainEntityManager final
{
public:
	TerrainEntityManager(TextureLoader& textureLoader);

	void createEntity(const string& ID, const string& heightMapPath);
	void deleteEntity(const string& ID);
	void deleteEntities();
	void loadMesh(const string& ID);
	void selectTerrain(const string& ID);

	const float getPixelHeight(const string& ID, float x, float z);

	const bool isEntityExisting(const string& ID);
	const bool isInside(const string& ID, float x, float z);

	const unordered_map<string, shared_ptr<TerrainEntity>>& getEntities();
	shared_ptr<TerrainEntity> getEntity(const string& ID);
	shared_ptr<TerrainEntity> getSelectedTerrain();

	static inline const unsigned int MAX_SIZE = 1024;

private:
	float _getPixelHeight(float x, float z, float size, float maxHeight, const vector<float>& pixels);

	string _selectedID = "";

	unordered_map<string, shared_ptr<TerrainEntity>> _entities;
	TextureLoader& _textureLoader;
};