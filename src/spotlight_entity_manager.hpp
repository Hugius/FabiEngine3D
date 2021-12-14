#pragma once

#include <unordered_map>

using std::unordered_map;

class SpotlightEntityManager final
{
public:
	SpotlightEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// VOID
	void update() override;
	void createEntity(const string& ID);
	void deleteEntities();

	// BOOL
	const bool isEntityExisting(const string& ID);

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<SpotlightEntity>>& getEntities();
	shared_ptr<SpotlightEntity> getEntity(const string& ID);

	// UNSIGNED INT
	static inline const unsigned int MAX_LIGHT_COUNT = 64;

private:
	// MISCELLANEOUS
	unordered_map<string, shared_ptr<SpotlightEntity>> _entities;
};