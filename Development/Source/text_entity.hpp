#pragma once

#include "image_entity.hpp"

#include <memory>

using std::shared_ptr;

class TextEntity final : public ImageEntity
{
public:
	using ImageEntity::ImageEntity;
	~TextEntity() = default;
	
	void setDynamic(bool value);
	void deleteCharacterEntities();
	void updateCharacterEntities();
	void addCharacterEntity(shared_ptr<ImageEntity> character);
	void setTextContent(const string& text);
	void setFontPath(const string& fontPath);

	bool isDynamic();
	const vector<shared_ptr<ImageEntity>>& getCharacterEntities() const;
	const string& getTextContent() const;
	const string& getFontPath() const;

private:
	vector<shared_ptr<ImageEntity>> _characters;

	string _textContent = "";

	string _fontPath = "";

	bool _isDynamic = false;
};