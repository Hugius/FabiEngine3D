#pragma once

#include "image_entity.hpp"
#include "render_buffer.hpp"

#include <memory>

using std::shared_ptr;

class TextEntity final : public ImageEntity
{
public:
	using ImageEntity::ImageEntity;

	void setCentered(bool value);
	void setDynamic(bool value);
	void addCharacterEntity(shared_ptr<ImageEntity> value);
	void updateCharacterEntities();
	void deleteCharacterEntities();
	void setContent(const string& value);
	void setFontPath(const string& value);

	const string& getContent() const;
	const string& getFontPath() const;

	const bool isCentered() const;
	const bool isDynamic() const;

	const vector<shared_ptr<ImageEntity>>& getCharacterEntities() const;

private:
	string _content = "";
	string _fontPath = "";

	bool _isCentered = false;
	bool _isDynamic = false;

	vector<shared_ptr<ImageEntity>> _characterEntities;
};