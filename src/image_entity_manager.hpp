#pragma once

#include "render_bus.hpp"
#include "image_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class ImageEntityManager final
{
public:
	ImageEntityManager(RenderBus& renderBus);

	// VOID
	void update();
	void createEntity(const string& ID, bool isCentered);
	void deleteEntity(const string& ID);
	void deleteEntities();

	// BOOL
	const bool isEntityExisting(const string& ID);

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<ImageEntity>>& getEntities();
	shared_ptr<ImageEntity> getEntity(const string& ID);

private:
	// MISCELLANEOUS
	const shared_ptr<RenderBuffer> _centeredRenderBuffer;
	const shared_ptr<RenderBuffer> _nonCenteredRenderBuffer;
	unordered_map<string, shared_ptr<ImageEntity>> _entities;
	RenderBus& _renderBus;
};