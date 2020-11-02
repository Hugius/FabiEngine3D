#pragma once

#include "gui_entity.hpp"

#include <memory>

using std::shared_ptr;

class TextEntity final : public GuiEntity
{
public:
	using GuiEntity::GuiEntity;
	~TextEntity() = default;
	
	void setDynamic(bool value);
	void deleteCharacterEntities();
	void updateCharacterEntities();
	void addCharacterEntity(shared_ptr<GuiEntity> character);
	void setTextContent(const string& text);
	void setFontPath(const string& fontPath);

	bool isDynamic();
	const vector<shared_ptr<GuiEntity>>& getCharacterEntities() const;
	const string& getTextContent() const;
	const string& getFontPath() const;

private:
	vector<shared_ptr<GuiEntity>> _characters;

	string _textContent = "";

	string _fontPath = "";

	bool _isDynamic = false;
};