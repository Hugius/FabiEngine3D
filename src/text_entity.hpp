#pragma once

#include "image_entity.hpp"
#include "render_buffer.hpp"

#include <memory>

using std::shared_ptr;

class TextEntity final : public ImageEntity
{
public:
	using ImageEntity::ImageEntity;

	// VOID
	void setCentered(bool value);
	void setDynamic(bool value);
	void createCharacterEntity(shared_ptr<ImageEntity> character);
	void updateCharacterEntities();
	void deleteCharacterEntities();
	void setTextContent(const string& text);
	void setFontPath(const string& fontPath);

	// STRING
	const string& getTextContent() const;
	const string& getFontPath() const;

	// BOOL
	const bool isCentered() const;
	const bool isDynamic() const;

	// MISCELLANEOUS
	const vector<shared_ptr<ImageEntity>>& getCharacterEntities() const;

private:
	// STRING
	string _textContent = "";
	string _fontPath = "";

	// BOOL
	bool _isCentered = false;
	bool _isDynamic = false;

	// MISCELLANEOUS
	vector<shared_ptr<ImageEntity>> _characterEntities;
};