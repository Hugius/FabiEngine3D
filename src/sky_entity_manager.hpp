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
	void createEntity(const string & skyId);
	void deleteEntity(const string & skyId);
	void deleteEntities();
	void selectEntity(const string & skyId);

	const unordered_map<string, shared_ptr<SkyEntity>> & getEntities() const;

	const shared_ptr<SkyEntity> getEntity(const string & skyId) const;
	const shared_ptr<SkyEntity> getSelectedEntity() const;

	const bool isEntityExisting(const string & skyId) const;
	const bool isEntitiesExisting() const;

private:
	const shared_ptr<VertexBuffer> _vertexBuffer;

	unordered_map<string, shared_ptr<SkyEntity>> _entities = {};

	shared_ptr<RenderStorage> _renderStorage = nullptr;

	string _selectedEntityId = "";
};