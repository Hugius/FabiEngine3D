#include "engine_gui_scrolling_list.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>

EngineGuiScrollingList::EngineGuiScrollingList(FabiEngine3D& fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 buttonColor, fvec3 buttonHoverColor, fvec3 textColor, fvec3 textHoverColor, fvec2 charSize, bool isCentered)
	:
	EngineGuiRectangle(fe3d, parentID + "_scrollingList", ID, position, size, color, isCentered),
	_buttonColor(buttonColor),
	_buttonHoverColor(buttonHoverColor),
	_textColor(textColor),
	_textHoverColor(textHoverColor),
	_charSize(charSize)
{

}

void EngineGuiScrollingList::update(bool isHoverable)
{
	_updateHovering();
	_updateScolling();
	_updateButtons(isHoverable);
}

void EngineGuiScrollingList::createButton(const string& ID, string textContent)
{
	// Calculate dimensions
	float x = 0.0f;
	float y = (1.0f - _charSize.y - (_buttons.size() * (_charSize.y * 1.5f)));
	float w = (_charSize.x * textContent.size());
	float h = _charSize.y;

	// Add button
	fvec2 position = _convertPosition(fvec2(x, y));
	fvec2 size = _convertSize(fvec2(w, h));
	_buttons.push_back(make_shared<EngineGuiButton>(_fe3d, _parentID, ID, fvec2(position.x, position.y), fvec2(size.x, size.y),
					   _buttonColor, _buttonHoverColor, textContent, _textColor, _textHoverColor, true, true, _fe3d.image_isCentered(_entityID)));

	// Define list boundaries
	string rectangleID = _buttons.back()->getRectangle()->getEntityID();
	string textID = _buttons.back()->getTextField()->getEntityID();
	_fe3d.image_setMinPosition(rectangleID, fvec2(-1.0f, _initialPosition.y - (_initialSize.y / 2.0f)));
	_fe3d.text_setMinPosition(textID, fvec2(-1.0f, _initialPosition.y - (_initialSize.y / 2.0f)));
	_fe3d.image_setMaxPosition(rectangleID, fvec2(1.0f, _initialPosition.y + (_initialSize.y / 2.0f)));
	_fe3d.text_setMaxPosition(textID, fvec2(1.0f, _initialPosition.y + (_initialSize.y / 2.0f)));
}

void EngineGuiScrollingList::deleteButton(const string& ID)
{
	// Delete button
	for(size_t i = 0; i < _buttons.size(); i++)
	{
		if(ID == _buttons[i]->getID())
		{
			_buttons.erase(_buttons.begin() + i);

			// Retrieve info of all remaining buttons
			vector<string> buttonIDs;
			vector<string> textContents;
			for(size_t j = 0; j < _buttons.size(); j++)
			{
				buttonIDs.push_back(_buttons[j]->getID());
				textContents.push_back(_fe3d.text_getContent(_buttons[j]->getTextField()->getEntityID()));
			}

			// Delete all buttons
			deleteButtons();

			// Create newly positioned buttons
			for(size_t j = 0; j < buttonIDs.size(); j++)
			{
				createButton(buttonIDs[j], textContents[j]);
			}

			// Return
			return;
		}
	}

	// Error
	Logger::throwError("EngineGuiScrollingList::deleteButton");
}

void EngineGuiScrollingList::deleteButtons()
{
	_buttons.clear();
	_scrollingOffset = 0.0f;
	_scrollingSpeed = 0.0f;
}

void EngineGuiScrollingList::setVisible(bool isVisible)
{
	EngineGuiRectangle::setVisible(isVisible);

	// Show all buttons
	for(const auto& button : _buttons)
	{
		button->setVisible(isVisible);
	}
}

void EngineGuiScrollingList::_updateHovering()
{
	_isHovered = false;

	// Convert dimensions to same space
	fvec2 cursorPosition = Math::convertToNDC(Tools::convertFromScreenCoords(_fe3d.misc_getCursorPosition()));
	fvec2 listPosition = _fe3d.image_getPosition(_entityID);
	fvec2 listSize = _fe3d.image_getSize(_entityID);

	// Check if cursor inside button
	if(cursorPosition.x > listPosition.x - (listSize.x / 2.0f) && cursorPosition.x < listPosition.x + (listSize.x / 2.0f)) // X axis
	{
		if(cursorPosition.y > listPosition.y - (listSize.y / 2.0f) && cursorPosition.y < listPosition.y + (listSize.y / 2.0f)) // Y axis
		{
			_isHovered = true;
		}
	}
}

