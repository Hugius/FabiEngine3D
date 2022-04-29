#pragma once

#include "camera.hpp"
#include "quad3d_entity.hpp"
#include "render_storage.hpp"

#include <unordered_map>

using std::unordered_map;

class Quad3dManager final
{
public:
	Quad3dManager();

	void inject(shared_ptr<RenderStorage> renderStorage);
	void inject(shared_ptr<Camera> camera);
	void update();
	void createEntity(const string & quad3dId, bool isCentered);
	void deleteEntity(const string & quad3dId);
	void deleteEntities();

	const unordered_map<string, shared_ptr<Quad3dEntity>> & getEntities() const;

	const shared_ptr<Quad3dEntity> getEntity(const string & quad3dId) const;

	const bool isEntityExisting(const string & quad3dId) const;
	const bool isEntitiesExisting() const;

private:
	const shared_ptr<VertexBuffer> _centeredVertexBuffer;
	const shared_ptr<VertexBuffer> _standingVertexBuffer;

	unordered_map<string, shared_ptr<Quad3dEntity>> _entities = {};

	shared_ptr<RenderStorage> _renderStorage = nullptr;
	shared_ptr<Camera> _camera = nullptr;
};