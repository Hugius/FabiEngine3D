#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::textEntity_deleteAll()
{
	_core->_textEntityManager.deleteEntities();
}

void FabiEngine3D::textEntity_hideAll()
{
	for (auto& entity : _core->_textEntityManager.getEntities())
	{
		entity->setEnabled(false);
	}
}

void FabiEngine3D::textEntity_showAll()
{
	for (auto& entity : _core->_textEntityManager.getEntities())
	{
		entity->setEnabled(true);
	}
}

void FabiEngine3D::textEntity_add(const string& ID, const string& text, const string& fontPath, vec3 color, vec2 position, float rotation, vec2 size, bool centered)
{
	_core->_textEntityManager.addTextEntity(ID, text, fontPath, color, position, rotation, size, false, centered);
}

void FabiEngine3D::textEntity_delete(const string& ID)
{
	_core->_textEntityManager.deleteEntity(ID, EntityType::TEXT);
}

bool FabiEngine3D::textEntity_isExisting(const string& ID)
{
	return _core->_textEntityManager.isExisting(ID);
}

void FabiEngine3D::textEntity_setTextContent(const string& ID, const string& textContent, float charWidth)
{
	auto entity = _core->_textEntityManager.getEntity(ID);

	entity->setTextContent(textContent);
	entity->setDiffuseMap(_core->_texLoader.getText(textContent, entity->getFontPath()));

	if (charWidth != -1.0f)
	{
		entity->setScaling(vec2(charWidth * float(textContent.size()), entity->getScaling().y));
	}
}

void FabiEngine3D::textEntity_setColor(const string& ID, vec3 color)
{
	_core->_textEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::textEntity_setAlpha(const string& ID, float alpha)
{
	_core->_textEntityManager.getEntity(ID)->setAlpha(alpha);
}

void FabiEngine3D::textEntity_hide(const string& ID)
{
	_core->_textEntityManager.getEntity(ID)->setEnabled(false);
}

void FabiEngine3D::textEntity_show(const string& ID)
{
	_core->_textEntityManager.getEntity(ID)->setEnabled(true);
}

void FabiEngine3D::textEntity_setPosition(const string& ID, vec2 position)
{
	_core->_textEntityManager.getEntity(ID)->setTranslation(position);
}

void FabiEngine3D::textEntity_setRotation(const string& ID, float rotation)
{
	_core->_textEntityManager.getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::textEntity_setSize(const string& ID, vec2 size)
{
	_core->_textEntityManager.getEntity(ID)->setScaling(size);
}

void FabiEngine3D::textEntity_move(const string& ID, vec2 position)
{
	_core->_textEntityManager.getEntity(ID)->translate(position);
}

void FabiEngine3D::textEntity_rotate(const string& ID, float rotation)
{
	_core->_textEntityManager.getEntity(ID)->rotate(rotation);
}

void FabiEngine3D::textEntity_scale(const string& ID, vec2 size)
{
	_core->_textEntityManager.getEntity(ID)->scale(size);
}

void FabiEngine3D::textEntity_setMinPosition(const string& ID, vec2 minPos)
{
	_core->_textEntityManager.getEntity(ID)->setMinPosition(minPos);
}

void FabiEngine3D::textEntity_setMaxPosition(const string& ID, vec2 maxPos)
{
	_core->_textEntityManager.getEntity(ID)->setMaxPosition(maxPos);
}

vec2 FabiEngine3D::textEntity_getPosition(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getTranslation();
}

float FabiEngine3D::textEntity_getRotation(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getRotation();
}

vec2 FabiEngine3D::textEntity_getSize(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getScaling();
}

string FabiEngine3D::textEntity_getTextContent(const string& ID)
{
	return _core->_textEntityManager.getEntity(ID)->getTextContent();
}