#include "model_entity.hpp"
#include "logger.hpp"

const Matrix44& ModelEntity::getModelMatrix(const string& partID)
{
	return _parts[_getPartIndex(partID)].modelMatrix;
}

const GLuint ModelEntity::getDiffuseMap(const string& partID)
{
	return _parts[_getPartIndex(partID)].diffuseMap;
}

const GLuint ModelEntity::getLightMap(const string& partID)
{
	return _parts[_getPartIndex(partID)].lightMap;
}

const GLuint ModelEntity::getReflectionMap(const string& partID)
{
	return _parts[_getPartIndex(partID)].reflectionMap;
}

const GLuint ModelEntity::getNormalMap(const string& partID)
{
	return _parts[_getPartIndex(partID)].normalMap;
}

const Vec3 ModelEntity::getColor(const string& partID)
{
	if (partID.empty())
	{
		Vec3 total = Vec3(0.0f);
		for (auto& part : _parts)
		{
			total += part.color;
		}
		return total / static_cast<float>(_parts.size());
	}
	else
	{
		return _parts[_getPartIndex(partID)].color;
	}
}

const Vec3 ModelEntity::getTranslation(const string& partID)
{
	if (_parts.size() == 1 || (_parts.size() > 1 && partID.empty()))
	{
		return _baseTranslation;
	}
	else
	{
		return _parts[_getPartIndex(partID)].localTranslation;
	}
}

const Vec3 ModelEntity::getRotation(const string& partID)
{
	if (_parts.size() == 1 || (_parts.size() > 1 && partID.empty()))
	{
		return _baseRotation;
	}
	else
	{
		return _parts[_getPartIndex(partID)].localRotation;
	}
}

const Vec3 ModelEntity::getRotationOrigin(const string& partID)
{
	if (_parts.size() == 1 || (_parts.size() > 1 && partID.empty()))
	{
		return _baseRotationOrigin;
	}
	else
	{
		return _parts[_getPartIndex(partID)].localRotationOrigin;
	}
}

const Vec3 ModelEntity::getScaling(const string& partID)
{
	if (_parts.size() == 1 || (_parts.size() > 1 && partID.empty()))
	{
		return _baseScaling;
	}
	else
	{
		return _parts[_getPartIndex(partID)].localScaling;
	}
}

const Vec3 ModelEntity::getLevelOfDetailScaling()
{
	return _levelOfDetailScaling;
}

const float ModelEntity::getInversion(const string& partID)
{
	if (partID.empty())
	{
		float total = 0.0f;
		for (auto& part : _parts)
		{
			total += part.inversion;
		}
		return total / static_cast<float>(_parts.size());
	}
	else
	{
		return _parts[_getPartIndex(partID)].inversion;
	}
}

const string& ModelEntity::getMeshPath()
{
	return _meshPath;
}

const string& ModelEntity::getDiffuseMapPath(const string& partID)
{
	return _parts[_getPartIndex(partID)].diffuseMapPath;
}

const string& ModelEntity::getLightMapPath(const string& partID)
{
	return _parts[_getPartIndex(partID)].lightMapPath;
}

const string& ModelEntity::getReflectionMapPath(const string& partID)
{
	return _parts[_getPartIndex(partID)].reflectionMapPath;
}

const string& ModelEntity::getNormalMapPath(const string& partID)
{
	return _parts[_getPartIndex(partID)].normalMapPath;
}

const string& ModelEntity::getLodEntityID()
{
	return _lodEntityID;
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

const bool ModelEntity::isTransparent()
{
	return _isTransparent;
}

const bool ModelEntity::isFaceCulled()
{
	return _isFaceCulled;
}

const bool ModelEntity::isSpecularLighted()
{
	return _isSpecularLighted;
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
	if (partID.empty())
	{
		for (const auto& part : _parts)
		{
			if (part.diffuseMap != 0)
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		return (_parts[_getPartIndex(partID)].diffuseMap != 0);
	}
}

const bool ModelEntity::hasLightMap(const string& partID)
{
	if (partID.empty())
	{
		for (const auto& part : _parts)
		{
			if (part.lightMap != 0)
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		return (_parts[_getPartIndex(partID)].lightMap != 0);
	}
}

const bool ModelEntity::hasReflectionMap(const string& partID)
{
	if (partID.empty())
	{
		for (const auto& part : _parts)
		{
			if (part.reflectionMap != 0)
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		return (_parts[_getPartIndex(partID)].reflectionMap != 0);
	}
}

const bool ModelEntity::hasNormalMap(const string& partID)
{
	if (partID.empty())
	{
		for (const auto& part : _parts)
		{
			if (part.normalMap != 0)
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		return (_parts[_getPartIndex(partID)].normalMap != 0);
	}
}

const ReflectionType ModelEntity::getReflectionType()
{
	return _reflectionType;
}

const bool ModelEntity::isBright()
{
	return _isBright;
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

const bool ModelEntity::isWireframed()
{
	return _wireframed;
}

const float ModelEntity::getLightness()
{
	return _lightness;
}

const float ModelEntity::getSpecularFactor()
{
	return _specularFactor;
}

const float ModelEntity::getSpecularIntensity()
{
	return _specularIntensity;
}

const float ModelEntity::getMinHeight()
{
	return _minHeight;
}

const float ModelEntity::getMaxHeight()
{
	return _maxHeight;
}

const float ModelEntity::getAlpha()
{
	return _alpha;
}

const float ModelEntity::getUvRepeat()
{
	return _uvRepeat;
}

unsigned int ModelEntity::_getPartIndex(string partID)
{
	if (partID.empty())
	{
		if (_parts.size() > 1)
		{
			Logger::throwError("Model entity with ID \"" + getID() + "\" has multiple parts!");
		}
		else
		{
			return 0;
		}
	}

	for (size_t i = 0; i < _parts.size(); i++)
	{
		if (partID == _parts[i].ID)
		{
			return static_cast<unsigned int>(i);
		}
	}

	Logger::throwError("Model entity with ID \"" + getID() + "\" has no part called \"" + partID + "\"!");
}