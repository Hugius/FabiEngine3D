#include "fe3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::model_create(const string& ID, const string& meshPath)
{
	_core->_modelEntityManager.createEntity(ID, meshPath);
}

void FabiEngine3D::model_deleteAll()
{
	// For every model entity
	for(const auto& [keyID, entity] : _core->_modelEntityManager.getEntities())
	{
		model_delete(entity->getID());
	}
}

void FabiEngine3D::model_delete(const string& ID)
{
	// Delete all bound AABB entities if existing
	for(const auto& aabbID : aabb_getChildIDs(ID, AabbParentType::MODEL_ENTITY))
	{
		_core->_aabbEntityManager.deleteEntity(aabbID);
	}

	// Delete model entity
	_core->_modelEntityManager.deleteEntity(ID);
}

void FabiEngine3D::model_deleteGroup(const string& ID)
{
	for(const auto& [keyID, entity] : _core->_modelEntityManager.getEntities()) // Iterate through model entities
	{
		if(entity->getID().size() >= ID.size()) // Check if entity ID is at least the size of group ID
		{
			auto subString = entity->getID().substr(0, ID.size());

			// If entity matches ID
			if(subString == ID)
			{
				model_delete(entity->getID());
			}
		}
	}
}

void FabiEngine3D::model_setVisible(const string& ID, bool isVisible)
{
	_core->_modelEntityManager.getEntity(ID)->setVisible(isVisible);
}

void FabiEngine3D::model_setDiffuseMap(const string& ID, const string& partID, const string& texturePath)
{
	if(texturePath.empty())
	{
		_core->_modelEntityManager.getEntity(ID)->setDiffuseMap(partID, 0);
		_core->_modelEntityManager.getEntity(ID)->setDiffuseMapPath(partID, "");
	}
	else
	{
		_core->_modelEntityManager.getEntity(ID)->setDiffuseMap(partID, _core->_textureLoader.loadTexture2D(texturePath, true, true));
		_core->_modelEntityManager.getEntity(ID)->setDiffuseMapPath(partID, texturePath);
	}
}

void FabiEngine3D::model_setEmissionMap(const string& ID, const string& partID, const string& texturePath)
{
	if(texturePath.empty())
	{
		_core->_modelEntityManager.getEntity(ID)->setEmissionMap(partID, 0);
		_core->_modelEntityManager.getEntity(ID)->setEmissionMapPath(partID, "");
	}
	else
	{
		_core->_modelEntityManager.getEntity(ID)->setEmissionMap(partID, _core->_textureLoader.loadTexture2D(texturePath, true, true));
		_core->_modelEntityManager.getEntity(ID)->setEmissionMapPath(partID, texturePath);
	}
}

void FabiEngine3D::model_setSpecularMap(const string& ID, const string& partID, const string& texturePath)
{
	if(texturePath.empty())
	{
		_core->_modelEntityManager.getEntity(ID)->setSpecularMap(partID, 0);
		_core->_modelEntityManager.getEntity(ID)->setSpecularMapPath(partID, "");
	}
	else
	{
		_core->_modelEntityManager.getEntity(ID)->setSpecularMap(partID, _core->_textureLoader.loadTexture2D(texturePath, true, true));
		_core->_modelEntityManager.getEntity(ID)->setSpecularMapPath(partID, texturePath);
	}
}

void FabiEngine3D::model_setNormalMap(const string& ID, const string& partID, const string& texturePath)
{
	if(texturePath.empty())
	{
		_core->_modelEntityManager.getEntity(ID)->setNormalMap(partID, 0);
		_core->_modelEntityManager.getEntity(ID)->setNormalMapPath(partID, "");
	}
	else
	{
		_core->_modelEntityManager.getEntity(ID)->setNormalMap(partID, _core->_textureLoader.loadTexture2D(texturePath, true, true));
		_core->_modelEntityManager.getEntity(ID)->setNormalMapPath(partID, texturePath);
	}
}

