#include "text2d_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;
using std::make_shared;

void Text2dEntity::updateTarget()
{
	if(_position != _positionTarget)
	{
		const auto speedMultiplier = Mathematics::normalize(_positionTarget - _position);
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

		_rotation = Mathematics::limitAngle(_rotation);
		if(Mathematics::calculateAngleDifference(_rotation, _rotationTarget) <= _rotationTargetSpeed)
		{
			_rotation = _rotationTarget;
		}
	}

	if(_size != _sizeTarget)
	{
		const auto speedMultiplier = Mathematics::normalize(_sizeTarget - _size);
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

void Text2dEntity::updateCharacterEntities()
{
	const auto rotationMatrix = Mathematics::createRotationMatrixZ(Mathematics::convertToRadians(_rotation));
	const auto characterSize = fvec2((this->getSize().x / static_cast<float>(this->_content.size())), this->getSize().y);
	unsigned int index = 0;

	if(_isHorizontallyFlipped)
	{
		reverse(_characterEntities.begin(), _characterEntities.end());
	}

	for(const auto & character : _characterEntities)
	{
		auto offset = fvec2((static_cast<float>(index) * characterSize.x), 0.0f);

		if(_isCentered)
		{
			offset.x -= (this->getSize().x * 0.5f);
			offset.x += (characterSize.x * 0.5f);
		}

		character->setPosition(_position + (rotationMatrix * offset));
		character->setRotation(_rotation);
		character->setSize(characterSize);

		character->updateTransformation();

		index++;
	}

	if(_isHorizontallyFlipped)
	{
		reverse(_characterEntities.begin(), _characterEntities.end());
	}
}

void Text2dEntity::setContent(const string & value)
{
	if(value != _content)
	{
		_content = value;
		_characterEntities.clear();

		for(const auto & character : _content)
		{
			if(_fontMapIndices.find(character) == _fontMapIndices.end())
			{
				abort();
			}

			const auto xIndex = _fontMapIndices.at(character).x;
			const auto yIndex = _fontMapIndices.at(character).y;
			const auto uvMultiplier = fvec2((1.0f / static_cast<float>(FONT_MAP_COLUMN_COUNT)), (1.0f / static_cast<float>(FONT_MAP_ROW_COUNT)));
			const auto uvOffset = fvec2((static_cast<float>(xIndex) * uvMultiplier.x), (static_cast<float>(yIndex) * uvMultiplier.y));

			auto characterEntity = make_shared<Quad2dEntity>("dummy");
			characterEntity->setVertexBuffer(_vertexBuffer);
			characterEntity->setDiffuseMapPath(_fontMapPath);
			characterEntity->setDiffuseMap(_fontTextureBuffer);
			characterEntity->setHorizontallyFlipped(_isHorizontallyFlipped);
			characterEntity->setVerticallyFlipped(_isVerticallyFlipped);
			characterEntity->setOpacity(_opacity);
			characterEntity->setWireframeColor(_wireframeColor);
			characterEntity->setColor(_color);
			characterEntity->setMinClippingPosition(_minClippingPosition);
			characterEntity->setMaxClippingPosition(_maxClippingPosition);
			characterEntity->setDepth(_depth);
			characterEntity->setWireframed(_isWireframed);
			characterEntity->setCentered(_isCentered);
			characterEntity->setVisible(_isVisible);
			characterEntity->setUvMultiplier(uvMultiplier);
			characterEntity->setUvOffset(uvOffset);

			_characterEntities.push_back(characterEntity);
		}
	}
}

void Text2dEntity::setMinClippingPosition(const fvec2 & value)
{
	_minClippingPosition = value;

	for(const auto & character : _characterEntities)
	{
		character->setMinClippingPosition(_minClippingPosition);
	}
}

void Text2dEntity::setMaxClippingPosition(const fvec2 & value)
{
	_maxClippingPosition = value;

	for(const auto & character : _characterEntities)
	{
		character->setMaxClippingPosition(_maxClippingPosition);
	}
}

void Text2dEntity::setDepth(unsigned int value)
{
	_depth = value;

	for(const auto & character : _characterEntities)
	{
		character->setDepth(_depth);
	}
}

void Text2dEntity::setWireframed(bool value)
{
	_isWireframed = value;

	for(const auto & character : _characterEntities)
	{
		character->setWireframed(_isWireframed);
	}
}

void Text2dEntity::setCentered(bool value)
{
	_isCentered = value;

	for(const auto & character : _characterEntities)
	{
		character->setCentered(_isCentered);
	}
}

void Text2dEntity::setVisible(bool value)
{
	_isVisible = value;

	for(const auto & character : _characterEntities)
	{
		character->setVisible(_isVisible);
	}
}

void Text2dEntity::setFontMapPath(const string & value)
{
	_fontMapPath = value;

	for(const auto & character : _characterEntities)
	{
		character->setDiffuseMapPath(_fontMapPath);
	}
}

void Text2dEntity::setVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_vertexBuffer = value;

	for(const auto & character : _characterEntities)
	{
		character->setVertexBuffer(_vertexBuffer);
	}
}

void Text2dEntity::setFontMap(shared_ptr<TextureBuffer> value)
{
	_fontTextureBuffer = value;

	for(const auto & character : _characterEntities)
	{
		character->setDiffuseMap(_fontTextureBuffer);
	}
}

void Text2dEntity::setColor(const fvec3 & value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));

	for(const auto & character : _characterEntities)
	{
		character->setColor(_color);
	}
}

