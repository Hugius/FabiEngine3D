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

const string& EngineGuiScreen::getID()
{
	return _ID;
}

const string& EngineGuiScreen::getParentID()
{
	return _parentID;
}

Vec2 EngineGuiScreen::convertPosition(Vec2 position)
{
	Vec2 screenPosition = _parentPosition;
	Vec2 screenSize = _parentSize;
	Vec2 buttonPosition = screenPosition + (position * (screenSize / 2.0f));

	return buttonPosition;
}

Vec2 EngineGuiScreen::convertSize(Vec2 size)
{
	Vec2 screenPosition = _parentPosition;
	Vec2 screenSize = _parentSize;
	Vec2 buttonSize = (size / 2.0f) * screenSize;

	return buttonSize;
}

bool EngineGuiScreen::isScrollingListExisting(const string& ID)
{
	for (const auto& scrollingList : _scrollingLists)
	{
		if (ID == scrollingList->getID())
		{
			return true;
		}
	}

	return false;
}

bool EngineGuiScreen::isWriteFieldExisting(const string& ID)
{
	for (const auto& writeField : _writeFields)
	{
		if (ID == writeField->getID())
		{
			return true;
		}
	}

	return false;
}

bool EngineGuiScreen::isButtonExisting(const string& ID)
{
	for (const auto& button : _buttons)
	{
		if (ID == button->getID())
		{
			return true;
		}
	}

	return false;
}

bool EngineGuiScreen::isRectangleExisting(const string& ID)
{
	for (const auto& rectangle : _rectangles)
	{
		if (ID == rectangle->getID())
		{
			return true;
		}
	}

	return false;
}

bool EngineGuiScreen::isTextFieldExisting(const string& ID)
{
	for (const auto& textField : _textFields)
	{
		if (ID == textField->getID())
		{
			return true;
		}
	}

	return false;
}

shared_ptr<EngineGuiScrollingList> EngineGuiScreen::getScrollingList(const string& ID)
{
	// Retrieve scrolling list
	for (const auto& scrollingList : _scrollingLists)
	{
		if (ID == scrollingList->getID())
		{
			return scrollingList;
		}
	}

	// Error
	Logger::throwError("EngineGuiScreen::getScrollingList");
}

shared_ptr<EngineGuiWriteField> EngineGuiScreen::getWriteField(const string& ID)
{
	// Retrieve write field
	for (const auto& writeField : _writeFields)
	{
		if (ID == writeField->getID())
		{
			return writeField;
		}
	}

	// Error
	Logger::throwError("EngineGuiScreen::getWriteField");
}

shared_ptr<EngineGuiButton> EngineGuiScreen::getButton(const string& ID)
{
	// Retrieve button
	for (const auto& button : _buttons)
	{
		if (ID == button->getID())
		{
			return button;
		}
	}

	// Error
	Logger::throwError("EngineGuiScreen::getButton");
}

shared_ptr<EngineGuiRectangle> EngineGuiScreen::getRectangle(const string& ID)
{
	// Retrieve rectangle
	for (const auto& rectangle : _rectangles)
	{
		if (ID == rectangle->getID())
		{
			return rectangle;
		}
	}

	// Error
	Logger::throwError("EngineGuiScreen::getRectangle");
}

shared_ptr<EngineGuiTextField> EngineGuiScreen::getTextField(const string& ID)
{
	// Retrieve text field
	for (const auto& textField : _textFields)
	{
		if (ID == textField->getID())
		{
			return textField;
		}
	}

	// Error
	Logger::throwError("EngineGuiScreen::getTextField");
}

vector<shared_ptr<EngineGuiScrollingList>>& EngineGuiScreen::getScrollingLists()
{
	return _scrollingLists;
}

vector<shared_ptr<EngineGuiWriteField>>& EngineGuiScreen::getWriteFields()
{
	return _writeFields;
}

vector<shared_ptr<EngineGuiButton>>& EngineGuiScreen::getButtons()
{
	return _buttons;
}

vector<shared_ptr<EngineGuiRectangle>>& EngineGuiScreen::getRectangles()
{
	return _rectangles;
}

vector<shared_ptr<EngineGuiTextField>>& EngineGuiScreen::getTextFields()
{
	return _textFields;
}

Vec4 EngineGuiScreen::_convertDimensions(Vec2 position, Vec2 size)
{
	Vec2 screenPosition = _parentPosition;
	Vec2 screenSize = _parentSize;
	Vec2 buttonPosition = screenPosition + (position * (screenSize / 2.0f));
	Vec2 buttonSize = (size / 2.0f) * screenSize;

	return Vec4(buttonPosition.x, buttonPosition.y, buttonSize.x, buttonSize.y);
}