#include "engine_gui_scrollinglist.hpp"

#include <algorithm>

EngineGuiScrollingList::EngineGuiScrollingList(
	FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color,
	Vec3 buttonColor, Vec3 buttonHoverColor, Vec3 textColor, Vec3 textHoverColor, Vec2 charSize) :
	EngineGuiRectangle(fe3d, parentID + "_scrollinglist", ID, position, size, color),
	_buttonColor(buttonColor),
	_buttonHoverColor(buttonHoverColor),
	_textColor(textColor),
	_textHoverColor(textHoverColor),
	_charSize(charSize)
{

}

void EngineGuiScrollingList::update(bool hoverable)
{
	_updateHovering();
	_updateScolling();
	_updateButtons(hoverable);
}

void EngineGuiScrollingList::addButton(const string& ID, string textContent)
{
	// Calculate dimensions
	float x = 0.0f;
	float y = 1.0f - _charSize.y - (_buttons.size() * (_charSize.y * 1.5f));
	float w = std::min(_charSize.x * textContent.size(), 1.7f);
	float h = _charSize.y;

	// Add button
	Vec2 position = _convertPosition(Vec2(x, y));
	Vec2 size = _convertSize(Vec2(w, h));
	_buttons.push_back(make_shared<EngineGuiButton>(_fe3d, _parentID, ID, Vec2(position.x, position.y), Vec2(size.x, size.y), 
		_buttonColor, _buttonHoverColor, textContent, _textColor, _textHoverColor));
	
	// Define list boundaries
	string rectangleID = _buttons.back()->getRectangle()->getEntityID();
	string textID = _buttons.back()->getTextfield()->getEntityID();
	_fe3d.imageEntity_setMinPosition(rectangleID, Vec2(-1.0f, _originalPosition.y - (_originalSize.y / 2.0f)));
	_fe3d.textEntity_setMinPosition(textID, Vec2(-1.0f, _originalPosition.y - (_originalSize.y / 2.0f)));
	_fe3d.imageEntity_setMaxPosition(rectangleID, Vec2(1.0f, _originalPosition.y + (_originalSize.y / 2.0f)));
	_fe3d.textEntity_setMaxPosition(textID, Vec2(1.0f, _originalPosition.y + (_originalSize.y / 2.0f)));
}

void EngineGuiScrollingList::deleteButton(const string& ID)
{
	// Delete button
	for (size_t i = 0; i < _buttons.size(); i++)
	{
		if (ID == _buttons[i]->getID())
		{
			_buttons.erase(_buttons.begin() + i);
			
			// Retrieve info of all remaining buttons
			vector<string> buttonIDs;
			vector<string> textContents;
			for (size_t j = 0; j < _buttons.size(); j++)
			{
				buttonIDs.push_back(_buttons[j]->getID());
				textContents.push_back(_fe3d.textEntity_getTextContent(_buttons[j]->getTextfield()->getEntityID()));
			}

			// Delete all buttons
			deleteButtons();

			// Create newly positioned buttons
			for (size_t j = 0; j < buttonIDs.size(); j++)
			{
				addButton(buttonIDs[j], textContents[j]);
			}

			// Return
			return;
		}
	}

	// Error
	_fe3d.logger_throwError("Button with ID \"" + ID + "\" not deleted from scrollinglist with ID \"" + _ID + "\"!");
}

void EngineGuiScrollingList::deleteButtons()
{
	_buttons.clear();
	_scrollingOffset = 0.0f;
	_scrollingSpeed = 0.0f;
}

void EngineGuiScrollingList::_updateHovering()
{
	_isHovered = false;

	// Convert dimensions to same space
	Vec2 mousePos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPosition()));
	Vec2 listPos = _fe3d.imageEntity_getPosition(_entityID);
	Vec2 listSize = _fe3d.imageEntity_getSize(_entityID);

	// Check if cursor inside button
	if (mousePos.x > listPos.x - (listSize.x / 2.0f) && mousePos.x < listPos.x + (listSize.x / 2.0f)) // X axis
	{
		if (mousePos.y > listPos.y - (listSize.y / 2.0f) && mousePos.y < listPos.y + (listSize.y / 2.0f)) // Y axis
		{
			_isHovered = true;
		}
	}
}

