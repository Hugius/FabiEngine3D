#include "model_entity.hpp"
#include "logger.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void ModelEntity::createPart(const string& id)
{
	_parts.push_back(ModelEntityPart(id));
}

void ModelEntity::updateTransformation()
{
	if(_basePosition != _basePositionTarget)
	{
		auto speedMultiplier = Math::normalize(_basePositionTarget - _basePosition);
		_basePosition += (speedMultiplier * _basePositionTargetSpeed);
		_correctPositionTarget(_basePosition, _basePositionTarget, _basePositionTargetSpeed);
	}

	if(_baseRotation != _baseRotationTarget)
	{
		auto difference = Math::calculateDifference(_baseRotation, _baseRotationTarget);
		fvec3 multiplier = fvec3(
			((difference.x < 180.0f) ? 1.0f : -1.0f),
			((difference.y < 180.0f) ? 1.0f : -1.0f),
			((difference.z < 180.0f) ? 1.0f : -1.0f));
		fvec3 speed = (fvec3(_baseRotationTargetSpeed) * multiplier);
		_baseRotation.x += ((_baseRotation.x < _baseRotationTarget.x) ? speed.x : (_baseRotation.x > _baseRotationTarget.x) ? -speed.x : 0.0f);
		_baseRotation.y += ((_baseRotation.y < _baseRotationTarget.y) ? speed.y : (_baseRotation.y > _baseRotationTarget.y) ? -speed.y : 0.0f);
		_baseRotation.z += ((_baseRotation.z < _baseRotationTarget.z) ? speed.z : (_baseRotation.z > _baseRotationTarget.z) ? -speed.z : 0.0f);
		_correctRotationTarget(_baseRotation, _baseRotationTarget, _baseRotationTargetSpeed);
	}

	if(_baseSize != _baseSizeTarget)
	{
		auto speedMultiplier = Math::normalize(_baseSizeTarget - _baseSize);
		_baseSize += (speedMultiplier * _baseSizeTargetSpeed);
		_correctSizeTarget(_baseSize, _baseSizeTarget, _baseSizeTargetSpeed);
	}

	for(auto& part : _parts)
	{
		if(part.position != part.positionTarget)
		{
			auto speedMultiplier = Math::normalize(part.positionTarget - part.position);
			part.position += (speedMultiplier * part.positionTargetSpeed);
			_correctPositionTarget(part.position, part.positionTarget, part.positionTargetSpeed);
		}

		if(part.rotation != part.rotationTarget)
		{
			auto difference = Math::calculateDifference(part.rotation, part.rotationTarget);
			fvec3 multiplier = fvec3(
				((difference.x < 180.0f) ? 1.0f : -1.0f),
				((difference.y < 180.0f) ? 1.0f : -1.0f),
				((difference.z < 180.0f) ? 1.0f : -1.0f));
			fvec3 speed = (fvec3(part.rotationTargetSpeed) * multiplier);
			fvec3 rotation = part.rotation;
			fvec3 target = part.rotationTarget;
			part.rotation.x += ((rotation.x < target.x) ? speed.x : (rotation.x > target.x) ? -speed.x : 0.0f);
			part.rotation.y += ((rotation.y < target.y) ? speed.y : (rotation.y > target.y) ? -speed.y : 0.0f);
			part.rotation.z += ((rotation.z < target.z) ? speed.z : (rotation.z > target.z) ? -speed.z : 0.0f);
			_correctRotationTarget(part.rotation, part.rotationTarget, part.rotationTargetSpeed);
		}

		if(part.size != part.sizeTarget)
		{
			auto speedMultiplier = Math::normalize(part.sizeTarget - part.size);
			part.size += (speedMultiplier * part.sizeTargetSpeed);
			_correctSizeTarget(part.size, part.sizeTarget, part.sizeTargetSpeed);
		}
	}
}

