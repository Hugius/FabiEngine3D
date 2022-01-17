#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::text_deleteAll()
{
	_core->getText2dEntityManager()->deleteEntities();
}

void EngineInterface::text_create(const string& ID, bool isCentered)
{
	_core->getText2dEntityManager()->createEntity(ID, isCentered);
}

void EngineInterface::text_delete(const string& ID)
{
	_core->getText2dEntityManager()->deleteEntity(ID);
}

void EngineInterface::text_setVisible(const string& ID, bool value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setVisible(value);
}

void EngineInterface::text_setFontMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getText2dEntityManager()->getEntity(ID)->setFontMap(nullptr);
		_core->getText2dEntityManager()->getEntity(ID)->setFontMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			texture = make_shared<TextureBuffer>(_core->getImageLoader()->loadImage(value));

			_core->getTextureBufferCache()->store2dBuffer(value, texture);
		}

		_core->getText2dEntityManager()->getEntity(ID)->setFontMap(_core->getTextureBufferCache()->get2dBuffer(value));
		_core->getText2dEntityManager()->getEntity(ID)->setFontMapPath(value);
	}
}

void EngineInterface::text_setContent(const string& ID, const string& value, float charWidth, float charHeight)
{
	auto entity = _core->getText2dEntityManager()->getEntity(ID);

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

void EngineInterface::text_setColor(const string& ID, fvec3 value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setColor(value);
}

void EngineInterface::text_setTransparency(const string& ID, float value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setTransparency(value);
}

void EngineInterface::text_setPosition(const string& ID, fvec2 value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setPosition(value);
}

void EngineInterface::text_setRotation(const string& ID, float value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setRotation(value);
}

void EngineInterface::text_setSize(const string& ID, fvec2 value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setSize(value);
}

void EngineInterface::text_move(const string& ID, fvec2 position)
{
	_core->getText2dEntityManager()->getEntity(ID)->move(position);
}

void EngineInterface::text_rotate(const string& ID, float rotation)
{
	_core->getText2dEntityManager()->getEntity(ID)->rotate(rotation);
}

void EngineInterface::text_scale(const string& ID, fvec2 size)
{
	_core->getText2dEntityManager()->getEntity(ID)->scale(size);
}

void EngineInterface::text_moveTo(const string& ID, fvec2 target, float speed)
{
	_core->getText2dEntityManager()->getEntity(ID)->moveTo(target, speed);
}

void EngineInterface::text_rotateTo(const string& ID, float target, float speed)
{
	_core->getText2dEntityManager()->getEntity(ID)->rotateTo(target, speed);
}

void EngineInterface::text_scaleTo(const string& ID, fvec2 target, float speed)
{
	_core->getText2dEntityManager()->getEntity(ID)->scaleTo(target, speed);
}

void EngineInterface::text_setHorizontallyMirrored(const string& ID, bool value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setHorizontallyMirrored(value);
}

void EngineInterface::text_setVerticallyMirrored(const string& ID, bool value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setVerticallyMirrored(value);
}

void EngineInterface::text_setWireframed(const string& ID, bool value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setWireframed(value);
}

void EngineInterface::text_setWireframeColor(const string& ID, fvec3 value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setWireframeColor(value);
}

void EngineInterface::text_setMinPosition(const string& ID, fvec2 value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setMinPosition(value);
}

void EngineInterface::text_setMaxPosition(const string& ID, fvec2 value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setMaxPosition(value);
}