void FabiEngine3D::model_setReflectionMap(const string& ID, const string& partID, const string& texturePath)
{
	if(texturePath.empty())
	{
		_core->_modelEntityManager.getEntity(ID)->setReflectionMap(partID, 0);
		_core->_modelEntityManager.getEntity(ID)->setReflectionMapPath(partID, "");
	}
	else
	{
		_core->_modelEntityManager.getEntity(ID)->setReflectionMap(partID, _core->_textureLoader.loadTexture2D(texturePath, true, true));
		_core->_modelEntityManager.getEntity(ID)->setReflectionMapPath(partID, texturePath);
	}
}

void FabiEngine3D::model_setLevelOfDetail(const string& ID, const string& levelOfDetailID)
{
	_core->_modelEntityManager.getEntity(ID)->setLevelOfDetailEntityID(levelOfDetailID);
}

void FabiEngine3D::model_setFaceCulled(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setFaceCulled(enabled);
}

void FabiEngine3D::model_setReflectionType(const string& ID, const string& partID, ReflectionType type)
{
	_core->_modelEntityManager.getEntity(ID)->setReflectionType(partID, type);
}

void FabiEngine3D::model_setSpecular(const string& ID, const string& partID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setSpecular(partID, enabled);
}

void FabiEngine3D::model_setReflective(const string& ID, const string& partID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setReflective(partID, enabled);
}

void FabiEngine3D::model_setBasePosition(const string& ID, Vec3 position)
{
	_core->_modelEntityManager.getEntity(ID)->setBasePosition(position);
}

void FabiEngine3D::model_setBaseRotation(const string& ID, Vec3 rotation)
{
	_core->_modelEntityManager.getEntity(ID)->setBaseRotation(rotation);
}

void FabiEngine3D::model_setBaseRotationOrigin(const string& ID, Vec3 rotationOrigin)
{
	_core->_modelEntityManager.getEntity(ID)->setBaseRotationOrigin(rotationOrigin);
}

void FabiEngine3D::model_setBaseSize(const string& ID, Vec3 size)
{
	_core->_modelEntityManager.getEntity(ID)->setBaseSize(size);
}

void FabiEngine3D::model_setPartPosition(const string& ID, const string& partID, Vec3 position)
{
	_core->_modelEntityManager.getEntity(ID)->setPartPosition(partID, position);
}

void FabiEngine3D::model_setPartRotation(const string& ID, const string& partID, Vec3 rotation)
{
	_core->_modelEntityManager.getEntity(ID)->setPartRotation(partID, rotation);
}

void FabiEngine3D::model_setPartRotationOrigin(const string& ID, const string& partID, Vec3 rotationOrigin)
{
	_core->_modelEntityManager.getEntity(ID)->setPartRotationOrigin(partID, rotationOrigin);
}

void FabiEngine3D::model_setPartSize(const string& ID, const string& partID, Vec3 size)
{
	_core->_modelEntityManager.getEntity(ID)->setPartSize(partID, size);
}

void FabiEngine3D::model_moveBase(const string& ID, Vec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->moveBase(change);
}

void FabiEngine3D::model_rotateBase(const string& ID, Vec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->rotateBase(change);
}

void FabiEngine3D::model_scaleBase(const string& ID, Vec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->scaleBase(change);
}

void FabiEngine3D::model_movePart(const string& ID, const string& partID, Vec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->movePart(partID, change);
}

void FabiEngine3D::model_rotatePart(const string& ID, const string& partID, Vec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->rotatePart(partID, change);
}

void FabiEngine3D::model_scalePart(const string& ID, const string& partID, Vec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->scalePart(partID, change);
}

void FabiEngine3D::model_moveBaseTo(const string& ID, Vec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->moveBaseTo(target, speed);
}

void FabiEngine3D::model_rotateBaseTo(const string& ID, Vec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->rotateBaseTo(target, speed);
}

void FabiEngine3D::model_scaleBaseTo(const string& ID, Vec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->scaleBaseTo(target, speed);
}

void FabiEngine3D::model_setSpecularShininess(const string& ID, const string& partID, float intensity)
{
	_core->_modelEntityManager.getEntity(ID)->setSpecularShininess(partID, intensity);
}

