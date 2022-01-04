#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::model_create(const string& ID, const string& meshPath)
{
	_core->_modelEntityManager.createEntity(_core->_meshLoader, ID, meshPath);
}

void FabiEngine3D::model_deleteAll()
{
	for(const auto& [key, entity] : _core->_modelEntityManager.getEntities())
	{
		model_delete(entity->getID());
	}
}

void FabiEngine3D::model_delete(const string& ID)
{
	for(const auto& aabbID : aabb_getChildIDs(ID, AabbParentEntityType::MODEL))
	{
		_core->_aabbEntityManager.deleteEntity(aabbID);
	}

	_core->_modelEntityManager.deleteEntity(ID);
}

void FabiEngine3D::model_deleteGroup(const string& ID)
{
	for(const auto& [key, entity] : _core->_modelEntityManager.getEntities())
	{
		if(entity->getID().size() >= ID.size())
		{
			auto subString = entity->getID().substr(0, ID.size());

			if(subString == ID)
			{
				model_delete(entity->getID());
			}
		}
	}
}

void FabiEngine3D::model_setVisible(const string& ID, bool value)
{
	_core->_modelEntityManager.getEntity(ID)->setVisible(value);
}

void FabiEngine3D::model_setDiffuseMap(const string& ID, const string& partID, const string& value)
{
	if(value.empty())
	{
		_core->_modelEntityManager.getEntity(ID)->setDiffuseMap(partID, 0);
		_core->_modelEntityManager.getEntity(ID)->setDiffuseMapPath(partID, "");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader.loadImage(value), true, true);
		_core->_modelEntityManager.getEntity(ID)->setDiffuseMap(partID, texture);
		_core->_modelEntityManager.getEntity(ID)->setDiffuseMapPath(partID, value);
	}
}

void FabiEngine3D::model_setEmissionMap(const string& ID, const string& partID, const string& value)
{
	if(value.empty())
	{
		_core->_modelEntityManager.getEntity(ID)->setEmissionMap(partID, 0);
		_core->_modelEntityManager.getEntity(ID)->setEmissionMapPath(partID, "");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader.loadImage(value), true, true);
		_core->_modelEntityManager.getEntity(ID)->setEmissionMap(partID, texture);
		_core->_modelEntityManager.getEntity(ID)->setEmissionMapPath(partID, value);
	}
}

void FabiEngine3D::model_setSpecularMap(const string& ID, const string& partID, const string& value)
{
	if(value.empty())
	{
		_core->_modelEntityManager.getEntity(ID)->setSpecularMap(partID, 0);
		_core->_modelEntityManager.getEntity(ID)->setSpecularMapPath(partID, "");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader.loadImage(value), true, true);
		_core->_modelEntityManager.getEntity(ID)->setSpecularMap(partID, texture);
		_core->_modelEntityManager.getEntity(ID)->setSpecularMapPath(partID, value);
	}
}

void FabiEngine3D::model_setNormalMap(const string& ID, const string& partID, const string& value)
{
	if(value.empty())
	{
		_core->_modelEntityManager.getEntity(ID)->setNormalMap(partID, 0);
		_core->_modelEntityManager.getEntity(ID)->setNormalMapPath(partID, "");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader.loadImage(value), true, true);
		_core->_modelEntityManager.getEntity(ID)->setNormalMap(partID, texture);
		_core->_modelEntityManager.getEntity(ID)->setNormalMapPath(partID, value);
	}
}

void FabiEngine3D::model_setReflectionMap(const string& ID, const string& partID, const string& value)
{
	if(value.empty())
	{
		_core->_modelEntityManager.getEntity(ID)->setReflectionMap(partID, 0);
		_core->_modelEntityManager.getEntity(ID)->setReflectionMapPath(partID, "");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader.loadImage(value), true, true);
		_core->_modelEntityManager.getEntity(ID)->setReflectionMap(partID, texture);
		_core->_modelEntityManager.getEntity(ID)->setReflectionMapPath(partID, value);
	}
}

