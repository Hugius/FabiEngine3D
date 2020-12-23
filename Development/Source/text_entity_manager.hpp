#pragma once

#include "base_entity_manager.hpp"

class TextEntityManager final : public BaseEntityManager
{
public:
	TextEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus);
	~TextEntityManager();

	shared_ptr<TextEntity> getEntity(const string& ID);

	const unordered_map<string, shared_ptr<TextEntity>>& getEntities();

	void addTextEntity
	(
		const string& ID, const string& textContent,
		const string& fontPath, Vec3 color,
		Vec2 translation, float rotation, Vec2 scaling,
		bool overwrite, bool isCentered, bool isDynamic
	);

	void reloadCharacters(const string& ID);
	void deleteDynamicTextEntity(const string& ID);
	void update() override;

private:
	OpenGLBuffer* _centeredOpenglBuffer = nullptr;
	OpenGLBuffer* _nonCenteredOpenglBuffer = nullptr;

	map<string, string> _textContentMap;
};