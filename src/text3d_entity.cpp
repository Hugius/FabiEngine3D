#include "text3d_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;
using std::make_shared;

void Text3dEntity::updateTarget()
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
		if(fabsf(_positionTarget.z - _position.z) <= _positionTargetSpeed)
		{
			_position.z = _positionTarget.z;
		}
	}

	if(_rotation != _rotationTarget)
	{
		auto difference = Mathematics::calculateDifference(_rotation, _rotationTarget);
		auto multiplier = fvec3(((difference.x < 180.0f) ? 1.0f : -1.0f), ((difference.y < 180.0f) ? 1.0f : -1.0f), ((difference.z < 180.0f) ? 1.0f : -1.0f));
		auto speed = (fvec3(_rotationTargetSpeed) * multiplier);

		_rotation.x += ((_rotation.x < _rotationTarget.x) ? speed.x : (_rotation.x > _rotationTarget.x) ? -speed.x : 0.0f);
		_rotation.y += ((_rotation.y < _rotationTarget.y) ? speed.y : (_rotation.y > _rotationTarget.y) ? -speed.y : 0.0f);
		_rotation.z += ((_rotation.z < _rotationTarget.z) ? speed.z : (_rotation.z > _rotationTarget.z) ? -speed.z : 0.0f);

		_rotation = fvec3(Mathematics::limitAngle(_rotation.x), Mathematics::limitAngle(_rotation.y), Mathematics::limitAngle(_rotation.z));

		if(Mathematics::calculateAngleDifference(_rotation.x, _rotationTarget.x) <= _rotationTargetSpeed)
		{
			_rotation.x = _rotationTarget.x;
		}
		if(Mathematics::calculateAngleDifference(_rotation.y, _rotationTarget.y) <= _rotationTargetSpeed)
		{
			_rotation.y = _rotationTarget.y;
		}
		if(Mathematics::calculateAngleDifference(_rotation.z, _rotationTarget.z) <= _rotationTargetSpeed)
		{
			_rotation.z = _rotationTarget.z;
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

void Text3dEntity::updateCharacterEntities()
{
	const auto rotationMatrix = Mathematics::createRotationMatrix(
		Mathematics::convertToRadians(_rotation.x),
		Mathematics::convertToRadians(_rotation.y),
		Mathematics::convertToRadians(_rotation.z), _rotationOrder);
	const auto characterSize = fvec2((this->getSize().x / static_cast<float>(this->_content.size())), this->getSize().y);
	int index = 0;

	for(const auto & character : _characterEntities)
	{
		auto offset = fvec2((static_cast<float>(index) * characterSize.x), 0.0f);
		offset.x -= (this->getSize().x * 0.5f);
		offset.x += (characterSize.x * 0.5f);

		character->setPosition(_position + (rotationMatrix * offset));
		character->setRotation(_rotation);
		character->setSize(characterSize);

		if(_isVisible)
		{
			character->updateTransformation();
		}

		index++;
	}
}

void Text3dEntity::setContent(const string & value)
{
	if(value != _content)
	{
		_content = value;
		_characterEntities.clear();

		for(const auto & character : _content)
		{
			const auto xIndex = _fontMapIndices.at(character).x;
			const auto yIndex = _fontMapIndices.at(character).y;
			const auto uvMultiplier = fvec2((1.0f / static_cast<float>(FONT_MAP_COLUMN_COUNT)), (1.0f / static_cast<float>(FONT_MAP_ROW_COUNT)));
			const auto uvOffset = fvec2((static_cast<float>(xIndex) * uvMultiplier.x), (static_cast<float>(yIndex) * uvMultiplier.y));

			auto characterEntity = make_shared<Quad3dEntity>("dummy");
			characterEntity->setVertexBuffer(_vertexBuffer);
			characterEntity->setDiffuseMapPath(_fontMapPath);
			characterEntity->setDiffuseMap(_fontTextureBuffer);
			characterEntity->setOpacity(_opacity);
			characterEntity->setMinTextureAlpha(_minTextureAlpha);
			characterEntity->setWireframeColor(_wireframeColor);
			characterEntity->setColor(_color);
			characterEntity->setWireframed(_isWireframed);
			characterEntity->setCentered(_isCentered);
			characterEntity->setVisible(_isVisible);
			characterEntity->setFacingCameraHorizontally(_isFacingCameraHorizontally);
			characterEntity->setFacingCameraVertically(_isFacingCameraVertically);
			characterEntity->setShadowed(_isShadowed);
			characterEntity->setReflected(_isReflected);
			characterEntity->setBright(_isBright);
			characterEntity->setLightness(_lightness);
			characterEntity->setMinClipPosition(_minClipPosition);
			characterEntity->setMaxClipPosition(_maxClipPosition);
			characterEntity->setFrozen(_isFrozen);
			characterEntity->setUvMultiplier(uvMultiplier);
			characterEntity->setUvOffset(uvOffset);

			_characterEntities.push_back(characterEntity);
		}
	}
}

void Text3dEntity::setVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_vertexBuffer = value;

	for(const auto & character : _characterEntities)
	{
		character->setVertexBuffer(_vertexBuffer);
	}
}

void Text3dEntity::setFontMapPath(const string & value)
{
	_fontMapPath = value;

	for(const auto & character : _characterEntities)
	{
		character->setDiffuseMapPath(_fontMapPath);
	}
}

void Text3dEntity::setFontMap(shared_ptr<TextureBuffer> value)
{
	_fontTextureBuffer = value;

	for(const auto & character : _characterEntities)
	{
		character->setDiffuseMap(_fontTextureBuffer);
	}
}

void Text3dEntity::setFacingCameraHorizontally(bool value)
{
	_isFacingCameraHorizontally = value;

	for(const auto & character : _characterEntities)
	{
		character->setFacingCameraHorizontally(_isFacingCameraHorizontally);
	}
}

void Text3dEntity::setFacingCameraVertically(bool value)
{
	_isFacingCameraVertically = value;

	for(const auto & character : _characterEntities)
	{
		character->setFacingCameraVertically(_isFacingCameraVertically);
	}
}

void Text3dEntity::setColor(const fvec3 & value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));

	for(const auto & character : _characterEntities)
	{
		character->setColor(_color);
	}
}

