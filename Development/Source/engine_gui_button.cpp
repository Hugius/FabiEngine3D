#include "engine_gui_button.hpp"

EngineGuiButton::EngineGuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, string textContent, Vec3 textColor, Vec3 textHoverColor, bool sizeChangeEnabled, bool colorChangeEnabled)
	:
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_rectangle(make_shared<EngineGuiRectangle>(fe3d, parentID + "_button", ID, position, size, color)),
	_textfield(make_shared<EngineGuiTextfield>(fe3d, parentID + "_button", ID, position, 
		Vec2(size.x * TEXT_WIDTH_MULTIPLIER, size.y * TEXT_HEIGHT_MULTIPLIER), textContent, textColor)),
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
	if (_textfield != nullptr)
	{
		_textfield->setVisible(isVisible);
	}
}

void EngineGuiButton::_updateHovering(bool isHoverable)
{
	_isHovered = false;

	// Check if button is visible anyway
	if (_fe3d.imageEntity_isVisible(_rectangle->getEntityID()))
	{
		// Convert dimensions to same space
		Vec2 mousePos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPosition()));
		Vec2 buttonPos = _fe3d.imageEntity_getPosition(_rectangle->getEntityID());
		Vec2 buttonSize = _fe3d.imageEntity_getSize(_rectangle->getEntityID());

		// Check if cursor inside button
		if (mousePos.x > buttonPos.x - (buttonSize.x / 2.0f) && mousePos.x < buttonPos.x + (buttonSize.x / 2.0f)) // X axis
		{
			if (mousePos.y > buttonPos.y - (buttonSize.y / 2.0f) && mousePos.y < buttonPos.y + (buttonSize.y / 2.0f)) // Y axis
			{
				// Check if button is hoverable
				if (isHoverable && _isHoverable)
				{
					_isHovered = true;

					// Update increased size
					if (_sizeChangeEnabled)
					{
						// Temporary values
						string rectangleID = _rectangle->getEntityID();

						// Slowly increase rectangle size
						if (_fe3d.imageEntity_getSize(rectangleID).x < (_rectangle->getOriginalSize() * TOTAL_SIZE_INCREASE).x &&
							_fe3d.imageEntity_getSize(rectangleID).y < (_rectangle->getOriginalSize() * TOTAL_SIZE_INCREASE).y)
						{
							// Rectangle
							_fe3d.imageEntity_setSize(rectangleID, _fe3d.imageEntity_getSize(rectangleID) * INCREASE_FACTOR);
						}

						// Slowly increase textfield size
						if (_textfield != nullptr)
						{
							string textfieldID = _textfield->getEntityID();

							if (_fe3d.textEntity_getSize(rectangleID).x < (_textfield->getOriginalSize() * TOTAL_SIZE_INCREASE).x &&
								_fe3d.textEntity_getSize(rectangleID).y < (_textfield->getOriginalSize() * TOTAL_SIZE_INCREASE).y)
							{
								_fe3d.textEntity_setSize(textfieldID, _fe3d.textEntity_getSize(textfieldID) * INCREASE_FACTOR);
							}
						}
					}

					// Update to changed color
					if (_colorChangeEnabled)
					{
						// Rectangle
						_fe3d.imageEntity_setColor(_rectangle->getEntityID(), _hoverColor);

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
			if (_fe3d.imageEntity_getSize(rectangleID).x > _rectangle->getOriginalSize().x &&
				_fe3d.imageEntity_getSize(rectangleID).y > _rectangle->getOriginalSize().y)
			{
				// Rectangle
				_fe3d.imageEntity_setSize(rectangleID, _fe3d.imageEntity_getSize(rectangleID) * DECREASE_FACTOR);
			}

			// Set rectangle to default color
			_fe3d.imageEntity_setColor(_rectangle->getEntityID(), _rectangle->getOriginalColor());

			// Textfield
			if (_textfield != nullptr)
			{
				string textfieldID = _textfield->getEntityID();

				// Slowly decrease to default size
				if (_fe3d.textEntity_getSize(rectangleID).x > _textfield->getOriginalSize().x &&
					_fe3d.textEntity_getSize(rectangleID).y > _textfield->getOriginalSize().y)
				{
					_fe3d.textEntity_setSize(textfieldID, _fe3d.textEntity_getSize(textfieldID) * DECREASE_FACTOR);
				}

				// Set to default color
				_fe3d.textEntity_setColor(_textfield->getEntityID(), _textfield->getOriginalColor());
			}
		}
	}

	// Set cursor texture to pointing
	if (_isHovered)
	{
		_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine_assets\\textures\\cursor_pointing.png");
	}
}

void EngineGuiButton::setHoverable(bool isHoverable)
{
	_isHoverable = isHoverable;

	if (isHoverable)
	{
		// Rectangle
		_fe3d.imageEntity_setAlpha(_rectangle->getEntityID(), 1.0f);

		// Text
		if (_textfield != nullptr)
		{
			_fe3d.textEntity_setAlpha(_textfield->getEntityID(), 1.0f);
		}
	}
	else
	{
		// Rectangle
		_fe3d.imageEntity_setAlpha(_rectangle->getEntityID(), 0.25f);

		// Text
		if (_textfield != nullptr)
		{
			_fe3d.textEntity_setAlpha(_textfield->getEntityID(), 0.25f);
		}
	}
}

void EngineGuiButton::changeTextContent(const string& content)
{
	auto textEntityID = getTextfield()->getEntityID();

	// Check if text content changed
	if (content != _fe3d.textEntity_getTextContent(textEntityID))
	{
		// Update textfield
		auto charWidth = (getTextfield()->getOriginalSize().x / static_cast<float>(_fe3d.textEntity_getTextContent(textEntityID).size()));
		auto charHeight = getTextfield()->getOriginalSize().y;
		_fe3d.textEntity_setTextContent(textEntityID, content, charWidth, charHeight);
		getTextfield()->updateOriginalSize();

		// Update rectangle
		auto newRectangleSize = Vec2(getTextfield()->getOriginalSize() / Vec2(TEXT_WIDTH_MULTIPLIER, TEXT_HEIGHT_MULTIPLIER));
		_fe3d.imageEntity_setSize(getRectangle()->getEntityID(), newRectangleSize);
		getRectangle()->updateOriginalSize();
	}
}

bool EngineGuiButton::isHoverable()
{
	return _isHoverable;
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