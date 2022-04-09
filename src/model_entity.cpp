#include "model_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;
using std::make_unique;

void ModelEntity::createPart(const string & id)
{
	_parts.insert({id, make_unique<ModelEntityPart>()});
}

void ModelEntity::deletePart(const string & id)
{
	_parts.erase(id);
}

void ModelEntity::deleteParts()
{
	_parts.clear();
}

void ModelEntity::updateTarget()
{
	if(_basePosition != _basePositionTarget)
	{
		auto speedMultiplier = Mathematics::normalize(_basePositionTarget - _basePosition);
		_basePosition += (speedMultiplier * _basePositionTargetSpeed);
		_correctPositionTarget(_basePosition, _basePositionTarget, _basePositionTargetSpeed);
	}

	if(_baseRotation != _baseRotationTarget)
	{
		auto difference = Mathematics::calculateDifference(_baseRotation, _baseRotationTarget);
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
		auto speedMultiplier = Mathematics::normalize(_baseSizeTarget - _baseSize);
		_baseSize += (speedMultiplier * _baseSizeTargetSpeed);
		_correctSizeTarget(_baseSize, _baseSizeTarget, _baseSizeTargetSpeed);
	}

	for(auto & [partId, part] : _parts)
	{
		if(part->position != part->positionTarget)
		{
			auto speedMultiplier = Mathematics::normalize(part->positionTarget - part->position);
			part->position += (speedMultiplier * part->positionTargetSpeed);
			_correctPositionTarget(part->position, part->positionTarget, part->positionTargetSpeed);
		}

		if(part->rotation != part->rotationTarget)
		{
			auto difference = Mathematics::calculateDifference(part->rotation, part->rotationTarget);
			fvec3 multiplier = fvec3(
				((difference.x < 180.0f) ? 1.0f : -1.0f),
				((difference.y < 180.0f) ? 1.0f : -1.0f),
				((difference.z < 180.0f) ? 1.0f : -1.0f));
			fvec3 speed = (fvec3(part->rotationTargetSpeed) * multiplier);
			fvec3 rotation = part->rotation;
			fvec3 target = part->rotationTarget;
			part->rotation.x += ((rotation.x < target.x) ? speed.x : (rotation.x > target.x) ? -speed.x : 0.0f);
			part->rotation.y += ((rotation.y < target.y) ? speed.y : (rotation.y > target.y) ? -speed.y : 0.0f);
			part->rotation.z += ((rotation.z < target.z) ? speed.z : (rotation.z > target.z) ? -speed.z : 0.0f);
			_correctRotationTarget(part->rotation, part->rotationTarget, part->rotationTargetSpeed);
		}

		if(part->size != part->sizeTarget)
		{
			auto speedMultiplier = Mathematics::normalize(part->sizeTarget - part->size);
			part->size += (speedMultiplier * part->sizeTargetSpeed);
			_correctSizeTarget(part->size, part->sizeTarget, part->sizeTargetSpeed);
		}
	}
}

void ModelEntity::updateTransformation()
{
	for(auto & [partId, part] : _parts)
	{
		part->transformation = mat44(1.0f);

		auto baseTranslationMatrix = Mathematics::createTranslationMatrix(_basePosition.x, _basePosition.y, _basePosition.z);
		part->transformation = (part->transformation * baseTranslationMatrix);

		auto translationMatrix = Mathematics::createTranslationMatrix(part->position.x, part->position.y, part->position.z);
		part->transformation = (part->transformation * translationMatrix);

		auto baseRotationOriginMatrix = Mathematics::createTranslationMatrix(_baseRotationOrigin.x, _baseRotationOrigin.y, _baseRotationOrigin.z);
		part->transformation = (part->transformation * baseRotationOriginMatrix);

		auto baseRotationMatrix = Mathematics::createRotationMatrix(
			Mathematics::convertToRadians(_baseRotation.x),
			Mathematics::convertToRadians(_baseRotation.y),
			Mathematics::convertToRadians(_baseRotation.z), _rotationOrder);
		part->transformation = (part->transformation * baseRotationMatrix);

		baseRotationOriginMatrix = Mathematics::createTranslationMatrix(-_baseRotationOrigin.x, -_baseRotationOrigin.y, -_baseRotationOrigin.z);
		part->transformation = (part->transformation * baseRotationOriginMatrix);

		auto rotationOriginMatrix = Mathematics::createTranslationMatrix(part->rotationOrigin.x, part->rotationOrigin.y, part->rotationOrigin.z);
		part->transformation = (part->transformation * rotationOriginMatrix);

		auto rotationMatrix = Mathematics::createRotationMatrix(
			Mathematics::convertToRadians(part->rotation.x),
			Mathematics::convertToRadians(part->rotation.y),
			Mathematics::convertToRadians(part->rotation.z), _rotationOrder);
		part->transformation = (part->transformation * rotationMatrix);

		rotationOriginMatrix = Mathematics::createTranslationMatrix(-part->rotationOrigin.x, -part->rotationOrigin.y, -part->rotationOrigin.z);
		part->transformation = (part->transformation * rotationOriginMatrix);

		auto baseScalingMatrix = Mathematics::createScalingMatrix(_baseSize.x, _baseSize.y, _baseSize.z);
		part->transformation = (part->transformation * baseScalingMatrix);

		auto scalingMatrix = Mathematics::createScalingMatrix(part->size.x, part->size.y, part->size.z);
		part->transformation = (part->transformation * scalingMatrix);
	}
}

