#include "text3d_entity.hpp"
#include "logger.hpp"

#include <algorithm>

using std::max;
using std::clamp;
using std::make_shared;

void Text3dEntity::updateTransformation()
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
		if(fabsf(_positionTarget.z - _position.z) <= _positionTargetSpeed)
		{
			_position.z = _positionTarget.z;
		}
	}

	if(_rotation != _rotationTarget)
	{
		auto difference = Math::calculateDifference(_rotation, _rotationTarget);
		auto multiplier = fvec3(((difference.x < 180.0f) ? 1.0f : -1.0f), ((difference.y < 180.0f) ? 1.0f : -1.0f), ((difference.z < 180.0f) ? 1.0f : -1.0f));
		auto speed = (fvec3(_rotationTargetSpeed) * multiplier);

		_rotation.x += ((_rotation.x < _rotationTarget.x) ? speed.x : (_rotation.x > _rotationTarget.x) ? -speed.x : 0.0f);
		_rotation.y += ((_rotation.y < _rotationTarget.y) ? speed.y : (_rotation.y > _rotationTarget.y) ? -speed.y : 0.0f);
		_rotation.z += ((_rotation.z < _rotationTarget.z) ? speed.z : (_rotation.z > _rotationTarget.z) ? -speed.z : 0.0f);

		_rotation = fvec3(Math::limitAngle(_rotation.x), Math::limitAngle(_rotation.y), Math::limitAngle(_rotation.z));

		if(Math::calculateAngleDifference(_rotation.x, _rotationTarget.x) <= _rotationTargetSpeed)
		{
			_rotation.x = _rotationTarget.x;
		}
		if(Math::calculateAngleDifference(_rotation.y, _rotationTarget.y) <= _rotationTargetSpeed)
		{
			_rotation.y = _rotationTarget.y;
		}
		if(Math::calculateAngleDifference(_rotation.z, _rotationTarget.z) <= _rotationTargetSpeed)
		{
			_rotation.z = _rotationTarget.z;
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

void Text3dEntity::updateCharacterEntities()
{
	const auto rotationMatrix = Math::createRotationMatrix(
		Math::convertToRadians(_rotation.x),
		Math::convertToRadians(_rotation.y),
		Math::convertToRadians(_rotation.z), DirectionOrder::YXZ);
	const auto characterSize = fvec2((this->getSize().x / static_cast<float>(this->_content.size())), this->getSize().y);
	unsigned int index = 0;

	for(const auto& character : _characterEntities)
	{
		auto offset = fvec2((static_cast<float>(index) * characterSize.x), 0.0f);
		offset.x -= (this->getSize().x * 0.5f);
		offset.x += (characterSize.x * 0.5f);

		character->setPosition(_position + (rotationMatrix * offset));
		character->setRotation(_rotation);
		character->setSize(characterSize);

		if(_isVisible)
		{
			character->updateTransformationMatrix();
		}

		index++;
	}
}

void Text3dEntity::setContent(const string& value)
{
	if(value != _content)
	{
		_content = value;
		_characterEntities.clear();

		for(const auto& character : _content)
		{
			const auto xIndex = _fontMapIndices.at(character).x;
			const auto yIndex = _fontMapIndices.at(character).y;
			const auto uvMultiplier = fvec2((1.0f / static_cast<float>(FONT_MAP_COLUMN_COUNT)), (1.0f / static_cast<float>(FONT_MAP_ROW_COUNT)));
			const auto uvOffset = fvec2((static_cast<float>(xIndex) * uvMultiplier.x), (static_cast<float>(yIndex) * uvMultiplier.y));

			auto characterEntity = make_shared<Quad3dEntity>("dummy");
			characterEntity->setMesh(_mesh);
			characterEntity->setDiffuseMapPath(_fontMapPath);
			characterEntity->setDiffuseMap(_fontMap);
			characterEntity->setOpacity(_opacity);
			characterEntity->setWireframeColor(_wireframeColor);
			characterEntity->setColor(_color);
			characterEntity->setWireframed(_isWireframed);
			characterEntity->setCentered(_isCentered);
			characterEntity->setVisible(_isVisible);
			characterEntity->setFacingCameraX(_isFacingCameraX);
			characterEntity->setFacingCameraY(_isFacingCameraY);
			characterEntity->setDepthMapIncluded(_isDepthMapIncluded);
			characterEntity->setShadowed(_isShadowed);
			characterEntity->setReflected(_isReflected);
			characterEntity->setBright(_isBright);
			characterEntity->setLightness(_lightness);
			characterEntity->setMinHeight(_minHeight);
			characterEntity->setMaxHeight(_maxHeight);
			characterEntity->setFrozen(_isFrozen);
			characterEntity->setUvMultiplier(uvMultiplier);
			characterEntity->setUvOffset(uvOffset);

			_characterEntities.push_back(characterEntity);
		}
	}
}

void Text3dEntity::setMesh(shared_ptr<VertexBuffer> value)
{
	_mesh = value;

	for(const auto& character : _characterEntities)
	{
		character->setMesh(_mesh);
	}
}

void Text3dEntity::setFontMapPath(const string& value)
{
	_fontMapPath = value;

	for(const auto& character : _characterEntities)
	{
		character->setDiffuseMapPath(_fontMapPath);
	}
}

void Text3dEntity::setFontMap(shared_ptr<TextureBuffer> value)
{
	_fontMap = value;

	for(const auto& character : _characterEntities)
	{
		character->setDiffuseMap(_fontMap);
	}
}

void Text3dEntity::setFacingCameraX(bool value)
{
	_isFacingCameraX = value;

	for(const auto& character : _characterEntities)
	{
		character->setFacingCameraX(_isFacingCameraX);
	}
}

void Text3dEntity::setFacingCameraY(bool value)
{
	_isFacingCameraY = value;

	for(const auto& character : _characterEntities)
	{
		character->setFacingCameraY(_isFacingCameraY);
	}
}

void Text3dEntity::setColor(const fvec3& value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));

	for(const auto& character : _characterEntities)
	{
		character->setColor(_color);
	}
}

