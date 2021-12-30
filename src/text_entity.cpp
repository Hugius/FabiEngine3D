#include "text_entity.hpp"
#include <iostream>

#include <algorithm>

using std::max;
using std::clamp;
using std::make_shared;

void TextEntity::setContent(const string& value)
{
	if(value != _content)
	{
		_content = value;
		_characterEntities.clear();

		for(const auto& character : _content)
		{
			auto xIndex = _fontMapIndices.at(character).x;
			auto yIndex = _fontMapIndices.at(character).y;
			auto multiplierUV = fvec2((1.0f / 16.0f), (1.0f / 6.0f));
			auto adderUV = fvec2((static_cast<float>(xIndex) * multiplierUV.x), (static_cast<float>(yIndex) * multiplierUV.y));

			auto characterEntity = make_shared<QuadEntity>("dummy");
			characterEntity->setRenderBuffer(_renderBuffer);
			characterEntity->setMultiplierUV(multiplierUV);
			characterEntity->setAdderUV(adderUV);

			_characterEntities.push_back(characterEntity);
		}
	}
}

void TextEntity::setFontMapPath(const string& value)
{
	_fontMapPath = value;
}

const string& TextEntity::getContent() const
{
	return _content;
}

const string& TextEntity::getFontMapPath() const
{
	return _fontMapPath;
}

void TextEntity::updateCharacterEntities()
{
	const auto characterSize = fvec2((this->getSize().x / static_cast<float>(this->_content.size())), this->getSize().y);
	unsigned int index = 0;

	for(const auto& character : _characterEntities)
	{
		if(_isCentered)
		{
			auto offset = fvec2((static_cast<float>(index) * characterSize.x), 0.0f);
			offset.x -= (this->getSize().x / 2.0f);
			offset.y -= (characterSize.y / 2.0f);
			character->setPosition(_position + offset);
		}
		else
		{
			auto offset = fvec2((static_cast<float>(index) * characterSize.x), 0.0f);
			character->setPosition(_position + offset);
		}

		character->setRotation(_rotation);
		character->setSize(characterSize);
		character->setColor(_color);
		character->setMirroredHorizontally(_isMirroredHorizontally);
		character->setMirroredVertically(_isMirroredVertically);
		character->setTransparency(_transparency);
		character->setMinPosition(_minPosition);
		character->setMaxPosition(_maxPosition);
		character->setVisible(_isVisible);
		character->setRenderBuffer(_renderBuffer);
		character->setCentered(_isCentered);
		character->setDepth(_depth);
		character->setDiffuseMap(_fontMap);
		character->setDiffuseMapPath(_fontMapPath);
		character->setWireframed(_isWireframed);

		if(_isVisible)
		{
			character->updateTransformationMatrix();
		}

		index++;
	}
}

const vector<shared_ptr<QuadEntity>>& TextEntity::getCharacterEntities() const
{
	return _characterEntities;
}

void TextEntity::updateTransformation()
{
	if(_position != _positionTarget)
	{
		auto speedMultiplier = Math::normalize(_positionTarget - _position);
		_position += (speedMultiplier * _positionTargetSpeed);

		if(fabsf(_positionTarget.x - _position.x) <= _positionTargetSpeed)
		{
			_position.x = _positionTarget.x;
		}
		if(fabsf(_positionTarget.y - _position.y) <= _positionTargetSpeed)
		{
			_position.y = _positionTarget.y;
		}
	}

	if(_rotation != _rotationTarget)
	{
		auto difference = fabsf(_rotation - _rotationTarget);
		float multiplier = ((difference < 180.0f) ? 1.0f : -1.0f);
		float speed = (_rotationTargetSpeed * multiplier);
		_rotation += ((_rotation < _rotationTarget) ? speed : (_rotation > _rotationTarget) ? -speed : 0.0f);

		_rotation = Math::limitAngle(_rotation);
		if(Math::calculateAngleDifference(_rotation, _rotationTarget) <= _rotationTargetSpeed)
		{
			_rotation = _rotationTarget;
		}
	}

	if(_size != _sizeTarget)
	{
		auto speedMultiplier = Math::normalize(_sizeTarget - _size);
		_size += (speedMultiplier * _sizeTargetSpeed);

		_size = fvec2(max(0.0f, _size.x), max(0.0f, _size.y));
		if(fabsf(_sizeTarget.x - _size.x) <= _sizeTargetSpeed)
		{
			_size.x = _positionTarget.x;
		}
		if(fabsf(_sizeTarget.y - _size.y) <= _sizeTargetSpeed)
		{
			_size.y = _positionTarget.y;
		}
	}
}