void ModelEntity::setVertexBuffer(const string & partId, shared_ptr<VertexBuffer> value)
{
	_parts.at(partId)->vertexBuffer = value;
}

void ModelEntity::setDiffuseTextureBuffer(const string & partId, shared_ptr<TextureBuffer> value)
{
	_parts.at(partId)->diffuseTextureBuffer = value;
}

void ModelEntity::setEmissionTextureBuffer(const string & partId, shared_ptr<TextureBuffer> value)
{
	_parts.at(partId)->emissionTextureBuffer = value;
}

void ModelEntity::setSpecularTextureBuffer(const string & partId, shared_ptr<TextureBuffer> value)
{
	_parts.at(partId)->specularTextureBuffer = value;
}

void ModelEntity::setReflectionTextureBuffer(const string & partId, shared_ptr<TextureBuffer> value)
{
	_parts.at(partId)->reflectionTextureBuffer = value;
}

void ModelEntity::setNormalTextureBuffer(const string & partId, shared_ptr<TextureBuffer> value)
{
	_parts.at(partId)->normalTextureBuffer = value;
}

void ModelEntity::setBasePosition(const fvec3 & value)
{
	_basePosition = value;
	_basePositionTarget = _basePosition;
}

void ModelEntity::setBaseRotation(const fvec3 & value)
{
	_baseRotation = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
	_baseRotationTarget = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
}

void ModelEntity::setBaseRotationOrigin(const fvec3 & value)
{
	_baseRotationOrigin = value;
}

