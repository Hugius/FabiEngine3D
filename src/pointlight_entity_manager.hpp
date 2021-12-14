#pragma once

#include <unordered_map>

using std::unordered_map;

class PointlightEntityManager final
{
public:
	PointlightEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// VOID
	void update() override;
	void createEntity(const string& ID);
	void deleteEntity(const string& ID);
	void deleteEntities();

	// BOOL
	const bool isEntityExisting(const string& ID);

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<PointlightEntity>>& getEntities();
	shared_ptr<PointlightEntity> getEntity(const string& ID);

	// UNSIGNED INT
	static inline const unsigned int MAX_LIGHT_COUNT = 64;

private:
	// MISCELLANEOUS
	unordered_map<string, shared_ptr<PointlightEntity>> _entities;
};