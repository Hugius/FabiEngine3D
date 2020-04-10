#include "EngineGuiButton.hpp"

EngineGuiButton::EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color, 
	string textContent, vec3 textColor, bool sizeIncreaseEnabled, bool colorChangeEnabled) :
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_rectangle(make_shared<EngineGuiRectangle>(fe3d, parentID + "_button", ID, position, size, color)),
	_textfield(make_shared<EngineGuiTextfield>(fe3d, parentID + "_button", ID, position, size * 0.8f, textContent, textColor)),
	_sizeIncreaseEnabled(sizeIncreaseEnabled),
	_colorChangeEnabled(colorChangeEnabled)
{

}

void EngineGuiButton::update(float delta, bool hoverable)
{
	_updateHovering(hoverable);
}

bool EngineGuiButton::isHovered()
{
	return _isHovered;
}

const string& EngineGuiButton::getID()
{
	return _ID;
}

const string& EngineGuiButton::getParentID()
{
	return _parentID;
}

shared_ptr<EngineGuiRectangle> EngineGuiButton::getRectangle()
{
	return _rectangle;
}

shared_ptr<EngineGuiTextfield> EngineGuiButton::getTextfield()
{
	return _textfield;
}

void EngineGuiButton::_updateHovering(bool hoverable)
{
	_isHovered = false;

	if (_fe3d.guiEntity_isVisible(_rectangle->getEntityID()))
	{
		// Convert dimensions to same space
		vec2 mousePos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getMousePos()));
		vec2 buttonPos = _fe3d.guiEntity_getPosition(_rectangle->getEntityID());
		vec2 buttonSize = _fe3d.guiEntity_getSize(_rectangle->getEntityID());

		// Check if cursor inside button
		if (mousePos.x > buttonPos.x - (buttonSize.x / 2.0f) && mousePos.x < buttonPos.x + (buttonSize.x / 2.0f)) // X axis
		{
			if (mousePos.y > buttonPos.y - (buttonSize.y / 2.0f) && mousePos.y < buttonPos.y + (buttonSize.y / 2.0f)) // Y axis
			{
				_isHovered = true;

				// Update increased size
				if (_sizeIncreaseEnabled)
				{
					_fe3d.guiEntity_setSize(_rectangle->getEntityID(), _rectangle->getOriginalSize() * 1.25f);

					_fe3d.textEntity_setSize(_textfield->getEntityID(), _textfield->getOriginalSize() * 1.25f);

				}

				// Update changed color
				if (_colorChangeEnabled)
				{
					_fe3d.guiEntity_setColor(_rectangle->getEntityID(), vec3(1.0f) - _rectangle->getOriginalColor());
					_fe3d.textEntity_setColor(_textfield->getEntityID(), vec3(1.0f) - _textfield->getOriginalColor());
				}
			}
		}
	}

	// Default properties
	if (!_isHovered || !hoverable)
	{
		// Update default size
		if (_sizeIncreaseEnabled)
		{
			_fe3d.guiEntity_setSize(_rectangle->getEntityID(), _rectangle->getOriginalSize());
			_fe3d.textEntity_setSize(_textfield->getEntityID(), _textfield->getOriginalSize());
		}

		// Update default color
		if (_colorChangeEnabled)
		{
			_fe3d.guiEntity_setColor(_rectangle->getEntityID(), _rectangle->getOriginalColor());
			_fe3d.textEntity_setColor(_textfield->getEntityID(), _textfield->getOriginalColor());
		}
	}
}