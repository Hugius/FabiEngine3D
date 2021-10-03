#include "model_entity.hpp"
#include "logger.hpp"

const shared_ptr<RenderBuffer> ModelEntity::getRenderBuffer(const string& partID)
{
	return _parts[_getPartIndex(partID)].renderBuffer;
}

const Matrix44& ModelEntity::getTransformationMatrix(const string& partID)
{
	return _parts[_getPartIndex(partID)].transformationMatrix;
}

const TextureID ModelEntity::getDiffuseMap(const string& partID)
{
	return _parts[_getPartIndex(partID)].diffuseMap;
}

const TextureID ModelEntity::getEmissionMap(const string& partID)
{
	return _parts[_getPartIndex(partID)].emissionMap;
}

const TextureID ModelEntity::getSpecularMap(const string& partID)
{
	return _parts[_getPartIndex(partID)].specularMap;
}

const TextureID ModelEntity::getReflectionMap(const string& partID)
{
	return _parts[_getPartIndex(partID)].reflectionMap;
}

const TextureID ModelEntity::getNormalMap(const string& partID)
{
	return _parts[_getPartIndex(partID)].normalMap;
}

const Vec3 ModelEntity::getColor(const string& partID)
{
	return _parts[_getPartIndex(partID)].color;
}

const Vec3 ModelEntity::getBasePosition()
{
	return _basePosition;
}

const Vec3 ModelEntity::getBaseRotation()
{
	return _baseRotation;
}

const Vec3 ModelEntity::getBaseRotationOrigin()
{
	return _baseRotationOrigin;
}

const Vec3 ModelEntity::getBaseSize()
{
	return _baseSize;
}

const Vec3 ModelEntity::getPartPosition(const string& partID)
{
	return _parts[_getPartIndex(partID)].position;
}

const Vec3 ModelEntity::getPartRotation(const string& partID)
{
	return _parts[_getPartIndex(partID)].rotation;
}

const Vec3 ModelEntity::getPartRotationOrigin(const string& partID)
{
	return _parts[_getPartIndex(partID)].rotationOrigin;
}

const Vec3 ModelEntity::getPartSize(const string& partID)
{
	return _parts[_getPartIndex(partID)].size;
}

const Vec3 ModelEntity::getLevelOfDetailSize()
{
	return _levelOfDetailSize;
}

const float ModelEntity::getColorInversion(const string& partID)
{
	return _parts[_getPartIndex(partID)].colorInversion;
}

const float ModelEntity::getCubeReflectionMixValue()
{
	return _cubeReflectionMixValue;
}

const float ModelEntity::getReflectivity(const string& partID)
{
	return _parts[_getPartIndex(partID)].reflectivity;
}

const string& ModelEntity::getMeshPath()
{
	return _meshPath;
}

const string& ModelEntity::getDiffuseMapPath(const string& partID)
{
	return _parts[_getPartIndex(partID)].diffuseMapPath;
}

const string& ModelEntity::getEmissionMapPath(const string& partID)
{
	return _parts[_getPartIndex(partID)].emissionMapPath;
}

const string& ModelEntity::getSpecularMapPath(const string& partID)
{
	return _parts[_getPartIndex(partID)].specularMapPath;
}

const string& ModelEntity::getReflectionMapPath(const string& partID)
{
	return _parts[_getPartIndex(partID)].reflectionMapPath;
}

const string& ModelEntity::getNormalMapPath(const string& partID)
{
	return _parts[_getPartIndex(partID)].normalMapPath;
}

const string& ModelEntity::getLevelOfDetailEntityID()
{
	return _levelOfDetailEntityID;
}

const string& ModelEntity::getPreviousReflectionEntityID()
{
	return _previousReflectionEntityID;
}

const string& ModelEntity::getCurrentReflectionEntityID()
{
	return _currentReflectionEntityID;
}

const vector<string> ModelEntity::getPartIDs()
{
	vector<string> result;

	for (const auto& part : _parts)
	{
		result.push_back(part.ID);
	}

	return result;
}

const bool ModelEntity::isFaceCulled()
{
	return _isFaceCulled;
}

const bool ModelEntity::isSpecular(const string& partID)
{
	return _parts[_getPartIndex(partID)].isSpecular;
}

const bool ModelEntity::isReflective(const string& partID)
{
	return _parts[_getPartIndex(partID)].isReflective;
}

const bool ModelEntity::isShadowed()
{
	return _isShadowed;
}

const bool ModelEntity::isReflected()
{
	return _isReflected;
}

const bool ModelEntity::hasDiffuseMap(const string& partID)
{
	return (_parts[_getPartIndex(partID)].diffuseMap != 0);
}

const bool ModelEntity::hasEmissionMap(const string& partID)
{
	return (_parts[_getPartIndex(partID)].emissionMap != 0);
}

const bool ModelEntity::hasSpecularMap(const string& partID)
{
	return (_parts[_getPartIndex(partID)].specularMap != 0);
}

const bool ModelEntity::hasReflectionMap(const string& partID)
{
	return (_parts[_getPartIndex(partID)].reflectionMap != 0);
}

const bool ModelEntity::hasNormalMap(const string& partID)
{
	return (_parts[_getPartIndex(partID)].normalMap != 0);
}

const ReflectionType ModelEntity::getReflectionType(const string& partID)
{
	return _parts[_getPartIndex(partID)].reflectionType;
}

const bool ModelEntity::isBright()
{
	return _isBright;
}

const bool ModelEntity::hasRenderBuffer(const string& partID)
{
	return (_parts[_getPartIndex(partID)].renderBuffer != nullptr);
}

const bool ModelEntity::isCameraStatic()
{
	return _isCameraStatic;
}

const bool ModelEntity::isDepthMapIncluded()
{
	return _isDepthMapIncluded;
}

const bool ModelEntity::isLevelOfDetailed()
{
	return _isLevelOfDetailed;
}

const bool ModelEntity::isWireFramed()
{
	return _isWireFramed;
}

const float ModelEntity::getLightness(const string& partID)
{
	return _parts[_getPartIndex(partID)].lightness;
}

const float ModelEntity::getSpecularShininess(const string& partID)
{
	return _parts[_getPartIndex(partID)].specularShininess;
}

const float ModelEntity::getSpecularIntensity(const string& partID)
{
	return _parts[_getPartIndex(partID)].specularIntensity;
}

const float ModelEntity::getMinHeight()
{
	return _minHeight;
}

const float ModelEntity::getMaxHeight()
{
	return _maxHeight;
}

const float ModelEntity::getEmissionIntensity(const string& partID)
{
	return _parts[_getPartIndex(partID)].emissionIntensity;
}

const float ModelEntity::getAlpha(const string& partID)
{
	return _parts[_getPartIndex(partID)].alpha;
}

const float ModelEntity::getTextureRepeat(const string& partID)
{
	return _parts[_getPartIndex(partID)].textureRepeat;
}

unsigned int ModelEntity::_getPartIndex(const string& partID)
{
	// Validate parts amount
	if (partID.empty())
	{
		if (_parts.size() > 1)
		{
			Logger::throwError("ModelEntity::_getPartIndex::1");
		}
		else
		{
			return 0;
		}
	}

	// Try to find index
	for (size_t i = 0; i < _parts.size(); i++)
	{
		if (partID == _parts[i].ID)
		{
			return static_cast<unsigned int>(i);
		}
	}

	// Part is not found
	Logger::throwError("ModelEntity::_getPartIndex::2");
}