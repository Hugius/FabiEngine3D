#include "engine_gui_button.hpp"

EngineGuiButton::EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor,
	string textContent, Vec3 textColor, Vec3 textHoverColor, bool sizeIncreaseEnabled, bool colorChangeEnabled) :
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_rectangle(make_shared<EngineGuiRectangle>(fe3d, parentID + "_button", ID, position, size, color)),
	_textfield(make_shared<EngineGuiTextfield>(fe3d, parentID + "_button", ID, position, 
		Vec2(size.x * 0.8f, size.y * 0.7f), textContent, textColor)),
	_hoverColor(hoverColor),
	_textHoverColor(textHoverColor),
	_sizeIncreaseEnabled(sizeIncreaseEnabled),
	_colorChangeEnabled(colorChangeEnabled)
{

}

EngineGuiButton::EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, 
	const string& texturePath, Vec3 hoverColor, bool sizeIncreaseEnabled, bool colorChangeEnabled) :
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_rectangle(make_shared<EngineGuiRectangle>(fe3d, parentID + "_button", ID, position, size, texturePath)),
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
		Vec2 mousePos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPosition()));
		Vec2 buttonPos = _fe3d.guiEntity_getPosition(_rectangle->getEntityID());
		Vec2 buttonSize = _fe3d.guiEntity_getSize(_rectangle->getEntityID());

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
						// Temporary values
						string rectangleID = _rectangle->getEntityID();

						// Slowly increase rectangle size
						if (_fe3d.guiEntity_getSize(rectangleID).x < (_rectangle->getOriginalSize() * _totalSizeIncrease).x &&
							_fe3d.guiEntity_getSize(rectangleID).y < (_rectangle->getOriginalSize() * _totalSizeIncrease).y)
						{
							// Rectangle
							_fe3d.guiEntity_setSize(rectangleID, _fe3d.guiEntity_getSize(rectangleID) * _increaseFactor);
						}

						// Slowly increase textfield size
						if (_textfield != nullptr)
						{
							string textfieldID = _textfield->getEntityID();

							if (_fe3d.textEntity_getSize(rectangleID).x < (_textfield->getOriginalSize() * _totalSizeIncrease).x &&
								_fe3d.textEntity_getSize(rectangleID).y < (_textfield->getOriginalSize() * _totalSizeIncrease).y)
							{
								_fe3d.textEntity_setSize(textfieldID, _fe3d.textEntity_getSize(textfieldID) * _increaseFactor);
							}
						}
					}

					// Update to changed color
					if (_colorChangeEnabled)
					{
						// Rectangle
						_fe3d.guiEntity_setColor(_rectangle->getEntityID(), _hoverColor);

						// Textfield
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
			// Temporary values
			string rectangleID = _rectangle->getEntityID();

			// Slowly decrease to default size
			if (_fe3d.guiEntity_getSize(rectangleID).x > _rectangle->getOriginalSize().x &&
				_fe3d.guiEntity_getSize(rectangleID).y > _rectangle->getOriginalSize().y)
			{
				// Rectangle
				_fe3d.guiEntity_setSize(rectangleID, _fe3d.guiEntity_getSize(rectangleID) * _decreaseFactor);
			}

			// Set rectangle to default color
			_fe3d.guiEntity_setColor(_rectangle->getEntityID(), _rectangle->getOriginalColor());

			// Textfield
			if (_textfield != nullptr)
			{
				string textfieldID = _textfield->getEntityID();

				// Slowly decrease to default size
				if (_fe3d.textEntity_getSize(rectangleID).x > _textfield->getOriginalSize().x &&
					_fe3d.textEntity_getSize(rectangleID).y > _textfield->getOriginalSize().y)
				{
					_fe3d.textEntity_setSize(textfieldID, _fe3d.textEntity_getSize(textfieldID) * _decreaseFactor);
				}

				// Set to default color
				_fe3d.textEntity_setColor(_textfield->getEntityID(), _textfield->getOriginalColor());
			}
		}
	}

	// Set cursor texture to pointing
	if(_isHovered)
	{
		_fe3d.guiEntity_changeTexture("@@cursor", "engine_assets\\textures\\cursor_pointing.png");
	}
}

void EngineGuiButton::show()
{
	// Rectangle
	_rectangle->show();

	// Text
	if (_textfield != nullptr)
	{
		_textfield->show();
	}
}

void EngineGuiButton::hide()
{
	// Rectangle
	_rectangle->hide();

	// Text
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
		// Rectangle
		_fe3d.guiEntity_setAlpha(_rectangle->getEntityID(), 1.0f);

		// Text
		if (_textfield != nullptr)
		{
			_fe3d.textEntity_setAlpha(_textfield->getEntityID(), 1.0f);
		}
	}
	else
	{
		// Rectangle
		_fe3d.guiEntity_setAlpha(_rectangle->getEntityID(), 0.25f);

		// Text
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