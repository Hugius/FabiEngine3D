#include <WE3D/TextEntity.hpp>

void TextEntity::setText(const string & text)
{
	p_textContent = text;
}

void TextEntity::setFontName(const string& fontName)
{
	p_fontName = fontName;
}

const string & TextEntity::getText() const
{
	return p_textContent;
}

const string& TextEntity::getFontName() const
{
	return p_fontName;
}