void Text3dEntity::setWireframeColor(const fvec3& value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));

	for(const auto& character : _characterEntities)
	{
		character->setWireframeColor(_wireframeColor);
	}
}

void Text3dEntity::setDepthMapIncluded(bool value)
{
	_isDepthMapIncluded = value;

	for(const auto& character : _characterEntities)
	{
		character->setDepthMapIncluded(_isDepthMapIncluded);
	}
}

void Text3dEntity::setReflected(bool value)
{
	_isReflected = value;

	for(const auto& character : _characterEntities)
	{
		character->setReflected(_isReflected);
	}
}

void Text3dEntity::setBright(bool value)
{
	_isBright = value;

	for(const auto& character : _characterEntities)
	{
		character->setBright(_isBright);
	}
}

void Text3dEntity::setWireframed(bool value)
{
	_isWireframed = value;

	for(const auto& character : _characterEntities)
	{
		character->setWireframeColor(_isWireframed);
	}
}

void Text3dEntity::setShadowed(bool value)
{
	_isShadowed = value;

	for(const auto& character : _characterEntities)
	{
		character->setShadowed(_isShadowed);
	}
}

void Text3dEntity::setCentered(bool value)
{
	_isCentered = value;

	for(const auto& character : _characterEntities)
	{
		character->setCentered(_isCentered);
	}
}

void Text3dEntity::setLightness(float value)
{
	_lightness = max(0.0f, value);

	for(const auto& character : _characterEntities)
	{
		character->setLightness(_lightness);
	}
}

void Text3dEntity::setOpacity(float value)
{
	_opacity = clamp(value, 0.0f, 1.0f);

	for(const auto& character : _characterEntities)
	{
		character->setOpacity(_opacity);
	}
}

void Text3dEntity::setMinHeight(float value)
{
	_minHeight = value;

	for(const auto& character : _characterEntities)
	{
		character->setMinHeight(_minHeight);
	}
}

void Text3dEntity::setMaxHeight(float value)
{
	_maxHeight = value;

	for(const auto& character : _characterEntities)
	{
		character->setMaxHeight(_maxHeight);
	}
}

