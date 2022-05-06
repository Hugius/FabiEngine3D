#include "model.hpp"

#include <algorithm>

using std::max;
using std::clamp;
using std::make_unique;

Model::Model(const string & id)
	:
	_id(id)
{
	if(id.empty())
	{
		abort();
	}
}

void Model::createPart(const string & partId)
{
	_parts.insert({partId, make_unique<ModelPart>()});
}

void Model::deletePart(const string & partId)
{
	_parts.erase(partId);
}

void Model::deleteParts()
{
	_parts.clear();
}

void Model::updateTarget()
{
	if(_basePosition != _basePositionTarget)
	{
		const auto speedMultiplier = Mathematics::normalize(_basePositionTarget - _basePosition);
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
		const auto speedMultiplier = Mathematics::normalize(_baseSizeTarget - _baseSize);
		_baseSize += (speedMultiplier * _baseSizeTargetSpeed);
		_correctSizeTarget(_baseSize, _baseSizeTarget, _baseSizeTargetSpeed);
	}

	for(auto & [partId, part] : _parts)
	{
		if(part->position != part->positionTarget)
		{
			const auto speedMultiplier = Mathematics::normalize(part->positionTarget - part->position);
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
			const auto speedMultiplier = Mathematics::normalize(part->sizeTarget - part->size);
			part->size += (speedMultiplier * part->sizeTargetSpeed);
			_correctSizeTarget(part->size, part->sizeTarget, part->sizeTargetSpeed);
		}
	}
}

void Model::updateTransformation()
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

void Model::setVertexBuffer(const string & partId, shared_ptr<VertexBuffer> value)
{
	_parts.at(partId)->vertexBuffer = value;
}

void Model::setDiffuseTextureBuffer(const string & partId, shared_ptr<TextureBuffer> value)
{
	_parts.at(partId)->diffuseTextureBuffer = value;
}

void Model::setEmissionTextureBuffer(const string & partId, shared_ptr<TextureBuffer> value)
{
	_parts.at(partId)->emissionTextureBuffer = value;
}

void Model::setSpecularTextureBuffer(const string & partId, shared_ptr<TextureBuffer> value)
{
	_parts.at(partId)->specularTextureBuffer = value;
}

void Model::setReflectionTextureBuffer(const string & partId, shared_ptr<TextureBuffer> value)
{
	_parts.at(partId)->reflectionTextureBuffer = value;
}

void Model::setRefractionTextureBuffer(const string & partId, shared_ptr<TextureBuffer> value)
{
	_parts.at(partId)->refractionTextureBuffer = value;
}

void Model::setNormalTextureBuffer(const string & partId, shared_ptr<TextureBuffer> value)
{
	_parts.at(partId)->normalTextureBuffer = value;
}

void Model::setBasePosition(const fvec3 & value)
{
	_basePosition = value;
	_basePositionTarget = _basePosition;
}

void Model::setBaseRotation(const fvec3 & value)
{
	_baseRotation = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
	_baseRotationTarget = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
}

void Model::setBaseRotationOrigin(const fvec3 & value)
{
	_baseRotationOrigin = value;
}

