#include "model_entity.hpp"
#include "logger.hpp"

const shared_ptr<RenderBuffer> ModelEntity::getRenderBuffer(const string& partID) const
{
	return _parts[_getPartIndex(partID)].renderBuffer;
}

const mat44& ModelEntity::getTransformationMatrix(const string& partID) const
{
	return _parts[_getPartIndex(partID)].transformationMatrix;
}

const TextureID ModelEntity::getDiffuseMap(const string& partID) const
{
	return _parts[_getPartIndex(partID)].diffuseMap;
}

const TextureID ModelEntity::getEmissionMap(const string& partID) const
{
	return _parts[_getPartIndex(partID)].emissionMap;
}

const TextureID ModelEntity::getSpecularMap(const string& partID) const
{
	return _parts[_getPartIndex(partID)].specularMap;
}

const TextureID ModelEntity::getReflectionMap(const string& partID) const
{
	return _parts[_getPartIndex(partID)].reflectionMap;
}

const TextureID ModelEntity::getNormalMap(const string& partID) const
{
	return _parts[_getPartIndex(partID)].normalMap;
}

const fvec3 ModelEntity::getColor(const string& partID) const
{
	return _parts[_getPartIndex(partID)].color;
}

const fvec3 ModelEntity::getWireframeColor(const string& partID) const
{
	return _parts[_getPartIndex(partID)].wireframeColor;
}

const fvec3 ModelEntity::getBasePosition() const
{
	return _basePosition;
}

const fvec3 ModelEntity::getBaseRotation() const
{
	return _baseRotation;
}

const fvec3 ModelEntity::getBaseRotationOrigin() const
{
	return _baseRotationOrigin;
}

const fvec3 ModelEntity::getBaseSize() const
{
	return _baseSize;
}

const fvec3 ModelEntity::getPartPosition(const string& partID) const
{
	return _parts[_getPartIndex(partID)].position;
}

const fvec3 ModelEntity::getPartRotation(const string& partID) const
{
	return _parts[_getPartIndex(partID)].rotation;
}

const fvec3 ModelEntity::getPartRotationOrigin(const string& partID) const
{
	return _parts[_getPartIndex(partID)].rotationOrigin;
}

const fvec3 ModelEntity::getPartSize(const string& partID) const
{
	return _parts[_getPartIndex(partID)].size;
}

const fvec3 ModelEntity::getLevelOfDetailSize() const
{
	return _levelOfDetailSize;
}

const float ModelEntity::getCubeReflectionMixValue() const
{
	return _cubeReflectionMixValue;
}

const float ModelEntity::getReflectivity(const string& partID) const
{
	return _parts[_getPartIndex(partID)].reflectivity;
}

const string& ModelEntity::getMeshPath() const
{
	return _meshPath;
}

const string& ModelEntity::getDiffuseMapPath(const string& partID) const
{
	return _parts[_getPartIndex(partID)].diffuseMapPath;
}

const string& ModelEntity::getEmissionMapPath(const string& partID) const
{
	return _parts[_getPartIndex(partID)].emissionMapPath;
}

const string& ModelEntity::getSpecularMapPath(const string& partID) const
{
	return _parts[_getPartIndex(partID)].specularMapPath;
}

const string& ModelEntity::getReflectionMapPath(const string& partID) const
{
	return _parts[_getPartIndex(partID)].reflectionMapPath;
}

const string& ModelEntity::getNormalMapPath(const string& partID) const
{
	return _parts[_getPartIndex(partID)].normalMapPath;
}

const string& ModelEntity::getLevelOfDetailEntityID() const
{
	return _levelOfDetailEntityID;
}

const string& ModelEntity::getPreviousReflectionEntityID() const
{
	return _previousReflectionEntityID;
}

const string& ModelEntity::getCurrentReflectionEntityID() const
{
	return _currentReflectionEntityID;
}

const vector<string> ModelEntity::getPartIDs() const
{
	vector<string> result;

	for(const auto& part : _parts)
	{
		result.push_back(part.ID);
	}

	return result;
}

const bool ModelEntity::isFaceCulled() const
{
	return _isFaceCulled;
}

const bool ModelEntity::isWireframed(const string& partID) const
{
	return _parts[_getPartIndex(partID)].isWireframed;
}

const bool ModelEntity::isSpecular(const string& partID) const
{
	return _parts[_getPartIndex(partID)].isSpecular;
}

const bool ModelEntity::isReflective(const string& partID) const
{
	return _parts[_getPartIndex(partID)].isReflective;
}

const bool ModelEntity::isShadowed() const
{
	return _isShadowed;
}

const bool ModelEntity::isReflected() const
{
	return _isReflected;
}

const bool ModelEntity::hasDiffuseMap(const string& partID) const
{
	return (_parts[_getPartIndex(partID)].diffuseMap != 0);
}

const bool ModelEntity::hasEmissionMap(const string& partID) const
{
	return (_parts[_getPartIndex(partID)].emissionMap != 0);
}

const bool ModelEntity::hasSpecularMap(const string& partID) const
{
	return (_parts[_getPartIndex(partID)].specularMap != 0);
}

const bool ModelEntity::hasReflectionMap(const string& partID) const
{
	return (_parts[_getPartIndex(partID)].reflectionMap != 0);
}

const bool ModelEntity::hasNormalMap(const string& partID) const
{
	return (_parts[_getPartIndex(partID)].normalMap != 0);
}

const ReflectionType ModelEntity::getReflectionType(const string& partID) const
{
	return _parts[_getPartIndex(partID)].reflectionType;
}

const DirectionOrder ModelEntity::getRotationOrder() const
{
	return _rotationOrder;
}

const bool ModelEntity::isBright() const
{
	return _isBright;
}

const bool ModelEntity::hasRenderBuffer(const string& partID) const
{
	return (_parts[_getPartIndex(partID)].renderBuffer != nullptr);
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

const float ModelEntity::getLightness(const string& partID) const
{
	return _parts[_getPartIndex(partID)].lightness;
}

const float ModelEntity::getSpecularShininess(const string& partID) const
{
	return _parts[_getPartIndex(partID)].specularShininess;
}

const float ModelEntity::getSpecularIntensity(const string& partID) const
{
	return _parts[_getPartIndex(partID)].specularIntensity;
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

const float ModelEntity::getEmissionIntensity(const string& partID) const
{
	return _parts[_getPartIndex(partID)].emissionIntensity;
}

const float ModelEntity::getTransparency(const string& partID) const
{
	return _parts[_getPartIndex(partID)].transparency;
}

const float ModelEntity::getTextureRepeat(const string& partID) const
{
	return _parts[_getPartIndex(partID)].textureRepeat;
}

const unsigned int ModelEntity::_getPartIndex(const string& partID) const
{
	// Validate parts amount
	if(partID.empty())
	{
		if(_parts.size() > 1)
		{
			Logger::throwError("ModelEntity::_getPartIndex::1");
		}
		else
		{
			return 0;
		}
	}

	// Try to find index
	for(size_t i = 0; i < _parts.size(); i++)
	{
		if(partID == _parts[i].ID)
		{
			return static_cast<unsigned int>(i);
		}
	}

	// Part is not found
	Logger::throwError("ModelEntity::_getPartIndex::2");
}