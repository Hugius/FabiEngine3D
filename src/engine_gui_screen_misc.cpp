#include "engine_gui_screen.hpp"
#include "logger.hpp"

void EngineGuiScreen::show()
{
	_isActive = true;
}

void EngineGuiScreen::hide()
{
	_isActive = false;
}

const string& EngineGuiScreen::getID() const
{
	return _ID;
}

const string& EngineGuiScreen::getParentID() const
{
	return _parentID;
}

const fvec2 EngineGuiScreen::convertPosition(fvec2 position) const
{
	fvec2 screenPosition = _parentPosition;
	fvec2 screenSize = _parentSize;
	fvec2 buttonPosition = (screenPosition + (position * (screenSize / 2.0f)));

	return buttonPosition;
}

const fvec2 EngineGuiScreen::convertSize(fvec2 size) const
{
	fvec2 screenPosition = _parentPosition;
	fvec2 screenSize = _parentSize;
	fvec2 buttonSize = (size / 2.0f) * screenSize;

	return buttonSize;
}

const bool EngineGuiScreen::isScrollingListExisting(const string& ID) const
{
	for(const auto& scrollingList : _scrollingLists)
	{
		if(ID == scrollingList->getID())
		{
			return true;
		}
	}

	return false;
}

const bool EngineGuiScreen::isWriteFieldExisting(const string& ID) const
{
	for(const auto& writeField : _writeFields)
	{
		if(ID == writeField->getID())
		{
			return true;
		}
	}

	return false;
}

const bool EngineGuiScreen::isButtonExisting(const string& ID) const
{
	for(const auto& button : _buttons)
	{
		if(ID == button->getID())
		{
			return true;
		}
	}

	return false;
}

const bool EngineGuiScreen::isRectangleExisting(const string& ID) const
{
	for(const auto& rectangle : _rectangles)
	{
		if(ID == rectangle->getID())
		{
			return true;
		}
	}

	return false;
}

const bool EngineGuiScreen::isTextFieldExisting(const string& ID) const
{
	for(const auto& textField : _textFields)
	{
		if(ID == textField->getID())
		{
			return true;
		}
	}

	return false;
}

shared_ptr<EngineGuiScrollingList> EngineGuiScreen::getScrollingList(const string& ID) const
{
	// Retrieve scrolling list
	for(const auto& scrollingList : _scrollingLists)
	{
		if(ID == scrollingList->getID())
		{
			return scrollingList;
		}
	}

	// Error
	Logger::throwError("EngineGuiScreen::getScrollingList");
}

shared_ptr<EngineGuiWriteField> EngineGuiScreen::getWriteField(const string& ID) const
{
	// Retrieve write field
	for(const auto& writeField : _writeFields)
	{
		if(ID == writeField->getID())
		{
			return writeField;
		}
	}

	// Error
	Logger::throwError("EngineGuiScreen::getWriteField");
}

shared_ptr<EngineGuiButton> EngineGuiScreen::getButton(const string& ID) const
{
	// Retrieve button
	for(const auto& button : _buttons)
	{
		if(ID == button->getID())
		{
			return button;
		}
	}

	// Error
	Logger::throwError("EngineGuiScreen::getButton");
}

shared_ptr<EngineGuiRectangle> EngineGuiScreen::getRectangle(const string& ID) const
{
	// Retrieve rectangle
	for(const auto& rectangle : _rectangles)
	{
		if(ID == rectangle->getID())
		{
			return rectangle;
		}
	}

	// Error
	Logger::throwError("EngineGuiScreen::getRectangle");
}

shared_ptr<EngineGuiTextField> EngineGuiScreen::getTextField(const string& ID) const
{
	// Retrieve text field
	for(const auto& textField : _textFields)
	{
		if(ID == textField->getID())
		{
			return textField;
		}
	}

	// Error
	Logger::throwError("EngineGuiScreen::getTextField");
}

const vector<shared_ptr<EngineGuiScrollingList>>& EngineGuiScreen::getScrollingLists() const
{
	return _scrollingLists;
}

const vector<shared_ptr<EngineGuiWriteField>>& EngineGuiScreen::getWriteFields() const
{
	return _writeFields;
}

const vector<shared_ptr<EngineGuiButton>>& EngineGuiScreen::getButtons() const
{
	return _buttons;
}

const vector<shared_ptr<EngineGuiRectangle>>& EngineGuiScreen::getRectangles() const
{
	return _rectangles;
}

const vector<shared_ptr<EngineGuiTextField>>& EngineGuiScreen::getTextFields() const
{
	return _textFields;
}

const fvec4 EngineGuiScreen::_convertDimensions(fvec2 position, fvec2 size) const
{
	fvec2 screenPosition = _parentPosition;
	fvec2 screenSize = _parentSize;
	fvec2 buttonPosition = (screenPosition + (position * (screenSize / 2.0f)));
	fvec2 buttonSize = (size / 2.0f) * screenSize;

	return fvec4(buttonPosition.x, buttonPosition.y, buttonSize.x, buttonSize.y);
}