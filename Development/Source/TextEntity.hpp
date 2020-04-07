#pragma once
#include "GuiEntity.hpp"

class TextEntity final : public GuiEntity
{
public:
	TextEntity() = default;
	~TextEntity() = default;

	void setText(const string& text);
	void setFontName(const string& fontName);

	const string& getText() const;
	const string& getFontName() const;

private:
	string p_textContent = "";

	string p_fontName = "";
};