void Text2dEntity::setHorizontallyFlipped(bool value)
{
	_isHorizontallyFlipped = value;

	for(const auto & character : _characterEntities)
	{
		character->setHorizontallyFlipped(_isHorizontallyFlipped);
	}
}

void Text2dEntity::setVerticallyFlipped(bool value)
{
	_isVerticallyFlipped = value;

	for(const auto & character : _characterEntities)
	{
		character->setVerticallyFlipped(_isVerticallyFlipped);
	}
}

void Text2dEntity::setOpacity(float value)
{
	_opacity = clamp(value, 0.0f, 1.0f);

	for(const auto & character : _characterEntities)
	{
		character->setOpacity(_opacity);
	}
}

void Text2dEntity::setWireframeColor(const fvec3 & value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));

	for(const auto & character : _characterEntities)
	{
		character->setWireframeColor(_wireframeColor);
	}
}

void Text2dEntity::setPosition(const fvec2 & value)
{
	_position = value;
	_positionTarget = value;
}

void Text2dEntity::setRotation(float value)
{
	_rotation = Mathematics::limitAngle(value);
	_rotationTarget = Mathematics::limitAngle(value);
}

void Text2dEntity::setSize(const fvec2 & value)
{
	_size = fvec2(max(0.0f, value.x), max(0.0f, value.y));
	_sizeTarget = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void Text2dEntity::move(const fvec2 & value)
{
	_position += value;
	_positionTarget += value;
}

void Text2dEntity::rotate(float value)
{
	_rotation += value;
	_rotationTarget += value;
	_rotation = Mathematics::limitAngle(_rotation);
	_rotationTarget = Mathematics::limitAngle(_rotationTarget);
}

void Text2dEntity::scale(const fvec2 & value)
{
	_size += value;
	_sizeTarget += value;
	_size = fvec2(max(0.0f, _size.x), max(0.0f, _size.y));
	_sizeTarget = fvec2(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y));
}

void Text2dEntity::moveTo(const fvec2 & target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void Text2dEntity::rotateTo(float target, float speed)
{
	_rotationTarget = Mathematics::limitAngle(target);
	_rotationTargetSpeed = speed;
}

void Text2dEntity::scaleTo(const fvec2 & target, float speed)
{
	_sizeTarget = fvec2(max(0.0f, target.x), max(0.0f, target.y));
	_sizeTargetSpeed = speed;
}

const string & Text2dEntity::getContent() const
{
	return _content;
}

const string & Text2dEntity::getFontMapPath() const
{
	return _fontMapPath;
}

const vector<shared_ptr<Quad2dEntity>> & Text2dEntity::getCharacterEntities() const
{
	return _characterEntities;
}

const shared_ptr<VertexBuffer> Text2dEntity::getVertexBuffer() const
{
	return _vertexBuffer;
}

const shared_ptr<TextureBuffer> Text2dEntity::getFontTextureBuffer() const
{
	return _fontTextureBuffer;
}

const fvec3 & Text2dEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3 & Text2dEntity::getColor() const
{
	return _color;
}

const float Text2dEntity::getOpacity() const
{
	return _opacity;
}

const bool Text2dEntity::isWireframed() const
{
	return _isWireframed;
}

const bool Text2dEntity::isCentered() const
{
	return _isCentered;
}

const bool Text2dEntity::isFlippedHorizonally() const
{
	return _isHorizontallyFlipped;
}

const bool Text2dEntity::isVerticallyFlipped() const
{
	return _isVerticallyFlipped;
}

const fvec2 & Text2dEntity::getPosition() const
{
	return _position;
}

const float Text2dEntity::getRotation() const
{
	return _rotation;
}

const fvec2 & Text2dEntity::getSize() const
{
	return _size;
}

const fvec2 & Text2dEntity::getMinClippingPosition() const
{
	return _minClippingPosition;
}

const fvec2 & Text2dEntity::getMaxClippingPosition() const
{
	return _maxClippingPosition;
}

const unsigned int Text2dEntity::getDepth() const
{
	return _depth;
}