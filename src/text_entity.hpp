#pragma once

#include "image_entity.hpp"
#include "render_buffer.hpp"

#include <memory>

using std::shared_ptr;

class TextEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	void setContent(const string& value);
	void setFontPath(const string& value);
	void addCharacterEntity(shared_ptr<ImageEntity> value);
	void updateCharacterEntities();
	void deleteCharacterEntities();

	const string& getContent() const;
	const string& getFontPath() const;

	const vector<shared_ptr<ImageEntity>>& getCharacterEntities() const;

private:
	string _content = "";
	string _fontPath = "";

	vector<shared_ptr<ImageEntity>> _characterEntities;
};