#include "engine_gui_button.hpp"
#include "tools.hpp"

EngineGuiButton::EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, string textContent, Vec3 textColor, Vec3 textHoverColor, bool sizeChangeEnabled, bool colorChangeEnabled)
	:
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_rectangle(make_shared<EngineGuiRectangle>(fe3d, parentID + "_button", ID, position, size, color)),
	_textField(make_shared<EngineGuiTextField>(fe3d, parentID + "_button", ID, position,
			   Vec2(size.x* TEXT_WIDTH_MULTIPLIER, size.y* TEXT_HEIGHT_MULTIPLIER), textContent, textColor)),
	_hoverColor(hoverColor),
	_textHoverColor(textHoverColor),
	_sizeChangeEnabled(sizeChangeEnabled),
	_colorChangeEnabled(colorChangeEnabled)
{

}

EngineGuiButton::EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, const string& texturePath, Vec3 hoverColor, bool sizeIncreaseEnabled, bool colorChangeEnabled)
	:
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_rectangle(make_shared<EngineGuiRectangle>(fe3d, parentID + "_button", ID, position, size, texturePath)),
	_hoverColor(hoverColor),
	_sizeChangeEnabled(sizeIncreaseEnabled),
	_colorChangeEnabled(colorChangeEnabled)
{

}

void EngineGuiButton::update(bool isHoverable)
{
	_updateHovering(isHoverable);
}

void EngineGuiButton::setVisible(bool isVisible)
{
	// Rectangle
	_rectangle->setVisible(isVisible);

	// Text
	if(_textField != nullptr)
	{
		_textField->setVisible(isVisible);
	}
}

void EngineGuiButton::_updateHovering(bool isHoverable)
{
	_isHovered = false;

	// Check if button is visible anyway
	if(_fe3d.imageEntity_isVisible(_rectangle->getEntityID()))
	{
		// Convert dimensions to same space
		Vec2 cursorPosition = Math::convertToNDC(Tools::convertFromScreenCoords(_fe3d.misc_getCursorPosition()));
		Vec2 buttonPosition = _fe3d.imageEntity_getPosition(_rectangle->getEntityID());
		Vec2 buttonSize = _fe3d.imageEntity_getSize(_rectangle->getEntityID());

		// Check if cursor inside button
		if(cursorPosition.x > buttonPosition.x - (buttonSize.x / 2.0f) && cursorPosition.x < buttonPosition.x + (buttonSize.x / 2.0f)) // X axis
		{
			if(cursorPosition.y > buttonPosition.y - (buttonSize.y / 2.0f) && cursorPosition.y < buttonPosition.y + (buttonSize.y / 2.0f)) // Y axis
			{
				// Check if button is hoverable
				if(isHoverable && _isHoverable)
				{
					_isHovered = true;

					// Update increased size
					if(_sizeChangeEnabled)
					{
						// Temporary values
						string rectangleID = _rectangle->getEntityID();

						// Slowly increase rectangle size
						if(_fe3d.imageEntity_getSize(rectangleID).x < (_rectangle->getOriginalSize() * TOTAL_SIZE_INCREASE).x &&
						   _fe3d.imageEntity_getSize(rectangleID).y < (_rectangle->getOriginalSize() * TOTAL_SIZE_INCREASE).y)
						{
							// Rectangle
							_fe3d.imageEntity_setSize(rectangleID, _fe3d.imageEntity_getSize(rectangleID) * INCREASE_MULTIPLIER);
						}

						// Slowly increase TextField size
						if(_textField != nullptr)
						{
							string TextFieldID = _textField->getEntityID();

							if(_fe3d.textEntity_getSize(rectangleID).x < (_textField->getOriginalSize() * TOTAL_SIZE_INCREASE).x &&
							   _fe3d.textEntity_getSize(rectangleID).y < (_textField->getOriginalSize() * TOTAL_SIZE_INCREASE).y)
							{
								_fe3d.textEntity_setSize(TextFieldID, _fe3d.textEntity_getSize(TextFieldID) * INCREASE_MULTIPLIER);
							}
						}
					}

					// Update to changed color
					if(_colorChangeEnabled)
					{
						// Rectangle
						_fe3d.imageEntity_setColor(_rectangle->getEntityID(), _hoverColor);

						// TextField
						if(_textField != nullptr)
						{
							_fe3d.textEntity_setColor(_textField->getEntityID(), _textHoverColor);
						}
					}
				}
			}
		}

		// Default properties
		if(!_isHovered)
		{
			// Temporary values
			string rectangleID = _rectangle->getEntityID();

			// Slowly decrease to default size
			if(_fe3d.imageEntity_getSize(rectangleID).x > _rectangle->getOriginalSize().x &&
			   _fe3d.imageEntity_getSize(rectangleID).y > _rectangle->getOriginalSize().y)
			{
				// Rectangle
				_fe3d.imageEntity_setSize(rectangleID, _fe3d.imageEntity_getSize(rectangleID) * DECREASE_MULTIPLIER);
			}

			// Set rectangle to default color
			_fe3d.imageEntity_setColor(_rectangle->getEntityID(), _rectangle->getOriginalColor());

			// TextField
			if(_textField != nullptr)
			{
				string TextFieldID = _textField->getEntityID();

				// Slowly decrease to default size
				if(_fe3d.textEntity_getSize(rectangleID).x > _textField->getOriginalSize().x &&
				   _fe3d.textEntity_getSize(rectangleID).y > _textField->getOriginalSize().y)
				{
					_fe3d.textEntity_setSize(TextFieldID, _fe3d.textEntity_getSize(TextFieldID) * DECREASE_MULTIPLIER);
				}

				// Set to default color
				_fe3d.textEntity_setColor(_textField->getEntityID(), _textField->getOriginalColor());
			}
		}
	}

	// Set cursor texture to pointing
	if(_isHovered)
	{
		_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_pointing.png");
	}
}

