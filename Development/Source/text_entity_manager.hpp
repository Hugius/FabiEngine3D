#pragma once

#include "base_entity_manager.hpp"

class TextEntityManager final : public BaseEntityManager
{
public:
	TextEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus);

	shared_ptr<TextEntity> getEntity(const string& ID);

	const unordered_map<string, shared_ptr<TextEntity>>& getEntities();

	void createEntity(const string& ID, bool isCentered, bool isDynamic);

	void loadCharacters(const string& ID);
	void deleteDynamicTextEntity(const string& ID);
	void update() override;

private:
	const shared_ptr<RenderBuffer> _centeredRenderBuffer;
	const shared_ptr<RenderBuffer> _nonCenteredRenderBuffer;

	map<string, string> _textContentMap;
};