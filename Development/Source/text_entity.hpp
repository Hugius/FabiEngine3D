#pragma once

#include "gui_entity.hpp"

class TextEntity final : public GuiEntity
{
public:
	TextEntity() = default;
	~TextEntity() = default;

	void setTextContent(const string& text);
	void setFontPath(const string& fontPath);

	const string& getTextContent() const;
	const string& getFontPath() const;

private:
	string _textContent = "";

	string _fontPath = "";
};