void EngineGuiButton::setHoverable(bool isHoverable)
{
	_isHoverable = isHoverable;

	if(isHoverable)
	{
		// Rectangle
		_fe3d.imageEntity_setAlpha(_rectangle->getEntityID(), 1.0f);

		// Text
		if(_textField != nullptr)
		{
			_fe3d.textEntity_setAlpha(_textField->getEntityID(), 1.0f);
		}
	}
	else
	{
		// Rectangle
		_fe3d.imageEntity_setAlpha(_rectangle->getEntityID(), 0.25f);

		// Text
		if(_textField != nullptr)
		{
			_fe3d.textEntity_setAlpha(_textField->getEntityID(), 0.25f);
		}
	}
}

void EngineGuiButton::changeTextContent(const string& content)
{
	auto textEntityID = getTextField()->getEntityID();

	// Check if text content changed
	if(content != _fe3d.textEntity_getTextContent(textEntityID))
	{
		// Update TextField
		auto charWidth = (getTextField()->getOriginalSize().x / static_cast<float>(_fe3d.textEntity_getTextContent(textEntityID).size()));
		auto charHeight = getTextField()->getOriginalSize().y;
		_fe3d.textEntity_setTextContent(textEntityID, content, charWidth, charHeight);
		getTextField()->updateOriginalSize();

		// Update rectangle
		auto newRectangleSize = Vec2(getTextField()->getOriginalSize() / Vec2(TEXT_WIDTH_MULTIPLIER, TEXT_HEIGHT_MULTIPLIER));
		_fe3d.imageEntity_setSize(getRectangle()->getEntityID(), newRectangleSize);
		getRectangle()->updateOriginalSize();
	}
}

const bool EngineGuiButton::isHoverable() const
{
	return _isHoverable;
}

const bool EngineGuiButton::isHovered() const
{
	return _isHovered;
}

const string& EngineGuiButton::getID() const
{
	return _ID;
}

const string& EngineGuiButton::getParentID() const
{
	return _parentID;
}

shared_ptr<EngineGuiRectangle> EngineGuiButton::getRectangle() const
{
	return _rectangle;
}

shared_ptr<EngineGuiTextField> EngineGuiButton::getTextField() const
{
	return _textField;
}