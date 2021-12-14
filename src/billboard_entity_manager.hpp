#pragma once

#include "render_buffer.hpp"
#include "camera.hpp"
#include "billboard_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class BillboardEntityManager final
{
public:
	BillboardEntityManager(RenderBus& renderBus, Camera& camera);

	// VOID
	void update();
	void createEntity(const string& ID);
	void deleteEntity(const string& ID);
	void deleteEntities();

	// BOOL
	const bool isEntityExisting(const string& ID);

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<BillboardEntity>>& getEntities();
	shared_ptr<BillboardEntity> getEntity(const string& ID);

private:
	// MISCELLANEOUS
	const shared_ptr<RenderBuffer> _renderBuffer;
	unordered_map<string, shared_ptr<BillboardEntity>> _entities;
	RenderBus& _renderBus;
	Camera& _camera;
};