void FabiEngine3D::model_setLevelOfDetailEntityID(const string& ID, const string& value)
{
	_core->_modelEntityManager.getEntity(ID)->setLevelOfDetailEntityID(value);
}

void FabiEngine3D::model_setFaceCulled(const string& ID, bool value)
{
	_core->_modelEntityManager.getEntity(ID)->setFaceCulled(value);
}

void FabiEngine3D::model_setReflectionType(const string& ID, const string& partID, ReflectionType value)
{
	_core->_modelEntityManager.getEntity(ID)->setReflectionType(partID, value);
}

void FabiEngine3D::model_setSpecular(const string& ID, const string& partID, bool value)
{
	_core->_modelEntityManager.getEntity(ID)->setSpecular(partID, value);
}

void FabiEngine3D::model_setReflective(const string& ID, const string& partID, bool value)
{
	_core->_modelEntityManager.getEntity(ID)->setReflective(partID, value);
}

void FabiEngine3D::model_setBasePosition(const string& ID, fvec3 value)
{
	_core->_modelEntityManager.getEntity(ID)->setBasePosition(value);
}

void FabiEngine3D::model_setBaseRotation(const string& ID, fvec3 value)
{
	_core->_modelEntityManager.getEntity(ID)->setBaseRotation(value);
}

void FabiEngine3D::model_setBaseRotationOrigin(const string& ID, fvec3 value)
{
	_core->_modelEntityManager.getEntity(ID)->setBaseRotationOrigin(value);
}

void FabiEngine3D::model_setBaseSize(const string& ID, fvec3 value)
{
	_core->_modelEntityManager.getEntity(ID)->setBaseSize(value);
}

void FabiEngine3D::model_setPartPosition(const string& ID, const string& partID, fvec3 value)
{
	_core->_modelEntityManager.getEntity(ID)->setPartPosition(partID, value);
}

void FabiEngine3D::model_setPartRotation(const string& ID, const string& partID, fvec3 value)
{
	_core->_modelEntityManager.getEntity(ID)->setPartRotation(partID, value);
}

void FabiEngine3D::model_setPartRotationOrigin(const string& ID, const string& partID, fvec3 value)
{
	_core->_modelEntityManager.getEntity(ID)->setPartRotationOrigin(partID, value);
}

void FabiEngine3D::model_setPartSize(const string& ID, const string& partID, fvec3 value)
{
	_core->_modelEntityManager.getEntity(ID)->setPartSize(partID, value);
}

void FabiEngine3D::model_moveBase(const string& ID, fvec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->moveBase(change);
}

void FabiEngine3D::model_rotateBase(const string& ID, fvec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->rotateBase(change);
}

void FabiEngine3D::model_scaleBase(const string& ID, fvec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->scaleBase(change);
}

void FabiEngine3D::model_movePart(const string& ID, const string& partID, fvec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->movePart(partID, change);
}

void FabiEngine3D::model_rotatePart(const string& ID, const string& partID, fvec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->rotatePart(partID, change);
}

void FabiEngine3D::model_scalePart(const string& ID, const string& partID, fvec3 change)
{
	_core->_modelEntityManager.getEntity(ID)->scalePart(partID, change);
}

void FabiEngine3D::model_moveBaseTo(const string& ID, fvec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->moveBaseTo(target, speed);
}

void FabiEngine3D::model_rotateBaseTo(const string& ID, fvec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->rotateBaseTo(target, speed);
}

void FabiEngine3D::model_scaleBaseTo(const string& ID, fvec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->scaleBaseTo(target, speed);
}

void FabiEngine3D::model_setSpecularShininess(const string& ID, const string& partID, float value)
{
	_core->_modelEntityManager.getEntity(ID)->setSpecularShininess(partID, value);
}

