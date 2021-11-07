#pragma once

#include "base_entity_manager.hpp"

class TextEntityManager final : public BaseEntityManager
{
public:
	TextEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);
	
	// Voids
	void update() override;
	void createEntity(const string& ID, bool isCentered, bool isDynamic);
	void loadCharacters(const string& ID);
	void deleteDynamicTextEntity(const string& ID);

	// Miscellaneous
	const unordered_map<string, shared_ptr<TextEntity>>& getEntities();
	shared_ptr<TextEntity> getEntity(const string& ID);

private:
	// Strings
	map<string, string> _textContentMap;

	// Miscellaneous
	const shared_ptr<RenderBuffer> _centeredRenderBuffer;
	const shared_ptr<RenderBuffer> _nonCenteredRenderBuffer;
};