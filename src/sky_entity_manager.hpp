#pragma once

#include "render_storage.hpp"
#include "sky_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class SkyManager final
{
public:
	SkyManager();

	void inject(shared_ptr<RenderStorage> renderStorage);
	void update();
	void createEntity(const string & skyId);
	void deleteEntity(const string & skyId);
	void deleteEntities();
	void selectEntity(const string & skyId);

	const unordered_map<string, shared_ptr<Sky>> & getEntities() const;

	const shared_ptr<Sky> getEntity(const string & skyId) const;
	const shared_ptr<Sky> getSelectedEntity() const;

	const bool isEntityExisting(const string & skyId) const;
	const bool isEntitiesExisting() const;

private:
	const shared_ptr<VertexBuffer> _vertexBuffer;

	unordered_map<string, shared_ptr<Sky>> _entities = {};

	shared_ptr<RenderStorage> _renderStorage = nullptr;

	string _selectedEntityId = "";
};