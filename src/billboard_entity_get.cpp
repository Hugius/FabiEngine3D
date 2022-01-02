#include "billboard_entity.hpp"

const shared_ptr<VertexBuffer> BillboardEntity::getVertexBuffer() const
{
	return _vertexBuffer;
}

const mat44& BillboardEntity::getTransformationMatrix() const
{
	return _transformationMatrix;
}

const TextureID BillboardEntity::getDiffuseMap() const
{
	return _diffuseMap;
}

const TextureID BillboardEntity::getEmissionMap() const
{
	return _emissionMap;
}

const fvec3 BillboardEntity::getPosition() const
{
	return _position;
}

const fvec3 BillboardEntity::getRotation() const
{
	return _rotation;
}

const fvec2 BillboardEntity::getSize() const
{
	return _size;
}

const fvec2 BillboardEntity::getUvMultiplier() const
{
	return _uvMultiplier;
}

const fvec2 BillboardEntity::getUvOffset() const
{
	return _uvOffset;
}

const fvec3 BillboardEntity::getColor() const
{
	return _color;
}

const fvec3 BillboardEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const string& BillboardEntity::getTextContent() const
{
	return _textContent;
}

const string& BillboardEntity::getFontPath() const
{
	return _fontPath;
}

const string& BillboardEntity::getDiffuseMapPath() const
{
	return _diffuseMapPath;
}

const string& BillboardEntity::getEmissionMapPath() const
{
	return _emissionMapPath;
}

const float BillboardEntity::getLightness() const
{
	return _lightness;
}

const float BillboardEntity::getTransparency() const
{
	return _transparency;
}

const float BillboardEntity::getMinHeight() const
{
	return _minHeight;
}

const float BillboardEntity::getMaxHeight() const
{
	return _maxHeight;
}

const float BillboardEntity::getTextureRepeat() const
{
	return _textureRepeat;
}

const float BillboardEntity::getEmissionIntensity() const
{
	return _emissionIntensity;
}

const bool BillboardEntity::isFacingCameraX() const
{
	return _isFacingCameraX;
}

const bool BillboardEntity::isFacingCameraY() const
{
	return _isFacingCameraY;
}

const bool BillboardEntity::isDepthMapIncluded() const
{
	return _isDepthMapIncluded;
}

const bool BillboardEntity::isShadowed() const
{
	return _isShadowed;
}

const bool BillboardEntity::isReflected() const
{
	return _isReflected;
}

const bool BillboardEntity::isBright() const
{
	return _isBright;
}

const bool BillboardEntity::isWireframed() const
{
	return _isWireframed;
}

const bool BillboardEntity::hasVertexBuffer() const
{
	return (_vertexBuffer != nullptr);
}

const bool BillboardEntity::hasDiffuseMap() const
{
	return (_diffuseMap != 0);
}

const bool BillboardEntity::hasEmissionMap() const
{
	return (_emissionMap != 0);
}

const bool BillboardEntity::isCentered() const
{
	return _isCentered;
}

const bool BillboardEntity::isTextual() const
{
	return _isTextual;
}

const bool BillboardEntity::isFrozen() const
{
	return _isFrozen;
}