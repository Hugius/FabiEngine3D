#pragma once

#include "image_loader.hpp"
#include "terrain_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class TerrainEntityManager final
{
public:
	void inject(shared_ptr<ImageLoader> imageLoader);
	void createEntity(const string & id, const string & heightMapPath);
	void deleteEntity(const string & id);
	void deleteEntities();
	void loadVertexBuffer(const string & id);
	void selectEntity(const string & id);

	const unordered_map<string, shared_ptr<TerrainEntity>> & getEntities() const;

	const shared_ptr<TerrainEntity> getEntity(const string & id) const;
	const shared_ptr<TerrainEntity> getSelectedEntity() const;

	const float getPixelHeight(const string & id, float x, float z);

	const bool isEntityExisting(const string & id) const;
	const bool isEntitiesExisting() const;
	const bool isInside(const string & id, float x, float z);

private:
	void _loadVertexBuffer(shared_ptr<TerrainEntity> entity, float size, float maxHeight, const vector<float> & pixels);

	float _getPixelHeight(float x, float z, float size, float maxHeight, const vector<float> & pixels);

	static inline constexpr float MAX_SIZE = 1024.0f;

	unordered_map<string, shared_ptr<TerrainEntity>> _entities = {};

	shared_ptr<ImageLoader> _imageLoader = nullptr;

	string _selectedEntityId = "";
};