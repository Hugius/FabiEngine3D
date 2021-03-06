#include "engine_gui_screen.hpp"

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

bool EngineGuiScreen::checkScrollingList(const string& ID)
{
	return getScrollingList(ID) != nullptr;
}

bool EngineGuiScreen::checkWriteField(const string& ID)
{
	return getWriteField(ID) != nullptr;
}

bool EngineGuiScreen::checkButton(const string& ID)
{
	return getButton(ID) != nullptr;
}

bool EngineGuiScreen::checkRectangle(const string& ID)
{
	return getRectangle(ID) != nullptr;
}

bool EngineGuiScreen::checkTextfield(const string& ID)
{
	return getTextfield(ID) != nullptr;
}

shared_ptr<EngineGuiScrollingList> EngineGuiScreen::getScrollingList(const string& ID)
{
	for (auto& scrollingList : _scrollingLists)
	{
		if (ID == scrollingList->getID())
		{
			return scrollingList;
		}
	}

	return nullptr;
}

shared_ptr<EngineGuiWriteField> EngineGuiScreen::getWriteField(const string& ID)
{
	for (auto& writefield : _writeFields)
	{
		if (ID == writefield->getID())
		{
			return writefield;
		}
	}

	return nullptr;
}

shared_ptr<EngineGuiButton> EngineGuiScreen::getButton(const string& ID)
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

shared_ptr<EngineGuiRectangle> EngineGuiScreen::getRectangle(const string& ID)
{
	for (auto& rectangle : _rectangles)
	{
		if (ID == rectangle->getID())
		{
			return rectangle;
		}
	}

	return nullptr;
}

shared_ptr<EngineGuiTextfield> EngineGuiScreen::getTextfield(const string& ID)
{
	for (auto& textfield : _textfields)
	{
		if (ID == textfield->getID())
		{
			return textfield;
		}
	}

	return nullptr;
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

vector<shared_ptr<EngineGuiTextfield>>& EngineGuiScreen::getTextfields()
{
	return _textfields;
}

Vec4 EngineGuiScreen::_convertDimensions(Vec2 position, Vec2 size)
{
	Vec2 screenPosition = _parentPosition;
	Vec2 screenSize = _parentSize;
	Vec2 buttonPosition = screenPosition + (position * (screenSize / 2.0f));
	Vec2 buttonSize = (size / 2.0f) * screenSize;

	return Vec4(buttonPosition.x, buttonPosition.y, buttonSize.x, buttonSize.y);
}