void EngineGuiScrollingList::_updateScolling()
{
	if (!_buttons.empty())
	{
		// Variables
		bool mustReset = false;

		// Checking if cursor is inside scrolling list
		Vec2 mousePos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPosition()));
		if (mousePos.x > _originalPosition.x - (_originalSize.x / 2.0f) && mousePos.x < _originalPosition.x + (_originalSize.x / 2.0f))
		{
			if (mousePos.y > _originalPosition.y - (_originalSize.y / 2.0f) && mousePos.y < _originalPosition.y + (_originalSize.y / 2.0f))
			{
				float scrollingAcceleration = (float(-_fe3d.input_getMouseWheelY()) / SCROLL_WHEEL_DIVIDER);
				_scrollingSpeed += scrollingAcceleration;
			}
		}

		// Slowing down the scrolling speed
		_scrollingSpeed *= 0.95f;

		// Update the total offset
		_scrollingOffset += _scrollingSpeed;

		// Reset if below zero
		if (_scrollingOffset < 0.0f)
		{
			_scrollingOffset = 0.0f;
			_scrollingSpeed = 0.0f;
			mustReset = true;
		}

		// Reset if maximum scrolling offset reached
		float firstButtonHeight = _fe3d.imageEntity_getPosition(_buttons[0]->getRectangle()->getEntityID()).y;
		float lastButtonHeight = _fe3d.imageEntity_getPosition(_buttons[_buttons.size() - 1]->getRectangle()->getEntityID()).y;
		float listHeight = _fe3d.imageEntity_getPosition(_entityID).y;
		float edgeOffset = (_fe3d.imageEntity_getSize(_entityID).y / 2.0f);
		if (lastButtonHeight >= listHeight - edgeOffset + (_charSize.y / 3.0f))
		{
			if (_scrollingSpeed > 0.0f) // Only if trying to scroll DOWN
			{
				_scrollingSpeed = 0.0f;
			}
		}

		if (firstButtonHeight <= listHeight + edgeOffset - (_charSize.y / 3.0f))
		{
			if (_scrollingSpeed < 0.0f) // Only if trying to scroll UP
			{
				_scrollingSpeed = 0.0f;
			}
		}

		// Update
		for (const auto& button : _buttons)
		{
			string rectangleID = button->getRectangle()->getEntityID();
			string textID = button->getTextfield()->getEntityID();

			// Determine whether moving or resetting the positions
			if (mustReset)
			{
				_fe3d.imageEntity_setPosition(rectangleID, button->getRectangle()->getOriginalPosition());
				_fe3d.textEntity_setPosition(textID, button->getTextfield()->getOriginalPosition());
			}
			else
			{
				_fe3d.imageEntity_move(rectangleID, Vec2(0.0f, _scrollingSpeed));
				_fe3d.textEntity_move(textID, Vec2(0.0f, _scrollingSpeed));
			}
		}
	}
}

void EngineGuiScrollingList::_updateButtons(bool hoverable)
{
	// Update buttons
	for (const auto& button : _buttons)
	{
		button->update(hoverable && _isHovered);
	}
}

Vec2 EngineGuiScrollingList::_convertPosition(Vec2 position)
{
	Vec2 listPosition = _fe3d.imageEntity_getPosition(_entityID);
	Vec2 listSize = _fe3d.imageEntity_getSize(_entityID);
	Vec2 buttonPosition = listPosition + (position * (listSize / 2.0f));
	return buttonPosition;
}

Vec2 EngineGuiScrollingList::_convertSize(Vec2 size)
{
	Vec2 listPosition = _fe3d.imageEntity_getPosition(_entityID);
	Vec2 listSize = _fe3d.imageEntity_getSize(_entityID);
	Vec2 buttonSize = (size / 2.0f) * listSize;
	return buttonSize;
}

void EngineGuiScrollingList::show()
{
	EngineGuiRectangle::show();

	// Show all buttons
	for (const auto& button : _buttons)
	{
		button->show();
	}
}

void EngineGuiScrollingList::hide()
{
	EngineGuiRectangle::hide();

	// Hide all buttons
	for (const auto& button : _buttons)
	{
		button->hide();
	}
}

bool EngineGuiScrollingList::isHovered()
{
	return _isHovered;
}

shared_ptr<EngineGuiButton> EngineGuiScrollingList::getButton(const string& ID)
{
	for (const auto& button : _buttons)
	{
		if (ID == button->getID())
		{
			return button;
		}
	}

	return nullptr;
}

vector<shared_ptr<EngineGuiButton>>& EngineGuiScrollingList::getButtons()
{
	return _buttons;
}