void ModelEntity::updateTransformationMatrix()
{
	for(size_t i = 0; i < _parts.size(); i++)
	{
		_parts[i].transformationMatrix = mat44(1.0f);

		auto baseTranslationMatrix = Math::createTranslationMatrix(_basePosition.x, _basePosition.y, _basePosition.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * baseTranslationMatrix);

		auto translationMatrix = Math::createTranslationMatrix(_parts[i].position.x, _parts[i].position.y, _parts[i].position.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * translationMatrix);

		auto baseRotationOriginMatrix = Math::createTranslationMatrix(_baseRotationOrigin.x, _baseRotationOrigin.y, _baseRotationOrigin.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * baseRotationOriginMatrix);

		auto baseRotationMatrix = Math::createRotationMatrix(
			Math::convertToRadians(_baseRotation.x),
			Math::convertToRadians(_baseRotation.y),
			Math::convertToRadians(_baseRotation.z), _rotationOrder);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * baseRotationMatrix);

		baseRotationOriginMatrix = Math::createTranslationMatrix(-_baseRotationOrigin.x, -_baseRotationOrigin.y, -_baseRotationOrigin.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * baseRotationOriginMatrix);

		auto rotationOriginMatrix = Math::createTranslationMatrix(_parts[i].rotationOrigin.x, _parts[i].rotationOrigin.y, _parts[i].rotationOrigin.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * rotationOriginMatrix);

		auto rotationMatrix = Math::createRotationMatrix(
			Math::convertToRadians(_parts[i].rotation.x),
			Math::convertToRadians(_parts[i].rotation.y),
			Math::convertToRadians(_parts[i].rotation.z), _rotationOrder);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * rotationMatrix);

		rotationOriginMatrix = Math::createTranslationMatrix(-_parts[i].rotationOrigin.x, -_parts[i].rotationOrigin.y, -_parts[i].rotationOrigin.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * rotationOriginMatrix);

		auto baseScalingMatrix = Math::createScalingMatrix(_baseSize.x, _baseSize.y, _baseSize.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * baseScalingMatrix);

		auto scalingMatrix = Math::createScalingMatrix(_parts[i].size.x, _parts[i].size.y, _parts[i].size.z);
		_parts[i].transformationMatrix = (_parts[i].transformationMatrix * scalingMatrix);
	}
}

void ModelEntity::setMesh(const string& partId, shared_ptr<VertexBuffer> value)
{
	_parts[_getPartIndex(partId)].vertexBuffer = value;
}

void ModelEntity::setDiffuseMap(const string& partId, shared_ptr<TextureBuffer> value)
{
	_parts[_getPartIndex(partId)].diffuseMap = value;
}

void ModelEntity::setEmissionMap(const string& partId, shared_ptr<TextureBuffer> value)
{
	_parts[_getPartIndex(partId)].emissionMap = value;
}

void ModelEntity::setSpecularMap(const string& partId, shared_ptr<TextureBuffer> value)
{
	_parts[_getPartIndex(partId)].specularMap = value;
}

void ModelEntity::setReflectionMap(const string& partId, shared_ptr<TextureBuffer> value)
{
	_parts[_getPartIndex(partId)].reflectionMap = value;
}

void ModelEntity::setNormalMap(const string& partId, shared_ptr<TextureBuffer> value)
{
	_parts[_getPartIndex(partId)].normalMap = value;
}

void ModelEntity::setBasePosition(const fvec3& value)
{
	_basePosition = value;
	_basePositionTarget = _basePosition;
}

void ModelEntity::setBaseRotation(const fvec3& value)
{
	_baseRotation = fvec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
	_baseRotationTarget = fvec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
}

void ModelEntity::setBaseRotationOrigin(const fvec3& value)
{
	_baseRotationOrigin = value;
}

