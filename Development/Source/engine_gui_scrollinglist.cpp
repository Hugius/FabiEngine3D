#include "engine_gui_scrollinglist.hpp"

#include <algorithm>

EngineGuiScrollingList::EngineGuiScrollingList(
	FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color,
	vec3 buttonColor, vec3 buttonHoverColor, vec3 textColor, vec3 textHoverColor, vec2 charSize) :
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
	vec2 position = _convertPosition(vec2(x, y));
	vec2 size = _convertSize(vec2(w, h));
	_buttons.push_back(make_shared<EngineGuiButton>(_fe3d, _parentID, ID, vec2(position.x, position.y), vec2(size.x, size.y), _buttonColor, _buttonHoverColor, textContent, _textColor, _textHoverColor));
	
	// Define list boundaries
	string rectangleID = _buttons.back()->getRectangle()->getEntityID();
	string textID = _buttons.back()->getTextfield()->getEntityID();
	_fe3d.guiEntity_setMinPosition(rectangleID, vec2(-1.0f, _originalPosition.y - (_originalSize.y / 2.0f)));
	_fe3d.textEntity_setMinPosition(textID, vec2(-1.0f, _originalPosition.y - (_originalSize.y / 2.0f)));
	_fe3d.guiEntity_setMaxPosition(rectangleID, vec2(1.0f, _originalPosition.y + (_originalSize.y / 2.0f)));
	_fe3d.textEntity_setMaxPosition(textID, vec2(1.0f, _originalPosition.y + (_originalSize.y / 2.0f)));
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
	_fe3d.logger_throwError("Button \"" + ID + "\" not deleted!");
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
	vec2 mousePos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getMousePos()));
	vec2 listPos = _fe3d.guiEntity_getPosition(_entityID);
	vec2 listSize = _fe3d.guiEntity_getSize(_entityID);

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
		vec2 mousePos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getMousePos()));
		if (mousePos.x > _originalPosition.x - (_originalSize.x / 2.0f) && mousePos.x < _originalPosition.x + (_originalSize.x / 2.0f))
		{
			if (mousePos.y > _originalPosition.y - (_originalSize.y / 2.0f) && mousePos.y < _originalPosition.y + (_originalSize.y / 2.0f))
			{
				float scrollingAcceleration = (float(-_fe3d.input_getMouseWheelY()) / _scrollWheelDivider);
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

		// Reset if maximum offset reached
		float lastButtonHeight = _fe3d.guiEntity_getPosition(_buttons[_buttons.size() - 1]->getRectangle()->getEntityID()).y;
		float listHeight = _fe3d.guiEntity_getPosition(_entityID).y;
		float edgeOffset = (_fe3d.guiEntity_getSize(_entityID).y / 2.0f);
		if (lastButtonHeight >= listHeight - edgeOffset + (_charSize.y / 3.0f))
		{
			if (_scrollingSpeed > 0.0f) // Only if trying to scroll down
			{
				_scrollingSpeed = 0.0f;
			}
		}

		// Update
		for (auto& button : _buttons)
		{
			string rectangleID = button->getRectangle()->getEntityID();
			string textID = button->getTextfield()->getEntityID();

			// Determine whether moving or resetting the positions
			if (mustReset)
			{
				_fe3d.guiEntity_setPosition(rectangleID, button->getRectangle()->getOriginalPosition());
				_fe3d.textEntity_setPosition(textID, button->getTextfield()->getOriginalPosition());
			}
			else
			{
				_fe3d.guiEntity_move(rectangleID, vec2(0.0f, _scrollingSpeed));
				_fe3d.textEntity_move(textID, vec2(0.0f, _scrollingSpeed));
			}
		}
	}
}

void EngineGuiScrollingList::_updateButtons(bool hoverable)
{
	// Update buttons
	for (auto& button : _buttons)
	{
		button->update(hoverable && _isHovered);
	}
}

vec2 EngineGuiScrollingList::_convertPosition(vec2 position)
{
	vec2 listPosition = _fe3d.guiEntity_getPosition(_entityID);
	vec2 listSize = _fe3d.guiEntity_getSize(_entityID);
	vec2 buttonPosition = listPosition + (position * (listSize / 2.0f));
	return buttonPosition;
}

vec2 EngineGuiScrollingList::_convertSize(vec2 size)
{
	vec2 listPosition = _fe3d.guiEntity_getPosition(_entityID);
	vec2 listSize = _fe3d.guiEntity_getSize(_entityID);
	vec2 buttonSize = (size / 2.0f) * listSize;
	return buttonSize;
}

void EngineGuiScrollingList::show()
{
	EngineGuiRectangle::show();

	// Show all buttons
	for (auto& button : _buttons)
	{
		button->show();
	}
}

void EngineGuiScrollingList::hide()
{
	EngineGuiRectangle::hide();

	// Hide all buttons
	for (auto& button : _buttons)
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
	for (auto& button : _buttons)
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