void ModelEntity::setBaseSize(const fvec3 & value)
{
	_baseSize = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
	_baseSizeTarget = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void ModelEntity::setPartPosition(const string & partId, const fvec3 & value)
{
	_parts.at(partId)->position = value;
	_parts.at(partId)->positionTarget = value;
}

void ModelEntity::setPartRotation(const string & partId, const fvec3 & value)
{
	_parts.at(partId)->rotation = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
	_parts.at(partId)->rotationTarget = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
}

void ModelEntity::setPartRotationOrigin(const string & partId, const fvec3 & value)
{
	_parts.at(partId)->rotationOrigin = value;
}

void ModelEntity::setPartSize(const string & partId, const fvec3 & value)
{
	_parts.at(partId)->size = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
	_parts.at(partId)->sizeTarget = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void ModelEntity::moveBase(const fvec3 & value)
{
	_basePosition += value;
	_basePositionTarget += value;
}

void ModelEntity::rotateBase(const fvec3 & value)
{
	_baseRotation += value;
	_baseRotationTarget += value;
	_baseRotation = fvec3(Mathematics::limitAngle(_baseRotation.x), Mathematics::limitAngle(_baseRotation.y), Mathematics::limitAngle(_baseRotation.z));
	_baseRotationTarget = fvec3(Mathematics::limitAngle(_baseRotationTarget.x), Mathematics::limitAngle(_baseRotationTarget.y), Mathematics::limitAngle(_baseRotationTarget.z));
}

void ModelEntity::scaleBase(const fvec3 & value)
{
	_baseSize += value;
	_baseSizeTarget += value;
	_baseSize = fvec3(max(0.0f, _baseSize.x), max(0.0f, _baseSize.y), max(0.0f, _baseSize.z));
	_baseSizeTarget = fvec3(max(0.0f, _baseSizeTarget.x), max(0.0f, _baseSizeTarget.y), max(0.0f, _baseSizeTarget.z));
}

void ModelEntity::movePart(const string & partId, const fvec3 & value)
{
	_parts.at(partId)->position += value;
	_parts.at(partId)->positionTarget += value;
}

void ModelEntity::rotatePart(const string & partId, const fvec3 & value)
{
	fvec3 & rotation = _parts.at(partId)->rotation;
	fvec3 & rotationTarget = _parts.at(partId)->rotationTarget;
	rotation += value;
	rotationTarget += value;
	rotation = fvec3(Mathematics::limitAngle(rotation.x), Mathematics::limitAngle(rotation.y), Mathematics::limitAngle(rotation.z));
	rotationTarget = fvec3(Mathematics::limitAngle(rotationTarget.x), Mathematics::limitAngle(rotationTarget.y), Mathematics::limitAngle(rotationTarget.z));
}

void ModelEntity::scalePart(const string & partId, const fvec3 & value)
{
	fvec3 & size = _parts.at(partId)->size;
	fvec3 & sizeTarget = _parts.at(partId)->sizeTarget;
	size += value;
	sizeTarget += value;
	size = fvec3(max(0.0f, size.x), max(0.0f, size.y), max(0.0f, size.z));
	sizeTarget = fvec3(max(0.0f, sizeTarget.x), max(0.0f, sizeTarget.y), max(0.0f, sizeTarget.z));
}

void ModelEntity::moveBaseTo(const fvec3 & target, float speed)
{
	_basePositionTarget = target;
	_basePositionTargetSpeed = max(0.0f, speed);
}

void ModelEntity::rotateBaseTo(const fvec3 & target, float speed)
{
	_baseRotationTarget = fvec3(Mathematics::limitAngle(target.x), Mathematics::limitAngle(target.y), Mathematics::limitAngle(target.z));
	_baseRotationTargetSpeed = max(0.0f, speed);
}

void ModelEntity::scaleBaseTo(const fvec3 & target, float speed)
{
	_baseSizeTarget = fvec3(max(0.0f, target.x), max(0.0f, target.y), max(0.0f, target.z));
	_baseSizeTargetSpeed = max(0.0f, speed);
}

void ModelEntity::movePartTo(const string & partId, const fvec3 & target, float speed)
{
	_parts.at(partId)->positionTarget = target;
	_parts.at(partId)->positionTargetSpeed = max(0.0f, speed);
}

void ModelEntity::rotatePartTo(const string & partId, const fvec3 & target, float speed)
{
	_parts.at(partId)->rotationTarget = fvec3(Mathematics::limitAngle(target.x), Mathematics::limitAngle(target.y), Mathematics::limitAngle(target.z));
	_parts.at(partId)->rotationTargetSpeed = max(0.0f, speed);
}

void ModelEntity::scalePartTo(const string & partId, const fvec3 & target, float speed)
{
	_parts.at(partId)->sizeTarget = fvec3(max(0.0f, target.x), max(0.0f, target.y), max(0.0f, target.z));
	_parts.at(partId)->sizeTargetSpeed = max(0.0f, speed);
}

void ModelEntity::setColor(const string & partId, const fvec3 & value)
{
	_parts.at(partId)->color = fvec3(clamp(value.x, 0.0f, 1.0f), clamp(value.y, 0.0f, 1.0f), clamp(value.z, 0.0f, 1.0f));
}

void ModelEntity::setWireframeColor(const string & partId, const fvec3 & value)
{
	_parts.at(partId)->wireframeColor = fvec3(clamp(value.x, 0.0f, 1.0f), clamp(value.y, 0.0f, 1.0f), clamp(value.z, 0.0f, 1.0f));
}

void ModelEntity::setMeshPath(const string & value)
{
	_meshPath = value;
}

void ModelEntity::setDiffuseMapPath(const string & partId, const string & value)
{
	_parts.at(partId)->diffuseMapPath = value;
}

void ModelEntity::setEmissionMapPath(const string & partId, const string & value)
{
	_parts.at(partId)->emissionMapPath = value;
}

void ModelEntity::setSpecularMapPath(const string & partId, const string & value)
{
	_parts.at(partId)->specularMapPath = value;
}

void ModelEntity::setReflectionMapPath(const string & partId, const string & value)
{
	_parts.at(partId)->reflectionMapPath = value;
}

void ModelEntity::setNormalMapPath(const string & partId, const string & value)
{
	_parts.at(partId)->normalMapPath = value;
}

void ModelEntity::setLevelOfDetailEntityId(const string & value)
{
	_levelOfDetailEntityId = value;
}

void ModelEntity::setPreviousReflectionEntityId(const string & value)
{
	_previousReflectionEntityId = value;
}

void ModelEntity::setCurrentReflectionEntityId(const string & value)
{
	_currentReflectionEntityId = value;
}

void ModelEntity::setCubeReflectionMixValue(float value)
{
	_cubeReflectionMixValue = clamp(value, 0.0f, 1.0f);
}

void ModelEntity::setReflectivity(const string & partId, float value)
{
	_parts.at(partId)->reflectivity = clamp(value, 0.0f, 1.0f);
}

void ModelEntity::setFaceCulled(const string & partId, bool value)
{
	_parts.at(partId)->isFaceCulled = value;
}

void ModelEntity::setRotationOrder(DirectionOrder value)
{
	_rotationOrder = value;
}

void ModelEntity::setMinTextureAlpha(const string & partId, float value)
{
	_parts.at(partId)->minTextureAlpha = clamp(value, 0.0f, 1.0f);
}

void ModelEntity::setReflectionType(const string & partId, ReflectionType value)
{
	_parts.at(partId)->reflectionType = value;
}

void ModelEntity::setSpecular(const string & partId, bool value)
{
	_parts.at(partId)->isSpecular = value;
}

void ModelEntity::setReflective(const string & partId, bool value)
{
	_parts.at(partId)->isReflective = value;
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

void ModelEntity::setLevelOfDetailed(bool value)
{
	_isLevelOfDetailed = value;
}

void ModelEntity::setWireframed(const string & partId, bool value)
{
	_parts.at(partId)->isWireframed = value;
}

void ModelEntity::setBright(const string & partId, bool value)
{
	_parts.at(partId)->isBright = value;
}

void ModelEntity::setLightness(const string & partId, float value)
{
	_parts.at(partId)->lightness = max(0.0f, value);
}

void ModelEntity::setSpecularShininess(const string & partId, float value)
{
	_parts.at(partId)->specularShininess = max(0.0f, value);
}

void ModelEntity::setSpecularIntensity(const string & partId, float value)
{
	_parts.at(partId)->specularIntensity = max(0.0f, value);
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
	_levelOfDetailDistance = max(0.0f, value);
}

void ModelEntity::setOpacity(const string & partId, float value)
{
	_parts.at(partId)->opacity = clamp(value, 0.0f, 1.0f);
}

void ModelEntity::setTextureRepeat(const string & partId, unsigned int value)
{
	_parts.at(partId)->textureRepeat = max(unsigned int(1), value);
}

void ModelEntity::setEmissionIntensity(const string & partId, float value)
{
	_parts.at(partId)->emissionIntensity = max(0.0f, value);
}

void ModelEntity::_correctPositionTarget(fvec3 & current, const fvec3 & target, float speed)
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

void ModelEntity::_correctRotationTarget(fvec3 & current, const fvec3 & target, float speed)
{
	current = fvec3(Mathematics::limitAngle(current.x), Mathematics::limitAngle(current.y), Mathematics::limitAngle(current.z));

	if(Mathematics::calculateAngleDifference(current.x, target.x) <= speed)
	{
		current.x = target.x;
	}

	if(Mathematics::calculateAngleDifference(current.y, target.y) <= speed)
	{
		current.y = target.y;
	}

	if(Mathematics::calculateAngleDifference(current.z, target.z) <= speed)
	{
		current.z = target.z;
	}
}

void ModelEntity::_correctSizeTarget(fvec3 & current, const fvec3 & target, float speed)
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

const shared_ptr<VertexBuffer> ModelEntity::getVertexBuffer(const string & partId) const
{
	return _parts.at(partId)->vertexBuffer;
}

const mat44 & ModelEntity::getTransformation(const string & partId) const
{
	return _parts.at(partId)->transformation;
}

const shared_ptr<TextureBuffer> ModelEntity::getDiffuseTextureBuffer(const string & partId) const
{
	return _parts.at(partId)->diffuseTextureBuffer;
}

const shared_ptr<TextureBuffer> ModelEntity::getEmissionTextureBuffer(const string & partId) const
{
	return _parts.at(partId)->emissionTextureBuffer;
}

const shared_ptr<TextureBuffer> ModelEntity::getSpecularTextureBuffer(const string & partId) const
{
	return _parts.at(partId)->specularTextureBuffer;
}

const shared_ptr<TextureBuffer> ModelEntity::getReflectionTextureBuffer(const string & partId) const
{
	return _parts.at(partId)->reflectionTextureBuffer;
}

const shared_ptr<TextureBuffer> ModelEntity::getNormalTextureBuffer(const string & partId) const
{
	return _parts.at(partId)->normalTextureBuffer;
}

const fvec3 & ModelEntity::getColor(const string & partId) const
{
	return _parts.at(partId)->color;
}

const fvec3 & ModelEntity::getWireframeColor(const string & partId) const
{
	return _parts.at(partId)->wireframeColor;
}

const fvec3 & ModelEntity::getBasePosition() const
{
	return _basePosition;
}

const fvec3 & ModelEntity::getBaseRotation() const
{
	return _baseRotation;
}

const fvec3 & ModelEntity::getBaseRotationOrigin() const
{
	return _baseRotationOrigin;
}

const fvec3 & ModelEntity::getBaseSize() const
{
	return _baseSize;
}

const fvec3 & ModelEntity::getPartPosition(const string & partId) const
{
	return _parts.at(partId)->position;
}

const fvec3 & ModelEntity::getPartRotation(const string & partId) const
{
	return _parts.at(partId)->rotation;
}

const fvec3 & ModelEntity::getPartRotationOrigin(const string & partId) const
{
	return _parts.at(partId)->rotationOrigin;
}

const fvec3 & ModelEntity::getPartSize(const string & partId) const
{
	return _parts.at(partId)->size;
}

const float ModelEntity::getCubeReflectionMixValue() const
{
	return _cubeReflectionMixValue;
}

const float ModelEntity::getReflectivity(const string & partId) const
{
	return _parts.at(partId)->reflectivity;
}

const string & ModelEntity::getMeshPath() const
{
	return _meshPath;
}

const string & ModelEntity::getDiffuseMapPath(const string & partId) const
{
	return _parts.at(partId)->diffuseMapPath;
}

const string & ModelEntity::getEmissionMapPath(const string & partId) const
{
	return _parts.at(partId)->emissionMapPath;
}

const string & ModelEntity::getSpecularMapPath(const string & partId) const
{
	return _parts.at(partId)->specularMapPath;
}

const string & ModelEntity::getReflectionMapPath(const string & partId) const
{
	return _parts.at(partId)->reflectionMapPath;
}

const string & ModelEntity::getNormalMapPath(const string & partId) const
{
	return _parts.at(partId)->normalMapPath;
}

const string & ModelEntity::getLevelOfDetailEntityId() const
{
	return _levelOfDetailEntityId;
}

const string & ModelEntity::getPreviousReflectionEntityId() const
{
	return _previousReflectionEntityId;
}

const string & ModelEntity::getCurrentReflectionEntityId() const
{
	return _currentReflectionEntityId;
}

const vector<string> ModelEntity::getPartIds() const
{
	vector<string> result;

	for(const auto & [partId, part] : _parts)
	{
		result.push_back(partId);
	}

	return result;
}

const bool ModelEntity::isFaceCulled(const string & partId) const
{
	return _parts.at(partId)->isFaceCulled;
}

const bool ModelEntity::isWireframed(const string & partId) const
{
	return _parts.at(partId)->isWireframed;
}

const bool ModelEntity::isSpecular(const string & partId) const
{
	return _parts.at(partId)->isSpecular;
}

const bool ModelEntity::isReflective(const string & partId) const
{
	return _parts.at(partId)->isReflective;
}

const bool ModelEntity::isShadowed() const
{
	return _isShadowed;
}

const bool ModelEntity::isReflected() const
{
	return _isReflected;
}

const ReflectionType ModelEntity::getReflectionType(const string & partId) const
{
	return _parts.at(partId)->reflectionType;
}

const DirectionOrder ModelEntity::getRotationOrder() const
{
	return _rotationOrder;
}

const bool ModelEntity::isBright(const string & partId) const
{
	return _parts.at(partId)->isBright;
}

const bool ModelEntity::isFrozen() const
{
	return _isFrozen;
}

const bool ModelEntity::isLevelOfDetailed() const
{
	return _isLevelOfDetailed;
}

const float ModelEntity::getLightness(const string & partId) const
{
	return _parts.at(partId)->lightness;
}

const float ModelEntity::getSpecularShininess(const string & partId) const
{
	return _parts.at(partId)->specularShininess;
}

const float ModelEntity::getSpecularIntensity(const string & partId) const
{
	return _parts.at(partId)->specularIntensity;
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

const float ModelEntity::getEmissionIntensity(const string & partId) const
{
	return _parts.at(partId)->emissionIntensity;
}

const float ModelEntity::getMinTextureAlpha(const string & partId) const
{
	return _parts.at(partId)->minTextureAlpha;
}

const float ModelEntity::getOpacity(const string & partId) const
{
	return _parts.at(partId)->opacity;
}

const unsigned int ModelEntity::getTextureRepeat(const string & partId) const
{
	return _parts.at(partId)->textureRepeat;
}