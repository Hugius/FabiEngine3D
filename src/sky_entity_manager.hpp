#pragma once

#include "render_storage.hpp"
#include "sky_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class SkyEntityManager final
{
public:
	SkyEntityManager();

	void inject(shared_ptr<RenderStorage> renderStorage);
	void update();
	void createEntity(const string& id);
	void deleteEntity(const string& id);
	void deleteEntities();
	void selectEntity(const string& id);

	const bool isEntityExisting(const string& id) const;
	const bool isEntitiesExisting() const;

	const unordered_map<string, shared_ptr<SkyEntity>>& getEntities() const;
	const shared_ptr<SkyEntity> getEntity(const string& id) const;
	const shared_ptr<SkyEntity> getSelectedEntity() const;

private:
	const shared_ptr<VertexBuffer> _vertexBuffer;

	unordered_map<string, shared_ptr<SkyEntity>> _entities = {};

	string _selectedEntityId = "";

	shared_ptr<RenderStorage> _renderStorage = nullptr;
};