void Text3dEntity::setWireframeColor(const fvec3 & value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));

	for(const auto & character : _characterEntities)
	{
		character->setWireframeColor(_wireframeColor);
	}
}

void Text3dEntity::setReflected(bool value)
{
	_isReflected = value;

	for(const auto & character : _characterEntities)
	{
		character->setReflected(_isReflected);
	}
}

void Text3dEntity::setBright(bool value)
{
	_isBright = value;

	for(const auto & character : _characterEntities)
	{
		character->setBright(_isBright);
	}
}

void Text3dEntity::setWireframed(bool value)
{
	_isWireframed = value;

	for(const auto & character : _characterEntities)
	{
		character->setWireframed(_isWireframed);
	}
}

void Text3dEntity::setShadowed(bool value)
{
	_isShadowed = value;

	for(const auto & character : _characterEntities)
	{
		character->setShadowed(_isShadowed);
	}
}

void Text3dEntity::setCentered(bool value)
{
	_isCentered = value;

	for(const auto & character : _characterEntities)
	{
		character->setCentered(_isCentered);
	}
}

void Text3dEntity::setLightness(float value)
{
	_lightness = max(0.0f, value);

	for(const auto & character : _characterEntities)
	{
		character->setLightness(_lightness);
	}
}

void Text3dEntity::setOpacity(float value)
{
	_opacity = clamp(value, 0.0f, 1.0f);

	for(const auto & character : _characterEntities)
	{
		character->setOpacity(_opacity);
	}
}

void Text3dEntity::setMinClipPosition(const fvec3 & value)
{
	_minClipPosition = value;

	for(const auto & character : _characterEntities)
	{
		character->setMinClipPosition(_minClipPosition);
	}
}

void Text3dEntity::setMaxClipPosition(const fvec3 & value)
{
	_maxClipPosition = value;

	for(const auto & character : _characterEntities)
	{
		character->setMaxClipPosition(_maxClipPosition);
	}
}

void Text3dEntity::setMinTextureAlpha(float value)
{
	_minTextureAlpha = value;

	for(const auto & character : _characterEntities)
	{
		character->setMinTextureAlpha(_minTextureAlpha);
	}
}

void Text3dEntity::setFrozen(bool value)
{
	_isFrozen = value;

	for(const auto & character : _characterEntities)
	{
		character->setFrozen(_isFrozen);
	}
}

void Text3dEntity::setHorizontallyFlipped(bool value)
{
	_isHorizontallyFlipped = value;

	for(const auto & character : _characterEntities)
	{
		character->setHorizontallyFlipped(_isHorizontallyFlipped);
	}
}

void Text3dEntity::setVerticallyFlipped(bool value)
{
	_isVerticallyFlipped = value;

	for(const auto & character : _characterEntities)
	{
		character->setVerticallyFlipped(_isVerticallyFlipped);
	}
}

void Text3dEntity::setRotationOrder(DirectionOrderType value)
{
	_rotationOrder = value;
}

