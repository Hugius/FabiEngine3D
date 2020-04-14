#include "TextEntity.hpp"

void TextEntity::setTextContent(const string & text)
{
	_textContent = text;
}

void TextEntity::setFontPath(const string& fontPath)
{
	_fontPath = fontPath;
}

const string & TextEntity::getTextContent() const
{
	return _textContent;
}

const string& TextEntity::getFontPath() const
{
	return _fontPath;
}