void Text3dEntity::setFrozen(bool value)
{
	_isFrozen = value;

	for(const auto& character : _characterEntities)
	{
		character->setFrozen(_isFrozen);
	}
}

void Text3dEntity::setVisible(bool value)
{
	_isVisible = value;

	for(const auto& character : _characterEntities)
	{
		character->setVisible(_isVisible);
	}
}

void Text3dEntity::setPosition(const fvec3& value)
{
	_position = value;
	_positionTarget = value;
}

void Text3dEntity::setRotation(const fvec3& value)
{
	_rotation = fvec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
	_rotationTarget = fvec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
}

void Text3dEntity::setSize(const fvec2& value)
{
	_size = fvec2(max(0.0f, value.x), max(0.0f, value.y));
	_sizeTarget = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void Text3dEntity::move(const fvec3& value)
{
	_position += value;
	_positionTarget += value;
}

void Text3dEntity::rotate(const fvec3& value)
{
	_rotation += value;
	_rotationTarget += value;
	_rotation = fvec3(Math::limitAngle(_rotation.x), Math::limitAngle(_rotation.y), Math::limitAngle(_rotation.z));
	_rotationTarget = fvec3(Math::limitAngle(_rotationTarget.x), Math::limitAngle(_rotationTarget.y), Math::limitAngle(_rotationTarget.z));
}

void Text3dEntity::scale(const fvec2& value)
{
	_size += value;
	_sizeTarget += value;
	_size = fvec2(max(0.0f, _size.x), max(0.0f, _size.y));
	_sizeTarget = fvec2(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y));
}

void Text3dEntity::moveTo(const fvec3& target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void Text3dEntity::rotateTo(const fvec3& target, float speed)
{
	_rotationTarget = fvec3(Math::limitAngle(target.x), Math::limitAngle(target.y), Math::limitAngle(target.z));
	_rotationTargetSpeed = speed;
}

void Text3dEntity::scaleTo(const fvec2& target, float speed)
{
	_sizeTarget = fvec2(max(0.0f, target.x), max(0.0f, target.y));
	_sizeTargetSpeed = speed;
}

const string& Text3dEntity::getContent() const
{
	return _content;
}

const string& Text3dEntity::getFontMapPath() const
{
	return _fontMapPath;
}

const vector<shared_ptr<Quad3dEntity>>& Text3dEntity::getCharacterEntities() const
{
	return _characterEntities;
}

const shared_ptr<VertexBuffer> Text3dEntity::getMesh() const
{
	return _mesh;
}

const shared_ptr<TextureBuffer> Text3dEntity::getFontMap() const
{
	return _fontMap;
}

const mat44& Text3dEntity::getTransformationMatrix() const
{
	return _transformationMatrix;
}

const fvec3& Text3dEntity::getPosition() const
{
	return _position;
}

const fvec3& Text3dEntity::getRotation() const
{
	return _rotation;
}

const fvec2& Text3dEntity::getSize() const
{
	return _size;
}

const fvec2& Text3dEntity::getUvMultiplier() const
{
	return _uvMultiplier;
}

const fvec2& Text3dEntity::getUvOffset() const
{
	return _uvOffset;
}

const fvec3& Text3dEntity::getColor() const
{
	return _color;
}

const fvec3& Text3dEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const float Text3dEntity::getLightness() const
{
	return _lightness;
}

const float Text3dEntity::getOpacity() const
{
	return _opacity;
}

const float Text3dEntity::getMinHeight() const
{
	return _minHeight;
}

const float Text3dEntity::getMaxHeight() const
{
	return _maxHeight;
}

const bool Text3dEntity::isFacingCameraX() const
{
	return _isFacingCameraX;
}

const bool Text3dEntity::isFacingCameraY() const
{
	return _isFacingCameraY;
}

const bool Text3dEntity::isDepthMapIncluded() const
{
	return _isDepthMapIncluded;
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

const bool Text3dEntity::isFrozen() const
{
	return _isFrozen;
}