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
	void addCharacterEntity(shared_ptr<ImageEntity> value);
	void updateCharacterEntities();
	void deleteCharacterEntities();
	void setContent(const string& value);
	void setFontPath(const string& value);

	// STRING
	const string& getContent() const;
	const string& getFontPath() const;

	// BOOL
	const bool isCentered() const;
	const bool isDynamic() const;

	// MISCELLANEOUS
	const vector<shared_ptr<ImageEntity>>& getCharacterEntities() const;

private:
	// STRING
	string _content = "";
	string _fontPath = "";

	// BOOL
	bool _isCentered = false;
	bool _isDynamic = false;

	// MISCELLANEOUS
	vector<shared_ptr<ImageEntity>> _characterEntities;
};