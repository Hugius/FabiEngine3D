#pragma once

#include <unordered_map>

using std::unordered_map;

class TextEntityManager final
{
public:
	TextEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// VOID
	void update() override;
	void createEntity(const string& ID, bool isCentered, bool isDynamic);
	void loadCharacters(const string& ID);
	void deleteDynamicTextEntity(const string& ID);
	void deleteEntities();

	// BOOL
	const bool isEntityExisting(const string& ID);

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<TextEntity>>& getEntities();
	shared_ptr<TextEntity> getEntity(const string& ID);

private:
	// STRING
	map<string, string> _contentMap;

	// MISCELLANEOUS
	const shared_ptr<RenderBuffer> _centeredRenderBuffer;
	const shared_ptr<RenderBuffer> _nonCenteredRenderBuffer;
	unordered_map<string, shared_ptr<TextEntity>> _entities;
};