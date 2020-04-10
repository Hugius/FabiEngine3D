#pragma once
#include "GuiEntity.hpp"

class TextEntity final : public GuiEntity
{
public:
	TextEntity() = default;
	~TextEntity() = default;

	void setTextContent(const string& text);
	void setFontName(const string& fontName);

	const string& getTextContent() const;
	const string& getFontName() const;

private:
	string _textContent = "";

	string _fontName = "";
};