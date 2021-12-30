#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::text_deleteAll()
{
	_core->_textEntityManager.deleteEntities();
}

void FabiEngine3D::text_create(const string& ID, bool isCentered)
{
	_core->_textEntityManager.createEntity(ID, isCentered);
}

void FabiEngine3D::text_delete(const string& ID)
{
	_core->_textEntityManager.deleteEntity(ID);
}

void FabiEngine3D::text_setVisible(const string& ID, bool value)
{
	_core->_textEntityManager.getEntity(ID)->setVisible(value);
}

void FabiEngine3D::text_setFontMap(const string& ID, const string& value)
{
	auto entity = _core->_textEntityManager.getEntity(ID);

	entity->setFontMap(_core->_textureLoader.load2dTexture(value, true, false));
	entity->setFontMapPath(value);
}

void FabiEngine3D::text_setContent(const string& ID, const string& value, float charWidth, float charHeight)
{
	auto entity = _core->_textEntityManager.getEntity(ID);

	auto fontMapPath = entity->getFontMapPath();
	if(fontMapPath.empty())
	{
		Logger::throwWarning("Tried to set text content of text with ID \"" + ID + "\": no font loaded!");
		return;
	}

	entity->setContent(value);

	fvec2 newSize = entity->getSize();
	if(charWidth >= 0.0f)
	{
		newSize.x = (charWidth * static_cast<float>(value.size()));
	}
	if(charHeight >= 0.0f)
	{
		newSize.y = charHeight;
	}
	entity->setSize(newSize);
}

void FabiEngine3D::text_setColor(const string& ID, fvec3 value)
{
	_core->_textEntityManager.getEntity(ID)->setColor(value);
}

void FabiEngine3D::text_setTransparency(const string& ID, float value)
{
	_core->_textEntityManager.getEntity(ID)->setTransparency(value);
}

void FabiEngine3D::text_setPosition(const string& ID, fvec2 value)
{
	_core->_textEntityManager.getEntity(ID)->setPosition(value);
}

void FabiEngine3D::text_setRotation(const string& ID, float value)
{
	_core->_textEntityManager.getEntity(ID)->setRotation(value);
}

void FabiEngine3D::text_setSize(const string& ID, fvec2 value)
{
	_core->_textEntityManager.getEntity(ID)->setSize(value);
}

void FabiEngine3D::text_move(const string& ID, fvec2 position)
{
	_core->_textEntityManager.getEntity(ID)->move(position);
}

void FabiEngine3D::text_rotate(const string& ID, float rotation)
{
	_core->_textEntityManager.getEntity(ID)->rotate(rotation);
}

void FabiEngine3D::text_scale(const string& ID, fvec2 size)
{
	_core->_textEntityManager.getEntity(ID)->scale(size);
}

void FabiEngine3D::text_moveTo(const string& ID, fvec2 target, float speed)
{
	_core->_textEntityManager.getEntity(ID)->moveTo(target, speed);
}

void FabiEngine3D::text_rotateTo(const string& ID, float target, float speed)
{
	_core->_textEntityManager.getEntity(ID)->rotateTo(target, speed);
}

void FabiEngine3D::text_scaleTo(const string& ID, fvec2 target, float speed)
{
	_core->_textEntityManager.getEntity(ID)->scaleTo(target, speed);
}

void FabiEngine3D::text_setMirroredHorizontally(const string& ID, bool value)
{
	_core->_textEntityManager.getEntity(ID)->setMirroredHorizontally(value);
}

void FabiEngine3D::text_setMirroredVertically(const string& ID, bool value)
{
	_core->_textEntityManager.getEntity(ID)->setMirroredVertically(value);
}

void FabiEngine3D::text_setWireframed(const string& ID, bool value)
{
	_core->_textEntityManager.getEntity(ID)->setWireframed(value);
}

void FabiEngine3D::text_setWireframeColor(const string& ID, fvec3 value)
{
	_core->_textEntityManager.getEntity(ID)->setWireframeColor(value);
}

void FabiEngine3D::text_setMinPosition(const string& ID, fvec2 value)
{
	_core->_textEntityManager.getEntity(ID)->setMinPosition(value);
}

void FabiEngine3D::text_setMaxPosition(const string& ID, fvec2 value)
{
	_core->_textEntityManager.getEntity(ID)->setMaxPosition(value);
}