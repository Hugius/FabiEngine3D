#pragma once

#include "base_entity_manager.hpp"
#include "vertex_buffer.hpp"
#include "aabb_entity.hpp"
#include "model_entity_manager.hpp"
#include "quad3d_entity_manager.hpp"
#include "text3d_entity_manager.hpp"

#include <unordered_map>

using std::unordered_map;

class AabbEntityManager final : public BaseEntityManager
{
public:
	AabbEntityManager();

	void inject(shared_ptr<ModelEntityManager> modelEntityManager);
	void inject(shared_ptr<Quad3dEntityManager> quad3dEntityManager);
	void inject(shared_ptr<Text3dEntityManager> text3dEntityManager);
	void createEntity(const string& ID, bool isCentered);
	void update();
	void deleteEntity(const string& ID);
	void deleteEntities();

	const bool isEntityExisting(const string& ID) const;

	const unordered_map<string, shared_ptr<AabbEntity>>& getEntities();

	shared_ptr<AabbEntity> getEntity(const string& ID);

private:
	static inline constexpr float MIN_SIZE = 0.1f;

	const shared_ptr<VertexBuffer> _centeredMesh;
	const shared_ptr<VertexBuffer> _standingMesh;

	unordered_map<string, shared_ptr<AabbEntity>> _entities;

	shared_ptr<ModelEntityManager> _modelEntityManager = nullptr;
	shared_ptr<Quad3dEntityManager> _quad3dEntityManager = nullptr;
	shared_ptr<Text3dEntityManager> _text3dEntityManager = nullptr;
};