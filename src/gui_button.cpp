#include "gui_button.hpp"
#include "tools.hpp"

GuiButton::GuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 hoverColor, string textContent, fvec3 textColor, fvec3 textHoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered)
	:
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_rectangle(make_shared<GuiRectangle>(fe3d, parentID + "_button", ID, position, size, color, isCentered)),
	_textField(make_shared<GuiTextField>(fe3d, parentID + "_button", ID, position,
			   fvec2(size.x* TEXT_WIDTH_MULTIPLIER, size.y* TEXT_HEIGHT_MULTIPLIER), textContent, textColor, isCentered, false)),
	_hoverColor(hoverColor),
	_textHoverColor(textHoverColor),
	_isSizeChangeEnabled(isSizeIncreaseEnabled),
	_isColorChangeEnabled(isColorChangeEnabled)
{

}

GuiButton::GuiButton(FabiEngine3D& fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size, const string& texturePath, fvec3 hoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered)
	:
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_rectangle(make_shared<GuiRectangle>(fe3d, parentID + "_button", ID, position, size, texturePath, isCentered)),
	_hoverColor(hoverColor),
	_isSizeChangeEnabled(isSizeIncreaseEnabled),
	_isColorChangeEnabled(isColorChangeEnabled)
{

}

void GuiButton::update(bool isHoverable)
{
	_updateHovering(isHoverable);
}

void GuiButton::setVisible(bool isVisible)
{
	_rectangle->setVisible(isVisible);

	if(_textField != nullptr)
	{
		_textField->setVisible(isVisible);
	}
}

void GuiButton::_updateHovering(bool isHoverable)
{
	_isHovered = false;

	if(_fe3d.image_isVisible(_rectangle->getEntityID()))
	{
		// Convert dimensions to same space
		fvec2 cursorPosition = Math::convertToNDC(Tools::convertFromScreenCoords(_fe3d.misc_getCursorPosition()));
		fvec2 buttonPosition = _fe3d.image_getPosition(_rectangle->getEntityID());
		fvec2 buttonSize = _fe3d.image_getSize(_rectangle->getEntityID());

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
					if(_isSizeChangeEnabled)
					{
						// Temporary values
						string rectangleID = _rectangle->getEntityID();

						// Slowly increase rectangle size
						if(_fe3d.image_getSize(rectangleID).x < (_rectangle->getInitialSize() * TOTAL_SIZE_INCREASE).x &&
						   _fe3d.image_getSize(rectangleID).y < (_rectangle->getInitialSize() * TOTAL_SIZE_INCREASE).y)
						{
							// Rectangle
							_fe3d.image_setSize(rectangleID, _fe3d.image_getSize(rectangleID) * INCREASE_MULTIPLIER);
						}

						// Slowly increase TextField size
						if(_textField != nullptr)
						{
							string TextFieldID = _textField->getEntityID();

							if(_fe3d.text_getSize(rectangleID).x < (_textField->getInitialSize() * TOTAL_SIZE_INCREASE).x &&
							   _fe3d.text_getSize(rectangleID).y < (_textField->getInitialSize() * TOTAL_SIZE_INCREASE).y)
							{
								_fe3d.text_setSize(TextFieldID, _fe3d.text_getSize(TextFieldID) * INCREASE_MULTIPLIER);
							}
						}
					}

					// Update to changed color
					if(_isColorChangeEnabled)
					{
						// Rectangle
						_fe3d.image_setColor(_rectangle->getEntityID(), _hoverColor);

						// TextField
						if(_textField != nullptr)
						{
							_fe3d.text_setColor(_textField->getEntityID(), _textHoverColor);
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
			if(_fe3d.image_getSize(rectangleID).x > _rectangle->getInitialSize().x &&
			   _fe3d.image_getSize(rectangleID).y > _rectangle->getInitialSize().y)
			{
				// Rectangle
				_fe3d.image_setSize(rectangleID, _fe3d.image_getSize(rectangleID) * DECREASE_MULTIPLIER);
			}

			// Set rectangle to default color
			_fe3d.image_setColor(_rectangle->getEntityID(), _rectangle->getInitialColor());

			// Check if button has text field
			if(_textField != nullptr)
			{
				// Temporary values
				string TextFieldID = _textField->getEntityID();

				// Slowly decrease to default size
				if(_fe3d.text_getSize(rectangleID).x > _textField->getInitialSize().x &&
				   _fe3d.text_getSize(rectangleID).y > _textField->getInitialSize().y)
				{
					_fe3d.text_setSize(TextFieldID, _fe3d.text_getSize(TextFieldID) * DECREASE_MULTIPLIER);
				}

				// Set to default color
				_fe3d.text_setColor(_textField->getEntityID(), _textField->getInitialColor());
			}
		}
	}

	if(_isHovered)
	{
		_fe3d.image_setDiffuseMap("@@cursor", "engine\\assets\\texture\\cursor_pointing.png");
	}
}

void GuiButton::setHoverable(bool isHoverable)
{
	_isHoverable = isHoverable;

	if(isHoverable)
	{
		// Rectangle
		_fe3d.image_setTransparency(_rectangle->getEntityID(), 1.0f);

		// Text
		if(_textField != nullptr)
		{
			_fe3d.text_setTransparency(_textField->getEntityID(), 1.0f);
		}
	}
	else
	{
		// Rectangle
		_fe3d.image_setTransparency(_rectangle->getEntityID(), 0.25f);

		// Text
		if(_textField != nullptr)
		{
			_fe3d.text_setTransparency(_textField->getEntityID(), 0.25f);
		}
	}
}

void GuiButton::changeTextContent(const string& content)
{
	auto textEntityID = getTextField()->getEntityID();

	if(content != _fe3d.text_getContent(textEntityID))
	{
		// Update TextField
		auto charWidth = (getTextField()->getInitialSize().x / static_cast<float>(_fe3d.text_getContent(textEntityID).size()));
		auto charHeight = getTextField()->getInitialSize().y;
		_fe3d.text_setContent(textEntityID, content, charWidth, charHeight);
		getTextField()->updateInitialSize();

		// Update rectangle
		auto newRectangleSize = fvec2(getTextField()->getInitialSize() / fvec2(TEXT_WIDTH_MULTIPLIER, TEXT_HEIGHT_MULTIPLIER));
		_fe3d.image_setSize(getRectangle()->getEntityID(), newRectangleSize);
		getRectangle()->updateInitialSize();
	}
}

const bool GuiButton::isHoverable() const
{
	return _isHoverable;
}

const bool GuiButton::isHovered() const
{
	return _isHovered;
}

const string& GuiButton::getID() const
{
	return _ID;
}

const string& GuiButton::getParentID() const
{
	return _parentID;
}

shared_ptr<GuiRectangle> GuiButton::getRectangle() const
{
	return _rectangle;
}

shared_ptr<GuiTextField> GuiButton::getTextField() const
{
	return _textField;
}