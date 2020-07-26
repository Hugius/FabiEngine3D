#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

#include <algorithm>

void FabiEngine3D::waterEntity_add(const string& ID, float size)
{
	_core->_waterEntityManager.addWaterEntity(ID, size);
}

void FabiEngine3D::waterEntity_delete(const string& ID)
{
	// Unselect water if selected
	if (ID == waterEntity_getSelectedID())
	{
		_core->_waterEntityManager.selectWater("");
	}

	_core->_waterEntityManager.deleteEntity(ID, EntityType::WATER);
}

void FabiEngine3D::waterEntity_hide(const string& ID)
{
	_core->_waterEntityManager.getEntity(ID)->setEnabled(false);
}

void FabiEngine3D::waterEntity_show(const string& ID)
{
	_core->_waterEntityManager.getEntity(ID)->setEnabled(true);
}

bool FabiEngine3D::waterEntity_isExisting(const string& ID)
{
	return _core->_waterEntityManager.isExisting(ID);
}

void FabiEngine3D::waterEntity_select(const string& ID)
{
	_core->_waterEntityManager.selectWater(ID);
}

void FabiEngine3D::waterEntity_setPosition(const string& ID, vec3 position)
{
	_core->_waterEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::waterEntity_setUvRepeat(const string& ID, float repeat)
{
	_core->_waterEntityManager.getEntity(ID)->setUvRepeat(repeat);
}

void FabiEngine3D::waterEntity_setReflective(const string& ID, bool enabled)
{
	_core->_waterEntityManager.getEntity(ID)->setReflective(enabled);
}

void FabiEngine3D::waterEntity_setRefractive(const string& ID, bool enabled)
{
	_core->_waterEntityManager.getEntity(ID)->setRefractive(enabled);
}

void FabiEngine3D::waterEntity_setSpeed(const string& ID, float speed)
{
	_core->_waterEntityManager.getEntity(ID)->setSpeed(speed);
}

void FabiEngine3D::waterEntity_setWaving(const string& ID, const string& displacementMapPath, float heightFactor, bool enabled)
{
	if (enabled)
	{
		_core->_waterEntityManager.getEntity(ID)->setDisplacementMap(_core->_texLoader.getTexture(displacementMapPath, false, false));
		_core->_waterEntityManager.getEntity(ID)->setWaveHeightFactor(heightFactor);
	}

	_core->_waterEntityManager.getEntity(ID)->setWaving(enabled);
}

void FabiEngine3D::waterEntity_setRippling(const string& ID, const string& dudvMapPath, bool enabled)
{
	if (enabled)
	{
		_core->_waterEntityManager.getEntity(ID)->setDudvMap(_core->_texLoader.getTexture(dudvMapPath, false, false));
	}

	_core->_waterEntityManager.getEntity(ID)->setRippling(enabled);
}

void FabiEngine3D::waterEntity_setColor(const string& ID, vec3 color)
{
	_core->_waterEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::waterEntity_setSpecular(const string& ID, const string& normalMapPath, float factor, float intensity, bool enabled)
{
	if (enabled)
	{
		_core->_waterEntityManager.getEntity(ID)->setNormalMap(_core->_texLoader.getTexture(normalMapPath, false, false));
		_core->_waterEntityManager.getEntity(ID)->setSpecularLightingFactor(factor);
		_core->_waterEntityManager.getEntity(ID)->setSpecularLightingIntensity(intensity);
	}

	_core->_waterEntityManager.getEntity(ID)->setSpecular(enabled);
}

void FabiEngine3D::waterEntity_setTransparency(const string& ID, float transparency)
{
	transparency = std::clamp(transparency, 0.0f, 1.0f);
	_core->_waterEntityManager.getEntity(ID)->setTransparency(transparency * 10.0f);
}

string FabiEngine3D::waterEntity_getSelectedID()
{
	if (_core->_waterEntityManager.getSelectedWater() != nullptr)
	{
		return _core->_waterEntityManager.getSelectedWater()->getID();
	}
	else
	{
		return "";
	}
}

float FabiEngine3D::waterEntity_getSize(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getSize();
}

vec3 FabiEngine3D::waterEntity_getPosition(const string& ID)
{
	return _core->_waterEntityManager.getEntity(ID)->getPosition();
}
