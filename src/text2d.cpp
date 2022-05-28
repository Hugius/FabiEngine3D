#include "text2d.hpp"

#include <algorithm>

using std::max;
using std::clamp;
using std::make_shared;

Text2d::Text2d(const string & id)
	:
	_id(id)
{
	if(id.empty())
	{
		abort();
	}
}

void Text2d::updateTarget()
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
		const auto difference = fabsf(_rotation - _rotationTarget);
		const auto multiplier = ((difference < 180.0f) ? 1.0f : -1.0f);
		const auto speed = (_rotationTargetSpeed * multiplier);

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

void Text2d::updateQuad2ds()
{
	const auto rotationMatrix = Mathematics::createRotationMatrixZ(Mathematics::convertToRadians(_rotation));
	const auto quad2dSize = fvec2((this->getSize().x / static_cast<float>(this->_content.size())), this->getSize().y);

	int index = 0;

	if(_isHorizontallyFlipped)
	{
		reverse(_quad2ds.begin(), _quad2ds.end());
	}

	for(const auto & quad2d : _quad2ds)
	{
		auto offset = fvec2((static_cast<float>(index) * quad2dSize.x), 0.0f);

		if(_isCentered)
		{
			offset.x -= (this->getSize().x * 0.5f);
			offset.x += (quad2dSize.x * 0.5f);
		}

		quad2d->setPosition(_position + (rotationMatrix * offset));
		quad2d->setRotation(_rotation);
		quad2d->setSize(quad2dSize);

		quad2d->updateTransformation();

		index++;
	}

	if(_isHorizontallyFlipped)
	{
		reverse(_quad2ds.begin(), _quad2ds.end());
	}
}

void Text2d::setContent(const string & value)
{
	if(value != _content)
	{
		_content = value;
		_quad2ds.clear();

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
			const auto quad2d = make_shared<Quad2d>("dummy");

			quad2d->setVertexBuffer(_vertexBuffer);
			quad2d->setDiffuseMapPath(_fontMapPath);
			quad2d->setDiffuseMap(_fontTextureBuffer);
			quad2d->setHorizontallyFlipped(_isHorizontallyFlipped);
			quad2d->setVerticallyFlipped(_isVerticallyFlipped);
			quad2d->setOpacity(_opacity);
			quad2d->setWireframeColor(_wireframeColor);
			quad2d->setColor(_color);
			quad2d->setMinClipPosition(_minClipPosition);
			quad2d->setMaxClipPosition(_maxClipPosition);
			quad2d->setDepth(_depth);
			quad2d->setWireframed(_isWireframed);
			quad2d->setCentered(_isCentered);
			quad2d->setVisible(_isVisible);
			quad2d->setUvMultiplier(uvMultiplier);
			quad2d->setUvOffset(uvOffset);

			_quad2ds.push_back(quad2d);
		}
	}
}

void Text2d::setMinClipPosition(const fvec2 & value)
{
	_minClipPosition = value;

	for(const auto & quad2d : _quad2ds)
	{
		quad2d->setMinClipPosition(_minClipPosition);
	}
}

void Text2d::setMaxClipPosition(const fvec2 & value)
{
	_maxClipPosition = value;

	for(const auto & quad2d : _quad2ds)
	{
		quad2d->setMaxClipPosition(_maxClipPosition);
	}
}

void Text2d::setDepth(int value)
{
	_depth = max(0, value);

	for(const auto & quad2d : _quad2ds)
	{
		quad2d->setDepth(_depth);
	}
}

void Text2d::setWireframed(bool value)
{
	_isWireframed = value;

	for(const auto & quad2d : _quad2ds)
	{
		quad2d->setWireframed(_isWireframed);
	}
}

void Text2d::setCentered(bool value)
{
	_isCentered = value;

	for(const auto & quad2d : _quad2ds)
	{
		quad2d->setCentered(_isCentered);
	}
}

void Text2d::setVisible(bool value)
{
	_isVisible = value;

	for(const auto & quad2d : _quad2ds)
	{
		quad2d->setVisible(_isVisible);
	}
}

void Text2d::setLightness(float value)
{
	_lightness = max(0.0f, value);

	for(const auto & quad2d : _quad2ds)
	{
		quad2d->setLightness(_lightness);
	}
}

void Text2d::setFontMapPath(const string & value)
{
	_fontMapPath = value;

	for(const auto & quad2d : _quad2ds)
	{
		quad2d->setDiffuseMapPath(_fontMapPath);
	}
}

