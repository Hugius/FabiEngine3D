#include "EngineGuiButton.hpp"

EngineGuiButton::EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color, string textContent, vec3 textColor) :
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_rectangle(fe3d, parentID, ID, position, size, color),
	_textfield(fe3d, parentID, ID, position + (size * 0.1f), size * 0.8f, textContent, textColor)
{

}

void EngineGuiButton::update()
{
	_isHovered = false;

	if (_fe3d.guiEntity_isVisible(_rectangle.getEntityID()))
	{
		// Convert dimensions to same space
		vec2 mousePos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getMousePos()));
		vec2 buttonPos = _fe3d.guiEntity_getPosition(_rectangle.getEntityID());
		vec2 buttonSize = _fe3d.guiEntity_getSize(_rectangle.getEntityID());

		// Check if cursor inside button
		if (mousePos.x > buttonPos.x && mousePos.x < buttonPos.x + buttonSize.x) // X axis
		{
			if (mousePos.y > buttonPos.y && mousePos.y < buttonPos.y + buttonSize.y) // Y axis
			{
				_isHovered = true;

				// Update increased size
				_fe3d.guiEntity_setPosition(_rectangle.getEntityID(), _rectangle.getOriginalPosition() - (_rectangle.getOriginalSize() * 0.125f));
				_fe3d.guiEntity_setSize(_rectangle.getEntityID(), _rectangle.getOriginalSize() * 1.25f);
				_fe3d.guiEntity_setColor(_rectangle.getEntityID(), vec3(1.0f) - _rectangle.getOriginalColor());
				_fe3d.textEntity_setPosition(_textfield.getEntityID(), _textfield.getOriginalPosition() - (_rectangle.getOriginalSize() * 0.125f));
				_fe3d.textEntity_setSize(_textfield.getEntityID(), _textfield.getOriginalSize() * 1.25f);
				_fe3d.textEntity_setColor(_textfield.getEntityID(), vec3(1.0f) - _textfield.getOriginalColor());
			}
		}
	}

	// Update default size
	if (!_isHovered)
	{
		_fe3d.guiEntity_setPosition(_rectangle.getEntityID(), _rectangle.getOriginalPosition());
		_fe3d.guiEntity_setSize(_rectangle.getEntityID(), _rectangle.getOriginalSize());
		_fe3d.guiEntity_setColor(_rectangle.getEntityID(), _rectangle.getOriginalColor());
		_fe3d.textEntity_setPosition(_textfield.getEntityID(), _textfield.getOriginalPosition());
		_fe3d.textEntity_setSize(_textfield.getEntityID(), _textfield.getOriginalSize());
		_fe3d.textEntity_setColor(_textfield.getEntityID(), _textfield.getOriginalColor());
	}
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

EngineGuiRectangle& EngineGuiButton::getRectangle()
{
	return _rectangle;
}

EngineGuiTextfield& EngineGuiButton::getText()
{
	return _textfield;
}