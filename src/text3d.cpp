#include "text3d.hpp"

#include <algorithm>

using std::max;
using std::clamp;
using std::make_shared;

Text3d::Text3d(const string & id)
	:
	_id(id)
{
	if(id.empty())
	{
		abort();
	}
}

void Text3d::updateTarget()
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
		const auto difference = Mathematics::calculateDifference(_rotation, _rotationTarget);
		const auto multiplier = fvec3(((difference.x < 180.0f) ? 1.0f : -1.0f), ((difference.y < 180.0f) ? 1.0f : -1.0f), ((difference.z < 180.0f) ? 1.0f : -1.0f));
		const auto speed = (fvec3(_rotationTargetSpeed) * multiplier);

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

void Text3d::updateQuad3ds()
{
	const auto rotationMatrix = Mathematics::createRotationMatrix(
		Mathematics::convertToRadians(_rotation.x),
		Mathematics::convertToRadians(_rotation.y),
		Mathematics::convertToRadians(_rotation.z), _rotationOrder);
	const auto quad3dSize = fvec2((this->getSize().x / static_cast<float>(this->_content.size())), this->getSize().y);

	int index = 0;

	for(const auto & quad3d : _quad3ds)
	{
		auto offset = fvec2((static_cast<float>(index) * quad3dSize.x), 0.0f);
		offset.x -= (this->getSize().x * 0.5f);
		offset.x += (quad3dSize.x * 0.5f);

		quad3d->setPosition(_position + (rotationMatrix * offset));
		quad3d->setRotation(_rotation);
		quad3d->setSize(quad3dSize);

		if(_isVisible)
		{
			quad3d->updateTransformation();
		}

		index++;
	}
}

void Text3d::setContent(const string & value)
{
	if(value != _content)
	{
		_content = value;
		_quad3ds.clear();

		for(const auto & character : _content)
		{
			const auto xIndex = _fontMapIndices.at(character).x;
			const auto yIndex = _fontMapIndices.at(character).y;
			const auto uvMultiplier = fvec2((1.0f / static_cast<float>(FONT_MAP_COLUMN_COUNT)), (1.0f / static_cast<float>(FONT_MAP_ROW_COUNT)));
			const auto uvOffset = fvec2((static_cast<float>(xIndex) * uvMultiplier.x), (static_cast<float>(yIndex) * uvMultiplier.y));
			const auto quad3d = make_shared<Quad3d>("dummy");

			quad3d->setVertexBuffer(_vertexBuffer);
			quad3d->setDiffuseMapPath(_fontMapPath);
			quad3d->setDiffuseMap(_fontTextureBuffer);
			quad3d->setOpacity(_opacity);
			quad3d->setMinAlpha(_minAlpha);
			quad3d->setWireframeColor(_wireframeColor);
			quad3d->setColor(_color);
			quad3d->setWireframed(_isWireframed);
			quad3d->setCentered(_isCentered);
			quad3d->setVisible(_isVisible);
			quad3d->setFacingCameraHorizontally(_isFacingCameraHorizontally);
			quad3d->setFacingCameraVertically(_isFacingCameraVertically);
			quad3d->setShadowed(_isShadowed);
			quad3d->setReflected(_isReflected);
			quad3d->setBright(_isBright);
			quad3d->setLightness(_lightness);
			quad3d->setMinClipPosition(_minClipPosition);
			quad3d->setMaxClipPosition(_maxClipPosition);
			quad3d->setUvMultiplier(uvMultiplier);
			quad3d->setUvOffset(uvOffset);

			_quad3ds.push_back(quad3d);
		}
	}
}

void Text3d::setVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_vertexBuffer = value;

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setVertexBuffer(_vertexBuffer);
	}
}

void Text3d::setFontMapPath(const string & value)
{
	_fontMapPath = value;

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setDiffuseMapPath(_fontMapPath);
	}
}

void Text3d::setFontMap(shared_ptr<TextureBuffer> value)
{
	_fontTextureBuffer = value;

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setDiffuseMap(_fontTextureBuffer);
	}
}

void Text3d::setFacingCameraHorizontally(bool value)
{
	_isFacingCameraHorizontally = value;

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setFacingCameraHorizontally(_isFacingCameraHorizontally);
	}
}

void Text3d::setFacingCameraVertically(bool value)
{
	_isFacingCameraVertically = value;

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setFacingCameraVertically(_isFacingCameraVertically);
	}
}

void Text3d::setColor(const fvec3 & value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setColor(_color);
	}
}

void Text3d::setWireframeColor(const fvec3 & value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setWireframeColor(_wireframeColor);
	}
}

void Text3d::setReflected(bool value)
{
	_isReflected = value;

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setReflected(_isReflected);
	}
}

void Text3d::setRefracted(bool value)
{
	_isRefracted = value;

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setRefracted(_isRefracted);
	}
}

void Text3d::setBright(bool value)
{
	_isBright = value;

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setBright(_isBright);
	}
}

void Text3d::setWireframed(bool value)
{
	_isWireframed = value;

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setWireframed(_isWireframed);
	}
}

void Text3d::setShadowed(bool value)
{
	_isShadowed = value;

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setShadowed(_isShadowed);
	}
}

void Text3d::setCentered(bool value)
{
	_isCentered = value;

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setCentered(_isCentered);
	}
}

void Text3d::setLightness(float value)
{
	_lightness = max(0.0f, value);

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setLightness(_lightness);
	}
}

