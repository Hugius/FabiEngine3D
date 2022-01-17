#include "quad3d_entity.hpp"

const shared_ptr<VertexBuffer> Quad3dEntity::getMesh() const
{
	return _mesh;
}

const mat44& Quad3dEntity::getTransformationMatrix() const
{
	return _transformationMatrix;
}

const shared_ptr<TextureBuffer> Quad3dEntity::getDiffuseMap() const
{
	return _diffuseMap;
}

const shared_ptr<TextureBuffer> Quad3dEntity::getEmissionMap() const
{
	return _emissionMap;
}

const fvec3 Quad3dEntity::getPosition() const
{
	return _position;
}

const fvec3 Quad3dEntity::getRotation() const
{
	return _rotation;
}

const fvec2 Quad3dEntity::getSize() const
{
	return _size;
}

const fvec2 Quad3dEntity::getUvMultiplier() const
{
	return _uvMultiplier;
}

const fvec2 Quad3dEntity::getUvOffset() const
{
	return _uvOffset;
}

const fvec3 Quad3dEntity::getColor() const
{
	return _color;
}

const fvec3 Quad3dEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const string& Quad3dEntity::getDiffuseMapPath() const
{
	return _diffuseMapPath;
}

const string& Quad3dEntity::getEmissionMapPath() const
{
	return _emissionMapPath;
}

const float Quad3dEntity::getLightness() const
{
	return _lightness;
}

const float Quad3dEntity::getTransparency() const
{
	return _transparency;
}

const float Quad3dEntity::getMinHeight() const
{
	return _minHeight;
}

const float Quad3dEntity::getMaxHeight() const
{
	return _maxHeight;
}

const float Quad3dEntity::getTextureRepeat() const
{
	return _textureRepeat;
}

const float Quad3dEntity::getEmissionIntensity() const
{
	return _emissionIntensity;
}

const bool Quad3dEntity::isFacingCameraX() const
{
	return _isFacingCameraX;
}

const bool Quad3dEntity::isFacingCameraY() const
{
	return _isFacingCameraY;
}

const bool Quad3dEntity::isDepthMapIncluded() const
{
	return _isDepthMapIncluded;
}

const bool Quad3dEntity::isShadowed() const
{
	return _isShadowed;
}

const bool Quad3dEntity::isReflected() const
{
	return _isReflected;
}

const bool Quad3dEntity::isBright() const
{
	return _isBright;
}

const bool Quad3dEntity::isWireframed() const
{
	return _isWireframed;
}

const bool Quad3dEntity::hasDiffuseMap() const
{
	return (_diffuseMap != nullptr);
}

const bool Quad3dEntity::hasEmissionMap() const
{
	return (_emissionMap != nullptr);
}

const bool Quad3dEntity::isCentered() const
{
	return _isCentered;
}

const bool Quad3dEntity::isFrozen() const
{
	return _isFrozen;
}