void Model::setBaseSize(const fvec3 & value)
{
	_baseSize = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
	_baseSizeTarget = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void Model::setPartPosition(const string & partId, const fvec3 & value)
{
	_parts.at(partId)->position = value;
	_parts.at(partId)->positionTarget = value;
}

void Model::setPartRotation(const string & partId, const fvec3 & value)
{
	_parts.at(partId)->rotation = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
	_parts.at(partId)->rotationTarget = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
}

void Model::setPartRotationOrigin(const string & partId, const fvec3 & value)
{
	_parts.at(partId)->rotationOrigin = value;
}

void Model::setPartSize(const string & partId, const fvec3 & value)
{
	_parts.at(partId)->size = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
	_parts.at(partId)->sizeTarget = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void Model::moveBase(const fvec3 & value)
{
	_basePosition += value;
	_basePositionTarget += value;
}

void Model::rotateBase(const fvec3 & value)
{
	_baseRotation += value;
	_baseRotationTarget += value;
	_baseRotation = fvec3(Mathematics::limitAngle(_baseRotation.x), Mathematics::limitAngle(_baseRotation.y), Mathematics::limitAngle(_baseRotation.z));
	_baseRotationTarget = fvec3(Mathematics::limitAngle(_baseRotationTarget.x), Mathematics::limitAngle(_baseRotationTarget.y), Mathematics::limitAngle(_baseRotationTarget.z));
}

void Model::scaleBase(const fvec3 & value)
{
	_baseSize += value;
	_baseSizeTarget += value;
	_baseSize = fvec3(max(0.0f, _baseSize.x), max(0.0f, _baseSize.y), max(0.0f, _baseSize.z));
	_baseSizeTarget = fvec3(max(0.0f, _baseSizeTarget.x), max(0.0f, _baseSizeTarget.y), max(0.0f, _baseSizeTarget.z));
}

void Model::movePart(const string & partId, const fvec3 & value)
{
	_parts.at(partId)->position += value;
	_parts.at(partId)->positionTarget += value;
}

void Model::rotatePart(const string & partId, const fvec3 & value)
{
	fvec3 & rotation = _parts.at(partId)->rotation;
	fvec3 & rotationTarget = _parts.at(partId)->rotationTarget;
	rotation += value;
	rotationTarget += value;
	rotation = fvec3(Mathematics::limitAngle(rotation.x), Mathematics::limitAngle(rotation.y), Mathematics::limitAngle(rotation.z));
	rotationTarget = fvec3(Mathematics::limitAngle(rotationTarget.x), Mathematics::limitAngle(rotationTarget.y), Mathematics::limitAngle(rotationTarget.z));
}

void Model::scalePart(const string & partId, const fvec3 & value)
{
	fvec3 & size = _parts.at(partId)->size;
	fvec3 & sizeTarget = _parts.at(partId)->sizeTarget;
	size += value;
	sizeTarget += value;
	size = fvec3(max(0.0f, size.x), max(0.0f, size.y), max(0.0f, size.z));
	sizeTarget = fvec3(max(0.0f, sizeTarget.x), max(0.0f, sizeTarget.y), max(0.0f, sizeTarget.z));
}

void Model::moveBaseTo(const fvec3 & target, float speed)
{
	_basePositionTarget = target;
	_basePositionTargetSpeed = max(0.0f, speed);
}

void Model::rotateBaseTo(const fvec3 & target, float speed)
{
	_baseRotationTarget = fvec3(Mathematics::limitAngle(target.x), Mathematics::limitAngle(target.y), Mathematics::limitAngle(target.z));
	_baseRotationTargetSpeed = max(0.0f, speed);
}

void Model::scaleBaseTo(const fvec3 & target, float speed)
{
	_baseSizeTarget = fvec3(max(0.0f, target.x), max(0.0f, target.y), max(0.0f, target.z));
	_baseSizeTargetSpeed = max(0.0f, speed);
}

void Model::movePartTo(const string & partId, const fvec3 & target, float speed)
{
	_parts.at(partId)->positionTarget = target;
	_parts.at(partId)->positionTargetSpeed = max(0.0f, speed);
}

void Model::rotatePartTo(const string & partId, const fvec3 & target, float speed)
{
	_parts.at(partId)->rotationTarget = fvec3(Mathematics::limitAngle(target.x), Mathematics::limitAngle(target.y), Mathematics::limitAngle(target.z));
	_parts.at(partId)->rotationTargetSpeed = max(0.0f, speed);
}

void Model::scalePartTo(const string & partId, const fvec3 & target, float speed)
{
	_parts.at(partId)->sizeTarget = fvec3(max(0.0f, target.x), max(0.0f, target.y), max(0.0f, target.z));
	_parts.at(partId)->sizeTargetSpeed = max(0.0f, speed);
}

void Model::setColor(const string & partId, const fvec3 & value)
{
	_parts.at(partId)->color = fvec3(clamp(value.x, 0.0f, 1.0f), clamp(value.y, 0.0f, 1.0f), clamp(value.z, 0.0f, 1.0f));
}

void Model::setWireframeColor(const string & partId, const fvec3 & value)
{
	_parts.at(partId)->wireframeColor = fvec3(clamp(value.x, 0.0f, 1.0f), clamp(value.y, 0.0f, 1.0f), clamp(value.z, 0.0f, 1.0f));
}

void Model::setMeshPath(const string & value)
{
	_meshPath = value;
}

void Model::setDiffuseMapPath(const string & partId, const string & value)
{
	_parts.at(partId)->diffuseMapPath = value;
}

void Model::setEmissionMapPath(const string & partId, const string & value)
{
	_parts.at(partId)->emissionMapPath = value;
}

void Model::setSpecularMapPath(const string & partId, const string & value)
{
	_parts.at(partId)->specularMapPath = value;
}

void Model::setReflectionMapPath(const string & partId, const string & value)
{
	_parts.at(partId)->reflectionMapPath = value;
}

void Model::setRefractionMapPath(const string & partId, const string & value)
{
	_parts.at(partId)->refractionMapPath = value;
}

void Model::setNormalMapPath(const string & partId, const string & value)
{
	_parts.at(partId)->normalMapPath = value;
}

void Model::setLevelOfDetailId(const string & value)
{
	_levelOfDetailId = value;
}

void Model::setPreviousCaptorId(const string & value)
{
	_previousCaptorId = value;
}

void Model::setCurrentCaptorId(const string & value)
{
	_currentCaptorId = value;
}

void Model::setCubeReflectionMixValue(float value)
{
	_cubeReflectionMixValue = clamp(value, 0.0f, 1.0f);
}

void Model::setReflectivity(const string & partId, float value)
{
	_parts.at(partId)->reflectivity = clamp(value, 0.0f, 1.0f);
}

void Model::setFaceCulled(const string & partId, bool value)
{
	_parts.at(partId)->isFaceCulled = value;
}

void Model::setRotationOrder(DirectionOrderType value)
{
	_rotationOrder = value;
}

void Model::setMinTextureAlpha(const string & partId, float value)
{
	_parts.at(partId)->minTextureAlpha = clamp(value, 0.0f, 1.0f);
}

void Model::setReflectionType(const string & partId, ReflectionType value)
{
	_parts.at(partId)->reflectionType = value;
}

void Model::setSpecular(const string & partId, bool value)
{
	_parts.at(partId)->isSpecular = value;
}

void Model::setReflective(const string & partId, bool value)
{
	_parts.at(partId)->isReflective = value;
}

void Model::setShadowed(bool value)
{
	_isShadowed = value;
}

void Model::setReflected(bool value)
{
	_isReflected = value;
}

void Model::setFrozen(bool value)
{
	_isFrozen = value;
}

void Model::setLevelOfDetailed(bool value)
{
	_isLevelOfDetailed = value;
}

void Model::setWireframed(const string & partId, bool value)
{
	_parts.at(partId)->isWireframed = value;
}

void Model::setBright(const string & partId, bool value)
{
	_parts.at(partId)->isBright = value;
}

void Model::setLightness(const string & partId, float value)
{
	_parts.at(partId)->lightness = max(0.0f, value);
}

void Model::setSpecularShininess(const string & partId, float value)
{
	_parts.at(partId)->specularShininess = max(0.0f, value);
}

void Model::setSpecularIntensity(const string & partId, float value)
{
	_parts.at(partId)->specularIntensity = max(0.0f, value);
}

void Model::setMinClipPosition(const fvec3 & value)
{
	_minClipPosition = value;
}

void Model::setMaxClipPosition(const fvec3 & value)
{
	_maxClipPosition = value;
}

void Model::setLevelOfDetailDistance(float value)
{
	_levelOfDetailDistance = max(0.0f, value);
}

void Model::setOpacity(const string & partId, float value)
{
	_parts.at(partId)->opacity = clamp(value, 0.0f, 1.0f);
}

void Model::setTextureRepeat(const string & partId, int value)
{
	_parts.at(partId)->textureRepeat = max(1, value);
}

void Model::setEmissionIntensity(const string & partId, float value)
{
	_parts.at(partId)->emissionIntensity = max(0.0f, value);
}

void Model::_correctPositionTarget(fvec3 & current, const fvec3 & target, float speed)
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

void Model::_correctRotationTarget(fvec3 & current, const fvec3 & target, float speed)
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

void Model::_correctSizeTarget(fvec3 & current, const fvec3 & target, float speed)
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

const shared_ptr<VertexBuffer> Model::getVertexBuffer(const string & partId) const
{
	return _parts.at(partId)->vertexBuffer;
}

const mat44 & Model::getTransformation(const string & partId) const
{
	return _parts.at(partId)->transformation;
}

const shared_ptr<TextureBuffer> Model::getDiffuseTextureBuffer(const string & partId) const
{
	return _parts.at(partId)->diffuseTextureBuffer;
}

const shared_ptr<TextureBuffer> Model::getEmissionTextureBuffer(const string & partId) const
{
	return _parts.at(partId)->emissionTextureBuffer;
}

const shared_ptr<TextureBuffer> Model::getSpecularTextureBuffer(const string & partId) const
{
	return _parts.at(partId)->specularTextureBuffer;
}

const shared_ptr<TextureBuffer> Model::getReflectionTextureBuffer(const string & partId) const
{
	return _parts.at(partId)->reflectionTextureBuffer;
}

const shared_ptr<TextureBuffer> Model::getRefractionTextureBuffer(const string & partId) const
{
	return _parts.at(partId)->refractionTextureBuffer;
}

const shared_ptr<TextureBuffer> Model::getNormalTextureBuffer(const string & partId) const
{
	return _parts.at(partId)->normalTextureBuffer;
}

const fvec3 & Model::getColor(const string & partId) const
{
	return _parts.at(partId)->color;
}

const fvec3 & Model::getWireframeColor(const string & partId) const
{
	return _parts.at(partId)->wireframeColor;
}

const fvec3 & Model::getBasePosition() const
{
	return _basePosition;
}

const fvec3 & Model::getBaseRotation() const
{
	return _baseRotation;
}

const fvec3 & Model::getBaseRotationOrigin() const
{
	return _baseRotationOrigin;
}

const fvec3 & Model::getBaseSize() const
{
	return _baseSize;
}

const fvec3 & Model::getPartPosition(const string & partId) const
{
	return _parts.at(partId)->position;
}

const fvec3 & Model::getPartRotation(const string & partId) const
{
	return _parts.at(partId)->rotation;
}

const fvec3 & Model::getPartRotationOrigin(const string & partId) const
{
	return _parts.at(partId)->rotationOrigin;
}

const fvec3 & Model::getPartSize(const string & partId) const
{
	return _parts.at(partId)->size;
}

const fvec3 & Model::getMinClipPosition() const
{
	return _minClipPosition;
}

const fvec3 & Model::getMaxClipPosition() const
{
	return _maxClipPosition;
}

const float Model::getCubeReflectionMixValue() const
{
	return _cubeReflectionMixValue;
}

const float Model::getReflectivity(const string & partId) const
{
	return _parts.at(partId)->reflectivity;
}

const string & Model::getId() const
{
	return _id;
}

const string & Model::getMeshPath() const
{
	return _meshPath;
}

const string & Model::getDiffuseMapPath(const string & partId) const
{
	return _parts.at(partId)->diffuseMapPath;
}

const string & Model::getEmissionMapPath(const string & partId) const
{
	return _parts.at(partId)->emissionMapPath;
}

const string & Model::getSpecularMapPath(const string & partId) const
{
	return _parts.at(partId)->specularMapPath;
}

const string & Model::getReflectionMapPath(const string & partId) const
{
	return _parts.at(partId)->reflectionMapPath;
}

const string & Model::getRefractionMapPath(const string & partId) const
{
	return _parts.at(partId)->refractionMapPath;
}

const string & Model::getNormalMapPath(const string & partId) const
{
	return _parts.at(partId)->normalMapPath;
}

const string & Model::getLevelOfDetailId() const
{
	return _levelOfDetailId;
}

const string & Model::getPreviousCaptorId() const
{
	return _previousCaptorId;
}

const string & Model::getCurrentCaptorId() const
{
	return _currentCaptorId;
}

const vector<string> Model::getPartIds() const
{
	vector<string> result;

	for(const auto & [partId, part] : _parts)
	{
		result.push_back(partId);
	}

	return result;
}

const bool Model::isFaceCulled(const string & partId) const
{
	return _parts.at(partId)->isFaceCulled;
}

const bool Model::isWireframed(const string & partId) const
{
	return _parts.at(partId)->isWireframed;
}

const bool Model::isSpecular(const string & partId) const
{
	return _parts.at(partId)->isSpecular;
}

const bool Model::isReflective(const string & partId) const
{
	return _parts.at(partId)->isReflective;
}

void Model::setVisible(bool value)
{
	_isVisible = value;
}

const bool Model::isShadowed() const
{
	return _isShadowed;
}

const bool Model::isReflected() const
{
	return _isReflected;
}

const ReflectionType Model::getReflectionType(const string & partId) const
{
	return _parts.at(partId)->reflectionType;
}

const DirectionOrderType Model::getRotationOrder() const
{
	return _rotationOrder;
}

const bool Model::isBright(const string & partId) const
{
	return _parts.at(partId)->isBright;
}

const bool Model::isVisible() const
{
	return _isVisible;
}

const bool Model::isFrozen() const
{
	return _isFrozen;
}

const bool Model::isLevelOfDetailed() const
{
	return _isLevelOfDetailed;
}

const float Model::getLightness(const string & partId) const
{
	return _parts.at(partId)->lightness;
}

const float Model::getSpecularShininess(const string & partId) const
{
	return _parts.at(partId)->specularShininess;
}

const float Model::getSpecularIntensity(const string & partId) const
{
	return _parts.at(partId)->specularIntensity;
}

const float Model::getLevelOfDetailDistance() const
{
	return _levelOfDetailDistance;
}

const float Model::getEmissionIntensity(const string & partId) const
{
	return _parts.at(partId)->emissionIntensity;
}

const float Model::getMinTextureAlpha(const string & partId) const
{
	return _parts.at(partId)->minTextureAlpha;
}

const float Model::getOpacity(const string & partId) const
{
	return _parts.at(partId)->opacity;
}

const int Model::getTextureRepeat(const string & partId) const
{
	return _parts.at(partId)->textureRepeat;
}