void ModelEntity::setBaseSize(const fvec3& value)
{
	_baseSize = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
	_baseSizeTarget = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void ModelEntity::setPartPosition(const string& partId, const fvec3& value)
{
	_parts[_getPartIndex(partId)].position = value;
	_parts[_getPartIndex(partId)].positionTarget = value;
}

void ModelEntity::setPartRotation(const string& partId, const fvec3& value)
{
	_parts[_getPartIndex(partId)].rotation = fvec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
	_parts[_getPartIndex(partId)].rotationTarget = fvec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
}

void ModelEntity::setPartRotationOrigin(const string& partId, const fvec3& value)
{
	_parts[_getPartIndex(partId)].rotationOrigin = value;
}

void ModelEntity::setPartSize(const string& partId, const fvec3& value)
{
	_parts[_getPartIndex(partId)].size = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
	_parts[_getPartIndex(partId)].sizeTarget = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void ModelEntity::moveBase(const fvec3& value)
{
	_basePosition += value;
	_basePositionTarget += value;
}

void ModelEntity::rotateBase(const fvec3& value)
{
	_baseRotation += value;
	_baseRotationTarget += value;
	_baseRotation = fvec3(Math::limitAngle(_baseRotation.x), Math::limitAngle(_baseRotation.y), Math::limitAngle(_baseRotation.z));
	_baseRotationTarget = fvec3(Math::limitAngle(_baseRotationTarget.x), Math::limitAngle(_baseRotationTarget.y), Math::limitAngle(_baseRotationTarget.z));
}

void ModelEntity::scaleBase(const fvec3& value)
{
	_baseSize += value;
	_baseSizeTarget += value;
	_baseSize = fvec3(max(0.0f, _baseSize.x), max(0.0f, _baseSize.y), max(0.0f, _baseSize.z));
	_baseSizeTarget = fvec3(max(0.0f, _baseSizeTarget.x), max(0.0f, _baseSizeTarget.y), max(0.0f, _baseSizeTarget.z));
}

void ModelEntity::movePart(const string& partId, const fvec3& value)
{
	_parts[_getPartIndex(partId)].position += value;
	_parts[_getPartIndex(partId)].positionTarget += value;
}

void ModelEntity::rotatePart(const string& partId, const fvec3& value)
{
	fvec3& rotation = _parts[_getPartIndex(partId)].rotation;
	fvec3& rotationTarget = _parts[_getPartIndex(partId)].rotationTarget;
	rotation += value;
	rotationTarget += value;
	rotation = fvec3(Math::limitAngle(rotation.x), Math::limitAngle(rotation.y), Math::limitAngle(rotation.z));
	rotationTarget = fvec3(Math::limitAngle(rotationTarget.x), Math::limitAngle(rotationTarget.y), Math::limitAngle(rotationTarget.z));
}

void ModelEntity::scalePart(const string& partId, const fvec3& value)
{
	fvec3& size = _parts[_getPartIndex(partId)].size;
	fvec3& sizeTarget = _parts[_getPartIndex(partId)].sizeTarget;
	size += value;
	sizeTarget += value;
	size = fvec3(max(0.0f, size.x), max(0.0f, size.y), max(0.0f, size.z));
	sizeTarget = fvec3(max(0.0f, sizeTarget.x), max(0.0f, sizeTarget.y), max(0.0f, sizeTarget.z));
}

void ModelEntity::moveBaseTo(const fvec3& target, float speed)
{
	_basePositionTarget = target;
	_basePositionTargetSpeed = max(0.0f, speed);
}

void ModelEntity::rotateBaseTo(const fvec3& target, float speed)
{
	_baseRotationTarget = fvec3(Math::limitAngle(target.x), Math::limitAngle(target.y), Math::limitAngle(target.z));
	_baseRotationTargetSpeed = max(0.0f, speed);
}

void ModelEntity::scaleBaseTo(const fvec3& target, float speed)
{
	_baseSizeTarget = fvec3(max(0.0f, target.x), max(0.0f, target.y), max(0.0f, target.z));
	_baseSizeTargetSpeed = max(0.0f, speed);
}

void ModelEntity::movePartTo(const string& partId, const fvec3& target, float speed)
{
	_parts[_getPartIndex(partId)].positionTarget = target;
	_parts[_getPartIndex(partId)].positionTargetSpeed = max(0.0f, speed);
}

void ModelEntity::rotatePartTo(const string& partId, const fvec3& target, float speed)
{
	_parts[_getPartIndex(partId)].rotationTarget = fvec3(Math::limitAngle(target.x), Math::limitAngle(target.y), Math::limitAngle(target.z));
	_parts[_getPartIndex(partId)].rotationTargetSpeed = max(0.0f, speed);
}

void ModelEntity::scalePartTo(const string& partId, const fvec3& target, float speed)
{
	_parts[_getPartIndex(partId)].sizeTarget = fvec3(max(0.0f, target.x), max(0.0f, target.y), max(0.0f, target.z));
	_parts[_getPartIndex(partId)].sizeTargetSpeed = max(0.0f, speed);
}

void ModelEntity::setColor(const string& partId, const fvec3& value)
{
	_parts[_getPartIndex(partId)].color = fvec3(clamp(value.x, 0.0f, 1.0f), clamp(value.y, 0.0f, 1.0f), clamp(value.z, 0.0f, 1.0f));
}

void ModelEntity::setWireframeColor(const string& partId, const fvec3& value)
{
	_parts[_getPartIndex(partId)].wireframeColor = fvec3(clamp(value.x, 0.0f, 1.0f), clamp(value.y, 0.0f, 1.0f), clamp(value.z, 0.0f, 1.0f));
}

void ModelEntity::setMeshPath(const string& value)
{
	_meshPath = value;
}

void ModelEntity::setLevelOfDetailSize(const fvec3& value)
{
	_levelOfDetailSize = value;
}

void ModelEntity::setDiffuseMapPath(const string& partId, const string& value)
{
	_parts[_getPartIndex(partId)].diffuseMapPath = value;
}

void ModelEntity::setEmissionMapPath(const string& partId, const string& value)
{
	_parts[_getPartIndex(partId)].emissionMapPath = value;
}

void ModelEntity::setSpecularMapPath(const string& partId, const string& value)
{
	_parts[_getPartIndex(partId)].specularMapPath = value;
}

void ModelEntity::setReflectionMapPath(const string& partId, const string& value)
{
	_parts[_getPartIndex(partId)].reflectionMapPath = value;
}

void ModelEntity::setNormalMapPath(const string& partId, const string& value)
{
	_parts[_getPartIndex(partId)].normalMapPath = value;
}

void ModelEntity::setLevelOfDetailEntityId(const string& value)
{
	_levelOfDetailEntityId = value;
}

void ModelEntity::setPreviousReflectionEntityId(const string& value)
{
	_previousReflectionEntityId = value;
}

void ModelEntity::setCurrentReflectionEntityId(const string& value)
{
	_currentReflectionEntityId = value;
}

void ModelEntity::setCubeReflectionMixValue(float value)
{
	_cubeReflectionMixValue = clamp(value, 0.0f, 1.0f);
}

void ModelEntity::setReflectivity(const string& partId, float value)
{
	_parts[_getPartIndex(partId)].reflectivity = clamp(value, 0.0f, 1.0f);
}

void ModelEntity::setFaceCulled(const string& partId, bool value)
{
	_parts[_getPartIndex(partId)].isFaceCulled = value;
}

void ModelEntity::setRotationOrder(DirectionOrder value)
{
	_rotationOrder = value;
}

void ModelEntity::setMinTextureAlpha(const string& partId, float value)
{
	_parts[_getPartIndex(partId)].minTextureAlpha = clamp(value, 0.0f, 1.0f);
}

void ModelEntity::setReflectionType(const string& partId, ReflectionType value)
{
	_parts[_getPartIndex(partId)].reflectionType = value;
}

void ModelEntity::setSpecular(const string& partId, bool value)
{
	_parts[_getPartIndex(partId)].isSpecular = value;
}

void ModelEntity::setReflective(const string& partId, bool value)
{
	_parts[_getPartIndex(partId)].isReflective = value;
}

void ModelEntity::setShadowed(bool value)
{
	_isShadowed = value;
}

void ModelEntity::setReflected(bool value)
{
	_isReflected = value;
}

void ModelEntity::setFrozen(bool value)
{
	_isFrozen = value;
}

void ModelEntity::setDepthMapIncluded(bool value)
{
	_isDepthMapIncluded = value;
}

void ModelEntity::setLevelOfDetailed(bool value)
{
	_isLevelOfDetailed = value;
}

void ModelEntity::setWireframed(const string& partId, bool value)
{
	_parts[_getPartIndex(partId)].isWireframed = value;
}

void ModelEntity::setBright(const string& partId, bool value)
{
	_parts[_getPartIndex(partId)].isBright = value;
}

void ModelEntity::deleteParts()
{
	_parts.clear();
}

void ModelEntity::setLightness(const string& partId, float value)
{
	_parts[_getPartIndex(partId)].lightness = max(0.0f, value);
}

void ModelEntity::setSpecularShininess(const string& partId, float value)
{
	_parts[_getPartIndex(partId)].specularShininess = max(0.0f, value);
}

void ModelEntity::setSpecularIntensity(const string& partId, float value)
{
	_parts[_getPartIndex(partId)].specularIntensity = max(0.0f, value);
}

void ModelEntity::setMinHeight(float value)
{
	_minHeight = value;
}

void ModelEntity::setMaxHeight(float value)
{
	_maxHeight = value;
}

void ModelEntity::setLevelOfDetailDistance(float value)
{
	_levelOfDetailDistance = value;
}

void ModelEntity::setOpacity(const string& partId, float value)
{
	_parts[_getPartIndex(partId)].opacity = clamp(value, 0.0f, 1.0f);
}

void ModelEntity::setTextureRepeat(const string& partId, float value)
{
	_parts[_getPartIndex(partId)].textureRepeat = max(0.0f, value);
}

void ModelEntity::setEmissionIntensity(const string& partId, float value)
{
	_parts[_getPartIndex(partId)].emissionIntensity = max(0.0f, value);
}

void ModelEntity::_correctPositionTarget(fvec3& current, const fvec3& target, float speed)
{
	if(fabsf(target.x - current.x) <= speed)
	{
		current.x = target.x;
	}

	if(fabsf(target.y - current.y) <= speed)
	{
		current.y = target.y;
	}

	if(fabsf(target.z - current.z) <= speed)
	{
		current.z = target.z;
	}
}

void ModelEntity::_correctRotationTarget(fvec3& current, const fvec3& target, float speed)
{
	current = fvec3(Math::limitAngle(current.x), Math::limitAngle(current.y), Math::limitAngle(current.z));

	if(Math::calculateAngleDifference(current.x, target.x) <= speed)
	{
		current.x = target.x;
	}

	if(Math::calculateAngleDifference(current.y, target.y) <= speed)
	{
		current.y = target.y;
	}

	if(Math::calculateAngleDifference(current.z, target.z) <= speed)
	{
		current.z = target.z;
	}
}

void ModelEntity::_correctSizeTarget(fvec3& current, const fvec3& target, float speed)
{
	current = fvec3(max(0.0f, current.x), max(0.0f, current.y), max(0.0f, current.z));

	if(fabsf(target.x - current.x) <= speed)
	{
		current.x = target.x;
	}

	if(fabsf(target.y - current.y) <= speed)
	{
		current.y = target.y;
	}

	if(fabsf(target.z - current.z) <= speed)
	{
		current.z = target.z;
	}
}

const shared_ptr<VertexBuffer> ModelEntity::getMesh(const string& partId) const
{
	return _parts[_getPartIndex(partId)].vertexBuffer;
}

const mat44& ModelEntity::getTransformationMatrix(const string& partId) const
{
	return _parts[_getPartIndex(partId)].transformationMatrix;
}

const shared_ptr<TextureBuffer> ModelEntity::getDiffuseMap(const string& partId) const
{
	return _parts[_getPartIndex(partId)].diffuseMap;
}

const shared_ptr<TextureBuffer> ModelEntity::getEmissionMap(const string& partId) const
{
	return _parts[_getPartIndex(partId)].emissionMap;
}

const shared_ptr<TextureBuffer> ModelEntity::getSpecularMap(const string& partId) const
{
	return _parts[_getPartIndex(partId)].specularMap;
}

const shared_ptr<TextureBuffer> ModelEntity::getReflectionMap(const string& partId) const
{
	return _parts[_getPartIndex(partId)].reflectionMap;
}

const shared_ptr<TextureBuffer> ModelEntity::getNormalMap(const string& partId) const
{
	return _parts[_getPartIndex(partId)].normalMap;
}

const fvec3& ModelEntity::getColor(const string& partId) const
{
	return _parts[_getPartIndex(partId)].color;
}

const fvec3& ModelEntity::getWireframeColor(const string& partId) const
{
	return _parts[_getPartIndex(partId)].wireframeColor;
}

const fvec3& ModelEntity::getBasePosition() const
{
	return _basePosition;
}

const fvec3& ModelEntity::getBaseRotation() const
{
	return _baseRotation;
}

const fvec3& ModelEntity::getBaseRotationOrigin() const
{
	return _baseRotationOrigin;
}

const fvec3& ModelEntity::getBaseSize() const
{
	return _baseSize;
}

const fvec3& ModelEntity::getPartPosition(const string& partId) const
{
	return _parts[_getPartIndex(partId)].position;
}

const fvec3& ModelEntity::getPartRotation(const string& partId) const
{
	return _parts[_getPartIndex(partId)].rotation;
}

const fvec3& ModelEntity::getPartRotationOrigin(const string& partId) const
{
	return _parts[_getPartIndex(partId)].rotationOrigin;
}

const fvec3& ModelEntity::getPartSize(const string& partId) const
{
	return _parts[_getPartIndex(partId)].size;
}

const fvec3& ModelEntity::getLevelOfDetailSize() const
{
	return _levelOfDetailSize;
}

const float ModelEntity::getCubeReflectionMixValue() const
{
	return _cubeReflectionMixValue;
}

const float ModelEntity::getReflectivity(const string& partId) const
{
	return _parts[_getPartIndex(partId)].reflectivity;
}

const string& ModelEntity::getMeshPath() const
{
	return _meshPath;
}

const string& ModelEntity::getDiffuseMapPath(const string& partId) const
{
	return _parts[_getPartIndex(partId)].diffuseMapPath;
}

const string& ModelEntity::getEmissionMapPath(const string& partId) const
{
	return _parts[_getPartIndex(partId)].emissionMapPath;
}

const string& ModelEntity::getSpecularMapPath(const string& partId) const
{
	return _parts[_getPartIndex(partId)].specularMapPath;
}

const string& ModelEntity::getReflectionMapPath(const string& partId) const
{
	return _parts[_getPartIndex(partId)].reflectionMapPath;
}

const string& ModelEntity::getNormalMapPath(const string& partId) const
{
	return _parts[_getPartIndex(partId)].normalMapPath;
}

const string& ModelEntity::getLevelOfDetailEntityId() const
{
	return _levelOfDetailEntityId;
}

const string& ModelEntity::getPreviousReflectionEntityId() const
{
	return _previousReflectionEntityId;
}

const string& ModelEntity::getCurrentReflectionEntityId() const
{
	return _currentReflectionEntityId;
}

const vector<string> ModelEntity::getPartIds() const
{
	vector<string> result;

	for(const auto& part : _parts)
	{
		result.push_back(part.id);
	}

	return result;
}

const bool ModelEntity::isFaceCulled(const string& partId) const
{
	return _parts[_getPartIndex(partId)].isFaceCulled;
}

const bool ModelEntity::isWireframed(const string& partId) const
{
	return _parts[_getPartIndex(partId)].isWireframed;
}

const bool ModelEntity::isSpecular(const string& partId) const
{
	return _parts[_getPartIndex(partId)].isSpecular;
}

const bool ModelEntity::isReflective(const string& partId) const
{
	return _parts[_getPartIndex(partId)].isReflective;
}

const bool ModelEntity::isShadowed() const
{
	return _isShadowed;
}

const bool ModelEntity::isReflected() const
{
	return _isReflected;
}

const ReflectionType ModelEntity::getReflectionType(const string& partId) const
{
	return _parts[_getPartIndex(partId)].reflectionType;
}

const DirectionOrder ModelEntity::getRotationOrder() const
{
	return _rotationOrder;
}

const bool ModelEntity::isBright(const string& partId) const
{
	return _parts[_getPartIndex(partId)].isBright;
}

const bool ModelEntity::isFrozen() const
{
	return _isFrozen;
}

const bool ModelEntity::isDepthMapIncluded() const
{
	return _isDepthMapIncluded;
}

const bool ModelEntity::isLevelOfDetailed() const
{
	return _isLevelOfDetailed;
}

const float ModelEntity::getLightness(const string& partId) const
{
	return _parts[_getPartIndex(partId)].lightness;
}

const float ModelEntity::getSpecularShininess(const string& partId) const
{
	return _parts[_getPartIndex(partId)].specularShininess;
}

const float ModelEntity::getSpecularIntensity(const string& partId) const
{
	return _parts[_getPartIndex(partId)].specularIntensity;
}

const float ModelEntity::getMinHeight() const
{
	return _minHeight;
}

const float ModelEntity::getMaxHeight() const
{
	return _maxHeight;
}

const float ModelEntity::getLevelOfDetailDistance() const
{
	return _levelOfDetailDistance;
}

const float ModelEntity::getEmissionIntensity(const string& partId) const
{
	return _parts[_getPartIndex(partId)].emissionIntensity;
}

const float ModelEntity::getMinTextureAlpha(const string& partId) const
{
	return _parts[_getPartIndex(partId)].minTextureAlpha;
}

const float ModelEntity::getOpacity(const string& partId) const
{
	return _parts[_getPartIndex(partId)].opacity;
}

const float ModelEntity::getTextureRepeat(const string& partId) const
{
	return _parts[_getPartIndex(partId)].textureRepeat;
}

const unsigned int ModelEntity::_getPartIndex(const string& partId) const
{
	if(partId.empty())
	{
		if(_parts.size() > 1)
		{
			abort();
		}
		else
		{
			return 0;
		}
	}

	for(size_t i = 0; i < _parts.size(); i++)
	{
		if(partId == _parts[i].id)
		{
			return static_cast<unsigned int>(i);
		}
	}

	abort();
}