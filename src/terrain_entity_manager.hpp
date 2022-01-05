#pragma once

#include "base_entity_manager.hpp"
#include "image_loader.hpp"
#include "terrain_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class TerrainEntityManager final : public BaseEntityManager
{
public:
	void inject(shared_ptr<ImageLoader> imageLoader);
	void createEntity(const string& ID, const string& heightMapPath);
	void deleteEntity(const string& ID) override;
	void deleteEntities() override;
	void loadMesh(const string& ID);
	void selectTerrain(const string& ID);

	const float getPixelHeight(const string& ID, float x, float z);

	const bool isEntityExisting(const string& ID) const override;
	const bool isInside(const string& ID, float x, float z);

	const unordered_map<string, shared_ptr<TerrainEntity>>& getEntities();
	shared_ptr<TerrainEntity> getEntity(const string& ID);
	shared_ptr<TerrainEntity> getSelectedTerrain();

private:
	void _loadMesh(shared_ptr<TerrainEntity> entity, float size, float maxHeight, const vector<float>& pixels);

	float _getPixelHeight(float x, float z, float size, float maxHeight, const vector<float>& pixels);

	string _selectedID = "";

	static inline const float MAX_SIZE = 1024.0f;

	unordered_map<string, shared_ptr<TerrainEntity>> _entities;

	shared_ptr<ImageLoader> _imageLoader = nullptr;
};