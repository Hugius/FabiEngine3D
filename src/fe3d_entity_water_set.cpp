#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::water_create(const string& ID)
{
	_core->_waterEntityManager->createEntity(ID);
}

void FabiEngine3D::water_deleteAll()
{
	for(const auto& [key, entity] : _core->_waterEntityManager->getEntities())
	{
		water_delete(entity->getID());
	}

	_core->_waterEntityManager->selectWater("");
}

void FabiEngine3D::water_delete(const string& ID)
{
	if(ID == water_getSelectedID())
	{
		_core->_waterEntityManager->selectWater("");
	}

	_core->_waterEntityManager->deleteEntity(ID);
}

void FabiEngine3D::water_setVisible(const string& ID, bool value)
{
	_core->_waterEntityManager->getEntity(ID)->setVisible(value);
}

void FabiEngine3D::water_select(const string& ID)
{
	_core->_waterEntityManager->selectWater(ID);
}

void FabiEngine3D::water_setHeight(const string& ID, float value)
{
	_core->_waterEntityManager->getEntity(ID)->setHeight(value);
}

void FabiEngine3D::water_setSize(const string& ID, float value)
{
	_core->_waterEntityManager->getEntity(ID)->setSize(value);
	_core->_waterEntityManager->loadMesh(ID);
}

void FabiEngine3D::water_setSpecular(const string& ID, bool value)
{
	_core->_waterEntityManager->getEntity(ID)->setSpecular(value);
}

void FabiEngine3D::water_setTextureRepeat(const string& ID, float value)
{
	_core->_waterEntityManager->getEntity(ID)->setTextureRepeat(value);
}

void FabiEngine3D::water_setQuality(const string& ID, WaterQuality value)
{
	_core->_waterEntityManager->getEntity(ID)->setQuality(value);
}

void FabiEngine3D::water_setReflective(const string& ID, bool value)
{
	_core->_waterEntityManager->getEntity(ID)->setReflective(value);
}

void FabiEngine3D::water_setRefractive(const string& ID, bool value)
{
	_core->_waterEntityManager->getEntity(ID)->setRefractive(value);
}

void FabiEngine3D::water_setWireframed(const string& ID, bool value)
{
	_core->_waterEntityManager->getEntity(ID)->setWireframed(value);
}

void FabiEngine3D::water_setWireframeColor(const string& ID, fvec3 value)
{
	_core->_waterEntityManager->getEntity(ID)->setWireframeColor(value);
}

void FabiEngine3D::water_setDudvMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_waterEntityManager->getEntity(ID)->setDudvMap(0);
		_core->_waterEntityManager->getEntity(ID)->setDudvMapPath("");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader->loadImage(value), true, false);
		_core->_waterEntityManager->getEntity(ID)->setDudvMap(texture);
		_core->_waterEntityManager->getEntity(ID)->setDudvMapPath(value);
	}
}

void FabiEngine3D::water_setNormalMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_waterEntityManager->getEntity(ID)->setNormalMap(0);
		_core->_waterEntityManager->getEntity(ID)->setNormalMapPath("");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader->loadImage(value), true, false);
		_core->_waterEntityManager->getEntity(ID)->setNormalMap(texture);
		_core->_waterEntityManager->getEntity(ID)->setNormalMapPath(value);
	}
}

void FabiEngine3D::water_setDisplacementMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_waterEntityManager->getEntity(ID)->setDisplacementMap(0);
		_core->_waterEntityManager->getEntity(ID)->setDisplacementMapPath("");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader->loadImage(value), true, false);
		_core->_waterEntityManager->getEntity(ID)->setDisplacementMap(texture);
		_core->_waterEntityManager->getEntity(ID)->setDisplacementMapPath(value);
	}
}

void FabiEngine3D::water_setWaveHeight(const string& ID, float value)
{
	_core->_waterEntityManager->getEntity(ID)->setWaveHeight(value);
}

void FabiEngine3D::water_setSpecularShininess(const string& ID, float value)
{
	_core->_waterEntityManager->getEntity(ID)->setSpecularShininess(value);
}

void FabiEngine3D::water_setSpecularIntensity(const string& ID, float value)
{
	_core->_waterEntityManager->getEntity(ID)->setSpecularIntensity(value);
}

void FabiEngine3D::water_setSpeed(const string& ID, fvec2 value)
{
	_core->_waterEntityManager->getEntity(ID)->setSpeed(value);
}

void FabiEngine3D::water_setColor(const string& ID, fvec3 value)
{
	_core->_waterEntityManager->getEntity(ID)->setColor(value);
}

void FabiEngine3D::water_setTransparency(const string& ID, float value)
{
	_core->_waterEntityManager->getEntity(ID)->setTransparency(value);
}