void Text3d::setOpacity(float value)
{
	_opacity = clamp(value, 0.0f, 1.0f);

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setOpacity(_opacity);
	}
}

void Text3d::setMinClipPosition(const fvec3 & value)
{
	_minClipPosition = value;

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setMinClipPosition(_minClipPosition);
	}
}

void Text3d::setMaxClipPosition(const fvec3 & value)
{
	_maxClipPosition = value;

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setMaxClipPosition(_maxClipPosition);
	}
}

void Text3d::setMinAlpha(float value)
{
	_minAlpha = value;

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setMinAlpha(_minAlpha);
	}
}

void Text3d::setHorizontallyFlipped(bool value)
{
	_isHorizontallyFlipped = value;

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setHorizontallyFlipped(_isHorizontallyFlipped);
	}
}

void Text3d::setVerticallyFlipped(bool value)
{
	_isVerticallyFlipped = value;

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setVerticallyFlipped(_isVerticallyFlipped);
	}
}

void Text3d::setRotationOrder(DirectionOrderType value)
{
	_rotationOrder = value;
}

void Text3d::setVisible(bool value)
{
	_isVisible = value;

	for(const auto & quad3d : _quad3ds)
	{
		quad3d->setVisible(_isVisible);
	}
}

void Text3d::setPosition(const fvec3 & value)
{
	_position = value;
	_positionTarget = value;
}

void Text3d::setRotation(const fvec3 & value)
{
	_rotation = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
	_rotationTarget = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
}

void Text3d::setSize(const fvec2 & value)
{
	_size = fvec2(max(0.0f, value.x), max(0.0f, value.y));
	_sizeTarget = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void Text3d::move(const fvec3 & change)
{
	_position += change;
	_positionTarget += change;
}

void Text3d::rotate(const fvec3 & change)
{
	_rotation += change;
	_rotationTarget += change;
	_rotation = fvec3(Mathematics::limitAngle(_rotation.x), Mathematics::limitAngle(_rotation.y), Mathematics::limitAngle(_rotation.z));
	_rotationTarget = fvec3(Mathematics::limitAngle(_rotationTarget.x), Mathematics::limitAngle(_rotationTarget.y), Mathematics::limitAngle(_rotationTarget.z));
}

void Text3d::scale(const fvec2 & change)
{
	_size += change;
	_sizeTarget += change;
	_size = fvec2(max(0.0f, _size.x), max(0.0f, _size.y));
	_sizeTarget = fvec2(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y));
}

void Text3d::moveTo(const fvec3 & target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void Text3d::rotateTo(const fvec3 & target, float speed)
{
	_rotationTarget = fvec3(Mathematics::limitAngle(target.x), Mathematics::limitAngle(target.y), Mathematics::limitAngle(target.z));
	_rotationTargetSpeed = speed;
}

void Text3d::scaleTo(const fvec2 & target, float speed)
{
	_sizeTarget = fvec2(max(0.0f, target.x), max(0.0f, target.y));
	_sizeTargetSpeed = speed;
}

const string & Text3d::getId() const
{
	return _id;
}

const string & Text3d::getContent() const
{
	return _content;
}

const string & Text3d::getFontMapPath() const
{
	return _fontMapPath;
}

const vector<shared_ptr<Quad3d>> & Text3d::getQuad3ds() const
{
	return _quad3ds;
}

const shared_ptr<VertexBuffer> Text3d::getVertexBuffer() const
{
	return _vertexBuffer;
}

const shared_ptr<TextureBuffer> Text3d::getFontTextureBuffer() const
{
	return _fontTextureBuffer;
}

const mat44 & Text3d::getTransformation() const
{
	return _transformation;
}

const fvec3 & Text3d::getPosition() const
{
	return _position;
}

const fvec3 & Text3d::getRotation() const
{
	return _rotation;
}

const fvec2 & Text3d::getSize() const
{
	return _size;
}

const fvec2 & Text3d::getUvMultiplier() const
{
	return _uvMultiplier;
}

const fvec2 & Text3d::getUvOffset() const
{
	return _uvOffset;
}

const fvec3 & Text3d::getColor() const
{
	return _color;
}

const fvec3 & Text3d::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3 & Text3d::getMinClipPosition() const
{
	return _minClipPosition;
}

const fvec3 & Text3d::getMaxClipPosition() const
{
	return _maxClipPosition;
}

const float Text3d::getMinAlpha() const
{
	return _minAlpha;
}

const float Text3d::getLightness() const
{
	return _lightness;
}

const float Text3d::getOpacity() const
{
	return _opacity;
}

const bool Text3d::isVisible() const
{
	return _isVisible;
}

const bool Text3d::isFacingCameraHorizontally() const
{
	return _isFacingCameraHorizontally;
}

const bool Text3d::isFacingCameraVertically() const
{
	return _isFacingCameraVertically;
}

const bool Text3d::isShadowed() const
{
	return _isShadowed;
}

const bool Text3d::isReflected() const
{
	return _isReflected;
}

const bool Text3d::isRefracted() const
{
	return _isRefracted;
}

const bool Text3d::isBright() const
{
	return _isBright;
}

const bool Text3d::isWireframed() const
{
	return _isWireframed;
}

const bool Text3d::isCentered() const
{
	return _isCentered;
}

const bool Text3d::isHorizontallyFlipped() const
{
	return _isHorizontallyFlipped;
}

const bool Text3d::isVerticallyFlipped() const
{
	return _isVerticallyFlipped;
}

const DirectionOrderType Text3d::getRotationOrder() const
{
	return _rotationOrder;
}