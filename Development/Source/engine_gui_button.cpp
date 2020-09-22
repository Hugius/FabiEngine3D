#include "engine_gui_button.hpp"

EngineGuiButton::EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color, vec3 hoverColor,
	string textContent, vec3 textColor, vec3 textHoverColor, bool sizeIncreaseEnabled, bool colorChangeEnabled) :
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_rectangle(make_shared<EngineGuiRectangle>(fe3d, parentID + "_button", ID, position, size, color)),
	_textfield(make_shared<EngineGuiTextfield>(fe3d, parentID + "_button", ID, position, vec2(size.x * 0.8f, size.y * 0.7f), textContent, textColor)),
	_hoverColor(hoverColor),
	_textHoverColor(textHoverColor),
	_sizeIncreaseEnabled(sizeIncreaseEnabled),
	_colorChangeEnabled(colorChangeEnabled)
{

}

EngineGuiButton::EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, 
	const string& textureName, vec3 hoverColor, bool sizeIncreaseEnabled, bool colorChangeEnabled) :
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_rectangle(make_shared<EngineGuiRectangle>(fe3d, parentID + "_button", ID, position, size, textureName)),
	_hoverColor(hoverColor),
	_sizeIncreaseEnabled(sizeIncreaseEnabled),
	_colorChangeEnabled(colorChangeEnabled)
{

}

void EngineGuiButton::update(bool hoverable)
{
	_updateHovering(hoverable);
}

void EngineGuiButton::_updateHovering(bool hoverable)
{
	_isHovered = false;

	// Check if button is visible anyway
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
				// Check if button is hoverable
				if (hoverable && _isHoverable)
				{
					_isHovered = true;

					// Update increased size
					if (_sizeIncreaseEnabled)
					{
						string entityID = _rectangle->getEntityID();

						// Slowly increase rectangle size
						if (_fe3d.guiEntity_getSize(entityID).x < (_rectangle->getOriginalSize() * _totalSizeIncrease).x &&
							_fe3d.guiEntity_getSize(entityID).y < (_rectangle->getOriginalSize() * _totalSizeIncrease).y)
						{
							_fe3d.guiEntity_setSize(entityID, _fe3d.guiEntity_getSize(entityID) * _increaseFactor);
						}

						// Slowly increase textfield size
						if (_textfield != nullptr)
						{
							string textfieldID = _textfield->getEntityID();

							if (_fe3d.textEntity_getSize(entityID).x < (_textfield->getOriginalSize() * _totalSizeIncrease).x &&
								_fe3d.textEntity_getSize(entityID).y < (_textfield->getOriginalSize() * _totalSizeIncrease).y)
							{
								_fe3d.textEntity_setSize(textfieldID, _fe3d.textEntity_getSize(textfieldID) * _increaseFactor);
							}
						}
					}

					// Update to changed color
					if (_colorChangeEnabled)
					{
						_fe3d.guiEntity_setColor(_rectangle->getEntityID(), _hoverColor);

						if (_textfield != nullptr)
						{
							_fe3d.textEntity_setColor(_textfield->getEntityID(), _textHoverColor);
						}
					}
				}
			}
		}

		// Default properties
		if (!_isHovered)
		{
			string entityID = _rectangle->getEntityID();

			// Slowly decrease to default size
			if (_fe3d.guiEntity_getSize(entityID).x > _rectangle->getOriginalSize().x &&
				_fe3d.guiEntity_getSize(entityID).y > _rectangle->getOriginalSize().y)
			{
				_fe3d.guiEntity_setSize(entityID, _fe3d.guiEntity_getSize(entityID) * _decreaseFactor);
			}

			// Set to default color
			_fe3d.guiEntity_setColor(_rectangle->getEntityID(), _rectangle->getOriginalColor());

			// Textfield
			if (_textfield != nullptr)
			{
				string textfieldID = _textfield->getEntityID();

				// Slowly decrease to default size
				if (_fe3d.textEntity_getSize(entityID).x > _textfield->getOriginalSize().x &&
					_fe3d.textEntity_getSize(entityID).y > _textfield->getOriginalSize().y)
				{
					_fe3d.textEntity_setSize(textfieldID, _fe3d.textEntity_getSize(textfieldID) * _decreaseFactor);
				}

				// Set to default color
				_fe3d.textEntity_setColor(_textfield->getEntityID(), _textfield->getOriginalColor());
			}
		}
	}

	// Update cursor texture
	if(_isHovered)
	{
		// Set cursor texture to pointing
		_fe3d.guiEntity_changeTexture("@@cursor", "engine\\textures\\cursor_pointing.png");
	}
}

void EngineGuiButton::show()
{
	_rectangle->show();

	if (_textfield != nullptr)
	{
		_textfield->show();
	}
}

void EngineGuiButton::hide()
{
	_rectangle->hide();

	if (_textfield != nullptr)
	{
		_textfield->hide();
	}
}

void EngineGuiButton::setHoverable(bool hoverable)
{
	_isHoverable = hoverable;

	if (hoverable)
	{
		_fe3d.guiEntity_setAlpha(_rectangle->getEntityID(), 1.0f);

		if (_textfield != nullptr)
		{
			_fe3d.textEntity_setAlpha(_textfield->getEntityID(), 1.0f);
		}
	}
	else
	{
		_fe3d.guiEntity_setAlpha(_rectangle->getEntityID(), 0.25f);

		if (_textfield != nullptr)
		{
			_fe3d.textEntity_setAlpha(_textfield->getEntityID(), 0.25f);
		}
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

shared_ptr<EngineGuiRectangle> EngineGuiButton::getRectangle()
{
	return _rectangle;
}

shared_ptr<EngineGuiTextfield> EngineGuiButton::getTextfield()
{
	return _textfield;
}