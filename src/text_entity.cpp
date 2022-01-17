#include "text_entity.hpp"
#include <iostream>

#include <algorithm>

using std::max;
using std::clamp;
using std::make_shared;

void Text2dEntity::setContent(const string& value)
{
	if(value != _content)
	{
		_content = value;
		_characterEntities.clear();

		for(const auto& character : _content)
		{
			auto xIndex = _fontMapIndices.at(character).x;
			auto yIndex = _fontMapIndices.at(character).y;
			auto uvMultiplier = fvec2((1.0f / 16.0f), (1.0f / 6.0f));
			auto uvOffset = fvec2((static_cast<float>(xIndex) * uvMultiplier.x), (static_cast<float>(yIndex) * uvMultiplier.y));

			auto characterEntity = make_shared<Quad2dEntity>("dummy");
			characterEntity->setMesh(_mesh);
			characterEntity->setUvMultiplier(uvMultiplier);
			characterEntity->setUvOffset(uvOffset);

			_characterEntities.push_back(characterEntity);
		}
	}
}

void Text2dEntity::setFontMapPath(const string& value)
{
	_fontMapPath = value;
}

const string& Text2dEntity::getContent() const
{
	return _content;
}

const string& Text2dEntity::getFontMapPath() const
{
	return _fontMapPath;
}

void Text2dEntity::updateCharacterEntities()
{
	const auto rotationMatrix = Math::createRotationMatrixZ(Math::convertToRadians(_rotation));
	const auto characterSize = fvec2((this->getSize().x / static_cast<float>(this->_content.size())), this->getSize().y);
	unsigned int index = 0;

	if(_isHorizontallyMirrored)
	{
		reverse(_characterEntities.begin(), _characterEntities.end());
	}

	for(const auto& character : _characterEntities)
	{
		auto offset = fvec2((static_cast<float>(index) * characterSize.x), 0.0f);

		if(_isCentered)
		{
			offset.x -= (this->getSize().x / 2.0f);
			offset.y -= (characterSize.y / 2.0f);
		}

		character->setPosition(_position + (rotationMatrix * offset));
		character->setRotation(_rotation);
		character->setSize(characterSize);
		character->setColor(_color);
		character->setWireframeColor(_wireframeColor);
		character->setHorizontallyMirrored(_isHorizontallyMirrored);
		character->setVerticallyMirrored(_isVerticallyMirrored);
		character->setTransparency(_transparency);
		character->setMinPosition(_minPosition);
		character->setMaxPosition(_maxPosition);
		character->setVisible(_isVisible);
		character->setMesh(_mesh);
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

	if(_isHorizontallyMirrored)
	{
		reverse(_characterEntities.begin(), _characterEntities.end());
	}
}

const vector<shared_ptr<Quad2dEntity>>& Text2dEntity::getCharacterEntities() const
{
	return _characterEntities;
}

const shared_ptr<VertexBuffer> Text2dEntity::getMesh() const
{
	return _mesh;
}

const shared_ptr<TextureBuffer> Text2dEntity::getFontMap() const
{
	return _fontMap;
}

void Text2dEntity::updateTransformation()
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

void Text2dEntity::setMesh(shared_ptr<VertexBuffer> value)
{
	_mesh = value;
}

void Text2dEntity::setFontMap(shared_ptr<TextureBuffer> value)
{
	_fontMap = value;
}

void Text2dEntity::setColor(fvec3 value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Text2dEntity::setHorizontallyMirrored(bool value)
{
	_isHorizontallyMirrored = value;
}

void Text2dEntity::setVerticallyMirrored(bool value)
{
	_isVerticallyMirrored = value;
}

void Text2dEntity::setTransparency(float value)
{
	_transparency = clamp(value, 0.0f, 1.0f);
}

void Text2dEntity::setWireframeColor(fvec3 value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Text2dEntity::setPosition(fvec2 value)
{
	_position = value;
	_positionTarget = value;
}

void Text2dEntity::setRotation(float value)
{
	_rotation = Math::limitAngle(value);
	_rotationTarget = Math::limitAngle(value);
}

void Text2dEntity::setSize(fvec2 value)
{
	_size = fvec2(max(0.0f, value.x), max(0.0f, value.y));
	_sizeTarget = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void Text2dEntity::move(fvec2 value)
{
	_position += value;
	_positionTarget += value;
}

void Text2dEntity::rotate(float value)
{
	_rotation += value;
	_rotationTarget += value;
	_rotation = Math::limitAngle(_rotation);
	_rotationTarget = Math::limitAngle(_rotationTarget);
}

void Text2dEntity::scale(fvec2 value)
{
	_size += value;
	_sizeTarget += value;
	_size = fvec2(max(0.0f, _size.x), max(0.0f, _size.y));
	_sizeTarget = fvec2(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y));
}

void Text2dEntity::moveTo(fvec2 target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void Text2dEntity::rotateTo(float target, float speed)
{
	_rotationTarget = Math::limitAngle(target);
	_rotationTargetSpeed = speed;
}

void Text2dEntity::scaleTo(fvec2 target, float speed)
{
	_sizeTarget = fvec2(max(0.0f, target.x), max(0.0f, target.y));
	_sizeTargetSpeed = speed;
}

void Text2dEntity::setMinPosition(fvec2 value)
{
	_minPosition = value;
}

void Text2dEntity::setMaxPosition(fvec2 value)
{
	_maxPosition = value;
}

void Text2dEntity::setDepth(unsigned int value)
{
	_depth = value;
}

const fvec3 Text2dEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3 Text2dEntity::getColor() const
{
	return _color;
}

const float Text2dEntity::getTransparency() const
{
	return _transparency;
}

const bool Text2dEntity::isWireframed() const
{
	return _isWireframed;
}

const bool Text2dEntity::isCentered() const
{
	return _isCentered;
}

const bool Text2dEntity::isMirroredHorizonally() const
{
	return _isHorizontallyMirrored;
}

const bool Text2dEntity::isVerticallyMirrored() const
{
	return _isVerticallyMirrored;
}

const fvec2 Text2dEntity::getPosition() const
{
	return _position;
}

const float Text2dEntity::getRotation() const
{
	return _rotation;
}

const fvec2 Text2dEntity::getSize() const
{
	return _size;
}

const fvec2 Text2dEntity::getMinPosition() const
{
	return _minPosition;
}

const fvec2 Text2dEntity::getMaxPosition() const
{
	return _maxPosition;
}

const unsigned int Text2dEntity::getDepth() const
{
	return _depth;
}

void Text2dEntity::setWireframed(bool value)
{
	_isWireframed = value;
}

void Text2dEntity::setCentered(bool value)
{
	_isCentered = value;
}