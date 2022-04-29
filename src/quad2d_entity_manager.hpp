#pragma once

#include "render_storage.hpp"
#include "quad2d_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class Quad2dManager final
{
public:
	Quad2dManager();

	void inject(shared_ptr<RenderStorage> renderStorage);
	void update();
	void createEntity(const string & quad2dId, bool isCentered);
	void deleteEntity(const string & quad2dId);
	void deleteEntities();

	const unordered_map<string, shared_ptr<Quad2dEntity>> & getEntities() const;

	const shared_ptr<Quad2dEntity> getEntity(const string & quad2dId) const;

	const bool isEntityExisting(const string & quad2dId) const;
	const bool isEntitiesExisting() const;

private:
	const shared_ptr<VertexBuffer> _centeredVertexBuffer;
	const shared_ptr<VertexBuffer> _corneredVertexBuffer;

	unordered_map<string, shared_ptr<Quad2dEntity>> _entities = {};

	shared_ptr<RenderStorage> _renderStorage = nullptr;
};