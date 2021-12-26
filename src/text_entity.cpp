#include "text_entity.hpp"

void TextEntity::setContent(const string& value)
{
	_content = value;
}

void TextEntity::setFontPath(const string& value)
{
	_fontPath = value;
}

const string& TextEntity::getContent() const
{
	return _content;
}

const string& TextEntity::getFontPath() const
{
	return _fontPath;
}