void FabiEngine3D::model_setSpecularIntensity(const string& ID, const string& partID, float intensity)
{
	_core->_modelEntityManager.getEntity(ID)->setSpecularIntensity(partID, intensity);
}

void FabiEngine3D::model_setReflectivity(const string& ID, const string& partID, float reflectivity)
{
	_core->_modelEntityManager.getEntity(ID)->setReflectivity(partID, reflectivity);
}

void FabiEngine3D::model_setLightness(const string& ID, const string& partID, float lightness)
{
	_core->_modelEntityManager.getEntity(ID)->setLightness(partID, lightness);
}

void FabiEngine3D::model_setEmissionIntensity(const string& ID, const string& partID, float intensity)
{
	_core->_modelEntityManager.getEntity(ID)->setEmissionIntensity(partID, intensity);
}

void FabiEngine3D::model_setMinHeight(const string& ID, float height)
{
	_core->_modelEntityManager.getEntity(ID)->setMinHeight(height);
}

void FabiEngine3D::model_setMaxHeight(const string& ID, float height)
{
	_core->_modelEntityManager.getEntity(ID)->setMaxHeight(height);
}

void FabiEngine3D::model_movePartTo(const string& ID, const string& partID, Vec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->movePartTo(partID, target, speed);
}

void FabiEngine3D::model_rotatePartTo(const string& ID, const string& partID, Vec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->rotatePartTo(partID, target, speed);
}

void FabiEngine3D::model_scalePartTo(const string& ID, const string& partID, Vec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->scalePartTo(partID, target, speed);
}

void FabiEngine3D::model_setLevelOfDetailSize(const string& ID, Vec3 size)
{
	_core->_modelEntityManager.getEntity(ID)->setLevelOfDetailSize(size);
}

void FabiEngine3D::model_setTextureRepeat(const string& ID, const string& partID, float repeat)
{
	_core->_modelEntityManager.getEntity(ID)->setTextureRepeat(partID, repeat);
}

void FabiEngine3D::model_enableInstancing(const string& ID, vector<Vec3> offsets)
{
	auto entity = _core->_modelEntityManager.getEntity(ID);

	for(const auto& partID : entity->getPartIDs())
	{
		entity->getRenderBuffer(partID)->enableInstancing(offsets);
	}
}

void FabiEngine3D::model_disableInstancing(const string& ID)
{
	auto entity = _core->_modelEntityManager.getEntity(ID);

	for(const auto& partID : entity->getPartIDs())
	{
		entity->getRenderBuffer(partID)->disableInstancing();
	}
}

void FabiEngine3D::model_setBright(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setBright(enabled);
}

void FabiEngine3D::model_setRotationOrder(const string& ID, DirectionOrder order)
{
	_core->_modelEntityManager.getEntity(ID)->setRotationOrder(order);
}

void FabiEngine3D::model_setStaticToCamera(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setCameraStatic(enabled);
}

void FabiEngine3D::model_setWireframed(const string& ID, const string& partID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setWireframed(partID, enabled);
}

void FabiEngine3D::model_setTransparency(const string& ID, const string& partID, float transparency)
{
	_core->_modelEntityManager.getEntity(ID)->setTransparency(partID, transparency);
}

void FabiEngine3D::model_setShadowed(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setShadowed(enabled);
}

void FabiEngine3D::model_setDepthMapIncluded(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setDepthMapIncluded(enabled);
}

void FabiEngine3D::model_setColor(const string& ID, const string& partID, Vec3 color)
{
	_core->_modelEntityManager.getEntity(ID)->setColor(partID, color);
}

void FabiEngine3D::model_setWireframeColor(const string& ID, const string& partID, Vec3 color)
{
	_core->_modelEntityManager.getEntity(ID)->setWireframeColor(partID, color);
}

void FabiEngine3D::model_setReflected(const string& ID, bool enabled)
{
	_core->_modelEntityManager.getEntity(ID)->setReflected(enabled);
}