void FabiEngine3D::model_setSpecularIntensity(const string& ID, const string& partID, float value)
{
	_core->_modelEntityManager.getEntity(ID)->setSpecularIntensity(partID, value);
}

void FabiEngine3D::model_setReflectivity(const string& ID, const string& partID, float value)
{
	_core->_modelEntityManager.getEntity(ID)->setReflectivity(partID, value);
}

void FabiEngine3D::model_setLightness(const string& ID, const string& partID, float value)
{
	_core->_modelEntityManager.getEntity(ID)->setLightness(partID, value);
}

void FabiEngine3D::model_setEmissionIntensity(const string& ID, const string& partID, float value)
{
	_core->_modelEntityManager.getEntity(ID)->setEmissionIntensity(partID, value);
}

void FabiEngine3D::model_setMinHeight(const string& ID, float value)
{
	_core->_modelEntityManager.getEntity(ID)->setMinHeight(value);
}

void FabiEngine3D::model_setMaxHeight(const string& ID, float value)
{
	_core->_modelEntityManager.getEntity(ID)->setMaxHeight(value);
}

void FabiEngine3D::model_setLevelOfDetailDistance(const string& ID, float value)
{
	_core->_modelEntityManager.getEntity(ID)->setLevelOfDetailDistance(value);
}

void FabiEngine3D::model_movePartTo(const string& ID, const string& partID, fvec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->movePartTo(partID, target, speed);
}

void FabiEngine3D::model_rotatePartTo(const string& ID, const string& partID, fvec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->rotatePartTo(partID, target, speed);
}

void FabiEngine3D::model_scalePartTo(const string& ID, const string& partID, fvec3 target, float speed)
{
	_core->_modelEntityManager.getEntity(ID)->scalePartTo(partID, target, speed);
}

void FabiEngine3D::model_setLevelOfDetailSize(const string& ID, fvec3 value)
{
	_core->_modelEntityManager.getEntity(ID)->setLevelOfDetailSize(value);
}

void FabiEngine3D::model_setTextureRepeat(const string& ID, const string& partID, float value)
{
	_core->_modelEntityManager.getEntity(ID)->setTextureRepeat(partID, value);
}

void FabiEngine3D::model_setBright(const string& ID, bool value)
{
	_core->_modelEntityManager.getEntity(ID)->setBright(value);
}

void FabiEngine3D::model_setRotationOrder(const string& ID, DirectionOrder value)
{
	_core->_modelEntityManager.getEntity(ID)->setRotationOrder(value);
}

void FabiEngine3D::model_setFrozen(const string& ID, bool value)
{
	_core->_modelEntityManager.getEntity(ID)->setFrozen(value);
}

void FabiEngine3D::model_setWireframed(const string& ID, const string& partID, bool value)
{
	_core->_modelEntityManager.getEntity(ID)->setWireframed(partID, value);
}

void FabiEngine3D::model_setTransparency(const string& ID, const string& partID, float value)
{
	_core->_modelEntityManager.getEntity(ID)->setTransparency(partID, value);
}

void FabiEngine3D::model_setShadowed(const string& ID, bool value)
{
	_core->_modelEntityManager.getEntity(ID)->setShadowed(value);
}

void FabiEngine3D::model_setDepthMapIncluded(const string& ID, bool value)
{
	_core->_modelEntityManager.getEntity(ID)->setDepthMapIncluded(value);
}

void FabiEngine3D::model_setColor(const string& ID, const string& partID, fvec3 value)
{
	_core->_modelEntityManager.getEntity(ID)->setColor(partID, value);
}

void FabiEngine3D::model_setWireframeColor(const string& ID, const string& partID, fvec3 value)
{
	_core->_modelEntityManager.getEntity(ID)->setWireframeColor(partID, value);
}

void FabiEngine3D::model_setReflected(const string& ID, bool value)
{
	_core->_modelEntityManager.getEntity(ID)->setReflected(value);
}