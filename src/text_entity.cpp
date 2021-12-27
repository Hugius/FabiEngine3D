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

void TextEntity::deleteCharacterEntities()
{
	_characterEntities.clear();
}

void TextEntity::updateCharacterEntities()
{
	float xCharSize = (this->getSize().x / static_cast<float>(this->_content.size()));
	float yCharSize = this->getSize().y;
	unsigned int index = 0;

	for(const auto& character : _characterEntities)
	{
		float xCharOffset = static_cast<float>(index) * xCharSize;
		float yCharOffset = 0.0f;

		if(_isCentered)
		{
			xCharOffset -= (this->getSize().x / 2.0f);
			yCharOffset -= (yCharSize / 2.0f);
		}

		character->setPosition(this->getPosition() + fvec2(xCharOffset, yCharOffset));
		character->setRotation(this->getRotation());
		character->setSize(fvec2(xCharSize, yCharSize));

		character->setColor(this->getColor());
		character->setMirroredHorizontally(this->isMirroredHorizonally());
		character->setMirroredVertically(this->isMirroredVertically());
		character->setTransparency(this->getTransparency());
		character->setMinPosition(this->getMinPosition());
		character->setMaxPosition(this->getMaxPosition());
		character->setVisible(this->isVisible());

		if(this->isVisible())
		{
			character->updateTransformationMatrix();
		}

		index++;
	}
}

void TextEntity::addCharacterEntity(shared_ptr<ImageEntity> value)
{
	_characterEntities.push_back(value);
}

const vector<shared_ptr<ImageEntity>>& TextEntity::getCharacterEntities() const
{
	return _characterEntities;
}