void EngineGuiScrollingList::_updateScolling()
{
	if(!_buttons.empty())
	{
		// Variables
		bool mustReset = false;

		// Checking if cursor is inside scrolling list
		fvec2 cursorPosition = Math::convertToNDC(Tools::convertFromScreenCoords(_fe3d.misc_getCursorPosition()));
		if(cursorPosition.x > _initialPosition.x - (_initialSize.x / 2.0f) && cursorPosition.x < _initialPosition.x + (_initialSize.x / 2.0f))
		{
			if(cursorPosition.y > _initialPosition.y - (_initialSize.y / 2.0f) && cursorPosition.y < _initialPosition.y + (_initialSize.y / 2.0f))
			{
				float scrollingAcceleration = (static_cast<float>(-_fe3d.input_getMouseWheelY()) / SCROLL_WHEEL_DIVIDER);
				_scrollingSpeed += scrollingAcceleration;
			}
		}

		// Slowing down the scrolling speed
		_scrollingSpeed *= 0.95f;

		// Update the total offset
		_scrollingOffset += _scrollingSpeed;

		// Reset if below zero
		if(_scrollingOffset < 0.0f)
		{
			_scrollingOffset = 0.0f;
			_scrollingSpeed = 0.0f;
			mustReset = true;
		}

		// Reset if maximum scrolling offset reached
		float firstButtonHeight = _fe3d.image_getPosition(_buttons[0]->getRectangle()->getEntityID()).y;
		float lastButtonHeight = _fe3d.image_getPosition(_buttons[_buttons.size() - 1]->getRectangle()->getEntityID()).y;
		float listHeight = _fe3d.image_getPosition(_entityID).y;
		float edgeOffset = (_fe3d.image_getSize(_entityID).y / 2.0f);
		if(lastButtonHeight >= listHeight - edgeOffset + (_charSize.y / 3.0f))
		{
			if(_scrollingSpeed > 0.0f) // Only if trying to scroll DOWN
			{
				_scrollingSpeed = 0.0f;
			}
		}

		if(firstButtonHeight <= listHeight + edgeOffset - (_charSize.y / 3.0f))
		{
			if(_scrollingSpeed < 0.0f) // Only if trying to scroll UP
			{
				_scrollingSpeed = 0.0f;
			}
		}

		// Update
		for(const auto& button : _buttons)
		{
			string rectangleID = button->getRectangle()->getEntityID();
			string textID = button->getTextField()->getEntityID();

			// Determine whether moving or resetting the positions
			if(mustReset)
			{
				_fe3d.image_setPosition(rectangleID, button->getRectangle()->getInitialPosition());
				_fe3d.text_setPosition(textID, button->getTextField()->getInitialPosition());
			}
			else
			{
				_fe3d.image_move(rectangleID, fvec2(0.0f, _scrollingSpeed));
				_fe3d.text_move(textID, fvec2(0.0f, _scrollingSpeed));
			}
		}
	}
}

void EngineGuiScrollingList::_updateButtons(bool hoverable)
{
	// Update buttons
	for(const auto& button : _buttons)
	{
		button->update(hoverable && _isHovered);
	}
}

const fvec2 EngineGuiScrollingList::_convertPosition(fvec2 position) const
{
	fvec2 listPosition = _fe3d.image_getPosition(_entityID);
	fvec2 listSize = _fe3d.image_getSize(_entityID);
	fvec2 buttonPosition = (listPosition + (position * (listSize / 2.0f)));

	return buttonPosition;
}

const fvec2 EngineGuiScrollingList::_convertSize(fvec2 size) const
{
	fvec2 listPosition = _fe3d.image_getPosition(_entityID);
	fvec2 listSize = _fe3d.image_getSize(_entityID);
	fvec2 buttonSize = (size / 2.0f) * listSize;

	return buttonSize;
}

const bool EngineGuiScrollingList::isHovered() const
{
	return _isHovered;
}

shared_ptr<EngineGuiButton> EngineGuiScrollingList::getButton(const string& ID) const
{
	for(const auto& button : _buttons)
	{
		if(ID == button->getID())
		{
			return button;
		}
	}

	return nullptr;
}

const vector<shared_ptr<EngineGuiButton>>& EngineGuiScrollingList::getButtons() const
{
	return _buttons;
}