void Text2d::setVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_vertexBuffer = value;

	for(const auto & quad2d : _quad2ds)
	{
		quad2d->setVertexBuffer(_vertexBuffer);
	}
}

void Text2d::setFontMap(shared_ptr<TextureBuffer> value)
{
	_fontTextureBuffer = value;

	for(const auto & quad2d : _quad2ds)
	{
		quad2d->setDiffuseMap(_fontTextureBuffer);
	}
}

void Text2d::setColor(const fvec3 & value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));

	for(const auto & quad2d : _quad2ds)
	{
		quad2d->setColor(_color);
	}
}

void Text2d::setHorizontallyFlipped(bool value)
{
	_isHorizontallyFlipped = value;

	for(const auto & quad2d : _quad2ds)
	{
		quad2d->setHorizontallyFlipped(_isHorizontallyFlipped);
	}
}

void Text2d::setVerticallyFlipped(bool value)
{
	_isVerticallyFlipped = value;

	for(const auto & quad2d : _quad2ds)
	{
		quad2d->setVerticallyFlipped(_isVerticallyFlipped);
	}
}

void Text2d::setOpacity(float value)
{
	_opacity = clamp(value, 0.0f, 1.0f);

	for(const auto & quad2d : _quad2ds)
	{
		quad2d->setOpacity(_opacity);
	}
}

void Text2d::setWireframeColor(const fvec3 & value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));

	for(const auto & quad2d : _quad2ds)
	{
		quad2d->setWireframeColor(_wireframeColor);
	}
}

void Text2d::setPosition(const fvec2 & value)
{
	_position = value;
	_positionTarget = value;
}

void Text2d::setRotation(float value)
{
	_rotation = Mathematics::limitAngle(value);
	_rotationTarget = Mathematics::limitAngle(value);
}

void Text2d::setSize(const fvec2 & value)
{
	_size = fvec2(max(0.0f, value.x), max(0.0f, value.y));
	_sizeTarget = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void Text2d::move(const fvec2 & change)
{
	_position += change;
	_positionTarget += change;
}

void Text2d::rotate(float change)
{
	_rotation += change;
	_rotationTarget += change;
	_rotation = Mathematics::limitAngle(_rotation);
	_rotationTarget = Mathematics::limitAngle(_rotationTarget);
}

void Text2d::scale(const fvec2 & change)
{
	_size += change;
	_sizeTarget += change;
	_size = fvec2(max(0.0f, _size.x), max(0.0f, _size.y));
	_sizeTarget = fvec2(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y));
}

void Text2d::moveTo(const fvec2 & target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void Text2d::rotateTo(float target, float speed)
{
	_rotationTarget = Mathematics::limitAngle(target);
	_rotationTargetSpeed = speed;
}

void Text2d::scaleTo(const fvec2 & target, float speed)
{
	_sizeTarget = fvec2(max(0.0f, target.x), max(0.0f, target.y));
	_sizeTargetSpeed = speed;
}

const string & Text2d::getId() const
{
	return _id;
}

const string & Text2d::getContent() const
{
	return _content;
}

const string & Text2d::getFontMapPath() const
{
	return _fontMapPath;
}

const vector<shared_ptr<Quad2d>> & Text2d::getQuad2ds() const
{
	return _quad2ds;
}

const shared_ptr<VertexBuffer> Text2d::getVertexBuffer() const
{
	return _vertexBuffer;
}

const shared_ptr<TextureBuffer> Text2d::getFontTextureBuffer() const
{
	return _fontTextureBuffer;
}

const fvec3 & Text2d::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3 & Text2d::getColor() const
{
	return _color;
}

const float Text2d::getOpacity() const
{
	return _opacity;
}

const bool Text2d::isVisible() const
{
	return _isVisible;
}

const bool Text2d::isWireframed() const
{
	return _isWireframed;
}

const bool Text2d::isCentered() const
{
	return _isCentered;
}

const bool Text2d::isHorizontallyFlipped() const
{
	return _isHorizontallyFlipped;
}

const bool Text2d::isVerticallyFlipped() const
{
	return _isVerticallyFlipped;
}

const fvec2 & Text2d::getPosition() const
{
	return _position;
}

const float Text2d::getRotation() const
{
	return _rotation;
}

const float Text2d::getLightness() const
{
	return _lightness;
}

const fvec2 & Text2d::getSize() const
{
	return _size;
}

const fvec2 & Text2d::getMinClipPosition() const
{
	return _minClipPosition;
}

const fvec2 & Text2d::getMaxClipPosition() const
{
	return _maxClipPosition;
}

const int Text2d::getDepth() const
{
	return _depth;
}