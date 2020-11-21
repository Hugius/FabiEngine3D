#include "text_entity.hpp"

void TextEntity::setDynamic(bool value)
{
	_isDynamic = value;
}

void TextEntity::deleteCharacterEntities()
{
	_characters.clear();
}

void TextEntity::updateCharacterEntities()
{
	// Temporary values
	float xCharSize = this->getScaling().x / static_cast<float>(this->_textContent.size());
	float yCharSize = this->getScaling().y;
	unsigned int index = 0;
	
	// Update every character
	for (auto& character : _characters)
	{
		// Temporary values
		float xCharOffset = static_cast<float>(index) * xCharSize;
		float yCharOffset = 0.0f;

		// Check if text is isCentered
		if (this->isCentered())
		{
			xCharOffset -= (this->getScaling().x / 2.0f);
			yCharOffset -= (yCharSize / 2.0f);
		}

		// Set new transformation
		character->setTranslation(this->getTranslation() + Vec2(xCharOffset, yCharOffset));
		character->setRotation(this->getRotation());
		character->setScaling(Vec2(xCharSize, yCharSize));

		// Copy all properties
		character->setColor(this->getColor());
		character->setMirroredHorizontally(this->isMirroredHorizonally());
		character->setMirroredVertically(this->isMirroredVertically());
		character->setAlpha(this->getAlpha());
		character->setCentered(this->isCentered());
		character->setMinPosition(this->getMinPosition());
		character->setMaxPosition(this->getMaxPosition());
		character->setVisible(this->isVisible());
		character->updateModelMatrix();

		index++;
	}
}

void TextEntity::addCharacterEntity(shared_ptr<GuiEntity> character)
{
	_characters.push_back(character);
}

void TextEntity::setTextContent(const string& text)
{
	_textContent = text;
}

void TextEntity::setFontPath(const string& fontPath)
{
	_fontPath = fontPath;
}

bool TextEntity::isDynamic()
{
	return _isDynamic;
}

const vector<shared_ptr<GuiEntity>>& TextEntity::getCharacterEntities() const
{
	return _characters;
}

const string& TextEntity::getTextContent() const
{
	return _textContent;
}

const string& TextEntity::getFontPath() const
{
	return _fontPath;
}