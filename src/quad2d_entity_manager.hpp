#pragma once

#include "base_entity_manager.hpp"
#include "render_storage.hpp"
#include "quad2d_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class Quad2dEntityManager final : public BaseEntityManager
{
public:
	Quad2dEntityManager();

	void inject(shared_ptr<RenderStorage> renderStorage);
	void update();
	void createEntity(const string& id, bool isCentered);
	void deleteEntity(const string& id);
	void deleteEntities();

	const bool isEntityExisting(const string& id) const;
	const bool isEntitiesExisting() const;

	const unordered_map<string, shared_ptr<Quad2dEntity>>& getEntities();
	shared_ptr<Quad2dEntity> getEntity(const string& id);

private:
	const shared_ptr<VertexBuffer> _centeredMesh;
	const shared_ptr<VertexBuffer> _corneredMesh;

	unordered_map<string, shared_ptr<Quad2dEntity>> _entities;

	shared_ptr<RenderStorage> _renderStorage = nullptr;
};