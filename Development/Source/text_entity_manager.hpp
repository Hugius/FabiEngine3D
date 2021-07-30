#pragma once

#include "base_entity_manager.hpp"

class TextEntityManager final : public BaseEntityManager
{
public:
	TextEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus);
	~TextEntityManager();

	shared_ptr<TextEntity> getEntity(const string& ID);

	const unordered_map<string, shared_ptr<TextEntity>>& getEntities();

	void createEntity
	(
		const string& ID, const string& textContent,
		const string& fontPath, Vec3 color,
		Vec2 position, float rotation, Vec2 size,
		bool overwrite, bool isCentered, bool isDynamic
	);

	void reloadCharacters(const string& ID);
	void deleteDynamicTextEntity(const string& ID);
	void update() override;

private:
	RenderBuffer* _centeredRenderBuffer = nullptr;
	RenderBuffer* _nonCenteredRenderBuffer = nullptr;

	map<string, string> _textContentMap;
};