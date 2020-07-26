#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::guiEntity_deleteAll()
{
	_core->_guiEntityManager.deleteEntities();
}

void FabiEngine3D::guiEntity_hideAll()
{
	for (auto& entity : _core->_guiEntityManager.getEntities())
	{
		entity->setVisible(false);
	}
}

void FabiEngine3D::guiEntity_showAll()
{
	for (auto& entity : _core->_guiEntityManager.getEntities())
	{
		entity->setVisible(true);
	}
}

void FabiEngine3D::guiEntity_add(const string& ID, const string& texturePath, vec2 translation, float rotation, vec2 scaling, bool centered, bool visible)
{
	_core->_guiEntityManager.addGuiEntity(ID, texturePath, translation, rotation, scaling, false, centered);
	_core->_guiEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::guiEntity_add(const string& ID, vec3 color, vec2 translation, float rotation, vec2 scaling, bool centered, bool visible)
{
	_core->_guiEntityManager.addGuiEntity(ID, color, translation, rotation, scaling, centered);
	_core->_guiEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::guiEntity_hide(const string& ID)
{
	_core->_guiEntityManager.getEntity(ID)->setVisible(false);
}

void FabiEngine3D::guiEntity_show(const string& ID)
{
	_core->_guiEntityManager.getEntity(ID)->setVisible(true);
}

void FabiEngine3D::guiEntity_delete(const string& ID)
{
	_core->_guiEntityManager.deleteEntity(ID, EntityType::GUI);
}

void FabiEngine3D::guiEntity_changeTexture(const string& ID, const string& texturePath)
{
	_core->_guiEntityManager.getEntity(ID)->setDiffuseMap(_core->_texLoader.getTexture(texturePath, true, true));
}

bool FabiEngine3D::guiEntity_isExisting(const string& ID)
{
	return _core->_guiEntityManager.isExisting(ID);
}

void FabiEngine3D::guiEntity_setPosition(const string& ID, vec2 position)
{
	_core->_guiEntityManager.getEntity(ID)->setTranslation(position);
}

void FabiEngine3D::guiEntity_setRotation(const string& ID, float rotation)
{
	_core->_guiEntityManager.getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::guiEntity_setSize(const string& ID, vec2 size)
{
	_core->_guiEntityManager.getEntity(ID)->setScaling(size);
}

void FabiEngine3D::guiEntity_move(const string& ID, vec2 position)
{
	_core->_guiEntityManager.getEntity(ID)->translate(position);
}

void FabiEngine3D::guiEntity_rotate(const string& ID, float rotation)
{
	_core->_guiEntityManager.getEntity(ID)->rotate(rotation);
}

void FabiEngine3D::guiEntity_scale(const string& ID, vec2 size)
{
	_core->_guiEntityManager.getEntity(ID)->scale(size);
}

void FabiEngine3D::guiEntity_setColor(const string& ID, vec3 color)
{
	_core->_guiEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::guiEntity_setAlpha(const string& ID, float alpha)
{
	_core->_guiEntityManager.getEntity(ID)->setAlpha(alpha);
}

void FabiEngine3D::guiEntity_setMinPosition(const string& ID, vec2 minPos)
{
	_core->_guiEntityManager.getEntity(ID)->setMinPosition(minPos);
}

void FabiEngine3D::guiEntity_setMaxPosition(const string& ID, vec2 maxPos)
{
	_core->_guiEntityManager.getEntity(ID)->setMaxPosition(maxPos);
}

vec2 FabiEngine3D::guiEntity_getPosition(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getTranslation();
}

float FabiEngine3D::guiEntity_getRotation(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getRotation();
}

vec2 FabiEngine3D::guiEntity_getSize(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getScaling();
}

bool FabiEngine3D::guiEntity_isVisible(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->isVisible();
}