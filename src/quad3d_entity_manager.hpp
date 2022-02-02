#pragma once

#include "base_entity_manager.hpp"
#include "camera.hpp"
#include "quad3d_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class Quad3dEntityManager final : public BaseEntityManager
{
public:
	Quad3dEntityManager();

	void inject(shared_ptr<RenderStorage> renderStorage);
	void inject(shared_ptr<Camera> camera);
	void update();
	void createEntity(const string& id, bool isCentered);
	void deleteEntity(const string& id);
	void deleteEntities();

	const bool isEntityExisting(const string& id) const;

	const unordered_map<string, shared_ptr<Quad3dEntity>>& getEntities();
	shared_ptr<Quad3dEntity> getEntity(const string& id);

private:
	const shared_ptr<VertexBuffer> _centeredMesh;
	const shared_ptr<VertexBuffer> _standingMesh;

	unordered_map<string, shared_ptr<Quad3dEntity>> _entities;

	shared_ptr<RenderStorage> _renderStorage = nullptr;
	shared_ptr<Camera> _camera = nullptr;
};