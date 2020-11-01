#pragma once

#include "gui_entity.hpp"

class TextEntity final : public GuiEntity
{
public:
	TextEntity() = default;
	~TextEntity();
	
	void setDynamic(bool value);
	void deleteCharacterEntities();
	void updateCharacterEntities();
	void addCharacterEntity(GuiEntity* character);
	void setTextContent(const string& text);
	void setFontPath(const string& fontPath);

	bool isDynamic();
	const vector<GuiEntity*>& getCharacterEntities() const;
	const string& getTextContent() const;
	const string& getFontPath() const;

private:
	vector<GuiEntity*> _characters;

	string _textContent = "";

	string _fontPath = "";

	bool _isDynamic = false;
};