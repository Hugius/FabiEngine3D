#include "TextEntity.hpp"

void TextEntity::setText(const string & text)
{
	_textContent = text;
}

void TextEntity::setFontName(const string& fontName)
{
	_fontName = fontName;
}

const string & TextEntity::getText() const
{
	return _textContent;
}

const string& TextEntity::getFontName() const
{
	return _fontName;
}