void Text3dEntity::setVisible(bool value)
{
	_isVisible = value;

	for(const auto & character : _characterEntities)
	{
		character->setVisible(_isVisible);
	}
}

void Text3dEntity::setPosition(const fvec3 & value)
{
	_position = value;
	_positionTarget = value;
}

void Text3dEntity::setRotation(const fvec3 & value)
{
	_rotation = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
	_rotationTarget = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
}

void Text3dEntity::setSize(const fvec2 & value)
{
	_size = fvec2(max(0.0f, value.x), max(0.0f, value.y));
	_sizeTarget = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void Text3dEntity::move(const fvec3 & change)
{
	_position += change;
	_positionTarget += change;
}

void Text3dEntity::rotate(const fvec3 & change)
{
	_rotation += change;
	_rotationTarget += change;
	_rotation = fvec3(Mathematics::limitAngle(_rotation.x), Mathematics::limitAngle(_rotation.y), Mathematics::limitAngle(_rotation.z));
	_rotationTarget = fvec3(Mathematics::limitAngle(_rotationTarget.x), Mathematics::limitAngle(_rotationTarget.y), Mathematics::limitAngle(_rotationTarget.z));
}

void Text3dEntity::scale(const fvec2 & change)
{
	_size += change;
	_sizeTarget += change;
	_size = fvec2(max(0.0f, _size.x), max(0.0f, _size.y));
	_sizeTarget = fvec2(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y));
}

void Text3dEntity::moveTo(const fvec3 & target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void Text3dEntity::rotateTo(const fvec3 & target, float speed)
{
	_rotationTarget = fvec3(Mathematics::limitAngle(target.x), Mathematics::limitAngle(target.y), Mathematics::limitAngle(target.z));
	_rotationTargetSpeed = speed;
}

void Text3dEntity::scaleTo(const fvec2 & target, float speed)
{
	_sizeTarget = fvec2(max(0.0f, target.x), max(0.0f, target.y));
	_sizeTargetSpeed = speed;
}

const string & Text3dEntity::getContent() const
{
	return _content;
}

const string & Text3dEntity::getFontMapPath() const
{
	return _fontMapPath;
}

const vector<shared_ptr<Quad3dEntity>> & Text3dEntity::getCharacterEntities() const
{
	return _characterEntities;
}

const shared_ptr<VertexBuffer> Text3dEntity::getVertexBuffer() const
{
	return _vertexBuffer;
}

const shared_ptr<TextureBuffer> Text3dEntity::getFontTextureBuffer() const
{
	return _fontTextureBuffer;
}

const mat44 & Text3dEntity::getTransformation() const
{
	return _transformation;
}

const fvec3 & Text3dEntity::getPosition() const
{
	return _position;
}

const fvec3 & Text3dEntity::getRotation() const
{
	return _rotation;
}

const fvec2 & Text3dEntity::getSize() const
{
	return _size;
}

const fvec2 & Text3dEntity::getUvMultiplier() const
{
	return _uvMultiplier;
}

const fvec2 & Text3dEntity::getUvOffset() const
{
	return _uvOffset;
}

const fvec3 & Text3dEntity::getColor() const
{
	return _color;
}

const fvec3 & Text3dEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3 & Text3dEntity::getMinClipPosition() const
{
	return _minClipPosition;
}

const fvec3 & Text3dEntity::getMaxClipPosition() const
{
	return _maxClipPosition;
}

const float Text3dEntity::getMinTextureAlpha() const
{
	return _minTextureAlpha;
}

const float Text3dEntity::getLightness() const
{
	return _lightness;
}

const float Text3dEntity::getOpacity() const
{
	return _opacity;
}

const bool Text3dEntity::isFacingCameraHorizontally() const
{
	return _isFacingCameraHorizontally;
}

const bool Text3dEntity::isFacingCameraVertically() const
{
	return _isFacingCameraVertically;
}

const bool Text3dEntity::isShadowed() const
{
	return _isShadowed;
}

const bool Text3dEntity::isReflected() const
{
	return _isReflected;
}

const bool Text3dEntity::isBright() const
{
	return _isBright;
}

const bool Text3dEntity::isWireframed() const
{
	return _isWireframed;
}

const bool Text3dEntity::isCentered() const
{
	return _isCentered;
}

const bool Text3dEntity::isHorizontallyFlipped() const
{
	return _isHorizontallyFlipped;
}

const bool Text3dEntity::isVerticallyFlipped() const
{
	return _isVerticallyFlipped;
}

const DirectionOrderType Text3dEntity::getRotationOrder() const
{
	return _rotationOrder;
}

const bool Text3dEntity::isFrozen() const
{
	return _isFrozen;
}