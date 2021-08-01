#include "text_entity.hpp"

void TextEntity::setDynamic(bool value)
{
	_isDynamic = value;
}

void TextEntity::deleteCharacterEntities()
{
	_characterEntities.clear();
}

void TextEntity::updateCharacterEntities()
{
	// Temporary values
	float xCharSize = this->getSize().x / static_cast<float>(this->_textContent.size());
	float yCharSize = this->getSize().y;
	unsigned int index = 0;
	
	// Update every character
	for (const auto& character : _characterEntities)
	{
		// Temporary values
		float xCharOffset = static_cast<float>(index) * xCharSize;
		float yCharOffset = 0.0f;

		// Check if text is isCentered
		if (this->isCentered())
		{
			xCharOffset -= (this->getSize().x / 2.0f);
			yCharOffset -= (yCharSize / 2.0f);
		}

		// Set new transformation
		character->setPosition(this->getPosition() + Vec2(xCharOffset, yCharOffset));
		character->setRotation(this->getRotation());
		character->setSize(Vec2(xCharSize, yCharSize));

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

void TextEntity::addCharacterEntity(shared_ptr<ImageEntity> character)
{
	_characterEntities.push_back(character);
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

const vector<shared_ptr<ImageEntity>>& TextEntity::getCharacterEntities()
{
	return _characterEntities;
}

const string& TextEntity::getTextContent()
{
	return _textContent;
}

const string& TextEntity::getFontPath()
{
	return _fontPath;
}