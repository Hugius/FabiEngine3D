#pragma once

#include "image_entity.hpp"
#include "render_buffer.hpp"

#include <memory>

using std::shared_ptr;

class TextEntity final : public ImageEntity
{
public:
	using ImageEntity::ImageEntity;

	// Voids
	void setCentered(bool value);
	void setDynamic(bool value);
	void createCharacterEntity(shared_ptr<ImageEntity> character);
	void updateCharacterEntities();
	void deleteCharacterEntities();
	void setTextContent(const string& text);
	void setFontPath(const string& fontPath);

	// Strings
	const string& getTextContent() const;
	const string& getFontPath() const;

	// Booleans
	const bool isCentered() const;
	const bool isDynamic() const;

	// Miscellaneous
	const vector<shared_ptr<ImageEntity>>& getCharacterEntities() const;

private:
	// Strings
	string _textContent = "";
	string _fontPath = "";

	// Booleans
	bool _isCentered = false;
	bool _isDynamic = false;

	// Miscellaneous
	vector<shared_ptr<ImageEntity>> _characterEntities;
};