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
	void createEntity(const string& id, const string& heightMapPath);
	void deleteEntity(const string& id);
	void deleteEntities();
	void loadMesh(const string& id);
	void selectEntity(const string& id);

	const float getPixelHeight(const string& id, float x, float z);

	const bool isEntityExisting(const string& id) const;
	const bool isInside(const string& id, float x, float z);

	const unordered_map<string, shared_ptr<TerrainEntity>>& getEntities();
	shared_ptr<TerrainEntity> getEntity(const string& id);
	shared_ptr<TerrainEntity> getSelectedEntity();

private:
	void _loadMesh(shared_ptr<TerrainEntity> entity, float size, float maxHeight, const vector<float>& pixels);

	float _getPixelHeight(float x, float z, float size, float maxHeight, const vector<float>& pixels);

	string _selectedEntityId = "";

	static inline constexpr float MAX_SIZE = 1024.0f;

	unordered_map<string, shared_ptr<TerrainEntity>> _entities;

	shared_ptr<ImageLoader> _imageLoader = nullptr;
};