void TextEntity::setRenderBuffer(shared_ptr<RenderBuffer> value)
{
	_renderBuffer = value;
}

void TextEntity::setFontMap(TextureID value)
{
	_fontMap = value;
}

void TextEntity::setColor(fvec3 value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void TextEntity::setMirroredHorizontally(bool value)
{
	_isMirroredHorizontally = value;
}

void TextEntity::setMirroredVertically(bool value)
{
	_isMirroredVertically = value;
}

void TextEntity::setTransparency(float value)
{
	_transparency = clamp(value, 0.0f, 1.0f);
}

void TextEntity::setWireframeColor(fvec3 value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void TextEntity::setPosition(fvec2 value)
{
	_position = value;
	_positionTarget = value;
}

void TextEntity::setRotation(float value)
{
	_rotation = Math::limitAngle(value);
	_rotationTarget = Math::limitAngle(value);
}

void TextEntity::setSize(fvec2 value)
{
	_size = fvec2(max(0.0f, value.x), max(0.0f, value.y));
	_sizeTarget = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void TextEntity::move(fvec2 value)
{
	_position += value;
	_positionTarget += value;
}

void TextEntity::rotate(float value)
{
	_rotation += value;
	_rotationTarget += value;
	_rotation = Math::limitAngle(_rotation);
	_rotationTarget = Math::limitAngle(_rotationTarget);
}

void TextEntity::scale(fvec2 value)
{
	_size += value;
	_sizeTarget += value;
	_size = fvec2(max(0.0f, _size.x), max(0.0f, _size.y));
	_sizeTarget = fvec2(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y));
}

void TextEntity::moveTo(fvec2 target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void TextEntity::rotateTo(float target, float speed)
{
	_rotationTarget = Math::limitAngle(target);
	_rotationTargetSpeed = speed;
}

void TextEntity::scaleTo(fvec2 target, float speed)
{
	_sizeTarget = fvec2(max(0.0f, target.x), max(0.0f, target.y));
	_sizeTargetSpeed = speed;
}

void TextEntity::setMinPosition(fvec2 value)
{
	_minPosition = value;
}

void TextEntity::setMaxPosition(fvec2 value)
{
	_maxPosition = value;
}

void TextEntity::setDepth(unsigned int value)
{
	_depth = value;
}

const fvec3 TextEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3 TextEntity::getColor() const
{
	return _color;
}

const float TextEntity::getTransparency() const
{
	return _transparency;
}

const bool TextEntity::isWireframed() const
{
	return _isWireframed;
}

const bool TextEntity::isCentered() const
{
	return _isCentered;
}

const bool TextEntity::isMirroredHorizonally() const
{
	return _isMirroredHorizontally;
}

const bool TextEntity::isMirroredVertically() const
{
	return _isMirroredVertically;
}

const fvec2 TextEntity::getPosition() const
{
	return _position;
}

const float TextEntity::getRotation() const
{
	return _rotation;
}

const fvec2 TextEntity::getSize() const
{
	return _size;
}

const fvec2 TextEntity::getMinPosition() const
{
	return _minPosition;
}

const fvec2 TextEntity::getMaxPosition() const
{
	return _maxPosition;
}

const unsigned int TextEntity::getDepth() const
{
	return _depth;
}

void TextEntity::setWireframed(bool value)
{
	_isWireframed = value;
}

void TextEntity::setCentered(bool value)
{
	_isCentered = value;
}