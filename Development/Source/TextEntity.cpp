#include "TextEntity.hpp"

void TextEntity::setTextContent(const string & text)
{
	_textContent = text;
}

void TextEntity::setFontName(const string& fontName)
{
	_fontName = fontName;
}

const string & TextEntity::getTextContent() const
{
	return _textContent;
}

const string& TextEntity::getFontName() const
{
	return _fontName;
}