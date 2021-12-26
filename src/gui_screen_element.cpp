#include "gui_screen.hpp"
#include "logger.hpp"

void GuiScreen::createScrollingList(const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 buttonColor, fvec3 buttonHoverColor, fvec3 textColor, fvec3 textHoverColor, fvec2 charSize, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_scrollingLists.push_back(make_shared<GuiScrollingList>(_fe3d, _parentID + "_" + _ID, ID, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), color, buttonColor, buttonHoverColor, textColor, textHoverColor, charSize, isCentered));
}

void GuiScreen::createWriteField(const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 hoverColor, fvec3 textColor, fvec3 textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_writeFields.push_back(make_shared<GuiWriteField>(_fe3d, _parentID + "_" + _ID, ID, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), color, hoverColor, textColor, textHoverColor, noNumbers, noCaps, noSpecials, noLetters, minusAllowed, isCentered));
}

void GuiScreen::createButton(const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 hoverColor, string textContent, fvec3 textColor, fvec3 textHoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_buttons.push_back(make_shared<GuiButton>(_fe3d, _parentID + "_" + _ID, ID, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), color, hoverColor, textContent, textColor, textHoverColor, isSizeIncreaseEnabled, isColorChangeEnabled, isCentered));
}

void GuiScreen::createButton(const string& ID, fvec2 position, fvec2 size, const string& texturePath, fvec3 hoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_buttons.push_back(make_shared<GuiButton>(_fe3d, _parentID + "_" + _ID, ID, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), texturePath, hoverColor, isSizeIncreaseEnabled, isColorChangeEnabled, isCentered));
}

void GuiScreen::createRectangle(const string& ID, fvec2 position, fvec2 size, fvec3 color, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_rectangles.push_back(make_shared<GuiRectangle>(_fe3d, _parentID + "_" + _ID, ID, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), color, isCentered));
}

void GuiScreen::createRectangle(const string& ID, fvec2 position, fvec2 size, const string& texturePath, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_rectangles.push_back(make_shared<GuiRectangle>(_fe3d, _parentID + "_" + _ID, ID, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), texturePath, isCentered));
}

void GuiScreen::createTextField(const string& ID, fvec2 position, fvec2 size, string textContent, fvec3 textColor, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_textFields.push_back(make_shared<GuiTextField>(_fe3d, _parentID + "_" + _ID, ID, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), textContent, textColor, isCentered));
}

void GuiScreen::deleteScrollingList(const string& ID)
{
	for(size_t i = 0; i < _scrollingLists.size(); i++)
	{
		if(ID == _scrollingLists[i]->getID())
		{
			_scrollingLists.erase(_scrollingLists.begin() + i);
			return;
		}
	}

	Logger::throwError("GuiScreen::deleteScrollingList");
}

void GuiScreen::deleteWriteField(const string& ID)
{
	for(size_t i = 0; i < _writeFields.size(); i++)
	{
		if(ID == _writeFields[i]->getID())
		{
			_writeFields.erase(_writeFields.begin() + i);
			return;
		}
	}

	Logger::throwError("GuiScreen::deleteWriteField");
}

void GuiScreen::deleteButton(const string& ID)
{
	for(size_t i = 0; i < _buttons.size(); i++)
	{
		if(ID == _buttons[i]->getID())
		{
			_buttons.erase(_buttons.begin() + i);
			return;
		}
	}

	Logger::throwError("GuiScreen::deleteButton");
}

void GuiScreen::deleteRectangle(const string& ID)
{
	for(size_t i = 0; i < _rectangles.size(); i++)
	{
		if(ID == _rectangles[i]->getID())
		{
			_rectangles.erase(_rectangles.begin() + i);
			return;
		}
	}

	Logger::throwError("GuiScreen::deleteRectangle");
}

void GuiScreen::deleteTextField(const string& ID)
{
	for(size_t i = 0; i < _textFields.size(); i++)
	{
		if(ID == _textFields[i]->getID())
		{
			_textFields.erase(_textFields.begin() + i);
			return;
		}
	}

	Logger::throwError("GuiScreen::deleteTextField");
}

const bool GuiScreen::isScrollingListExisting(const string& ID) const
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

const bool GuiScreen::isWriteFieldExisting(const string& ID) const
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

const bool GuiScreen::isButtonExisting(const string& ID) const
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

const bool GuiScreen::isRectangleExisting(const string& ID) const
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

const bool GuiScreen::isTextFieldExisting(const string& ID) const
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

shared_ptr<GuiScrollingList> GuiScreen::getScrollingList(const string& ID) const
{
	for(const auto& scrollingList : _scrollingLists)
	{
		if(ID == scrollingList->getID())
		{
			return scrollingList;
		}
	}

	Logger::throwError("GuiScreen::getScrollingList");
}

shared_ptr<GuiWriteField> GuiScreen::getWriteField(const string& ID) const
{
	for(const auto& writeField : _writeFields)
	{
		if(ID == writeField->getID())
		{
			return writeField;
		}
	}

	Logger::throwError("GuiScreen::getWriteField");
}

shared_ptr<GuiButton> GuiScreen::getButton(const string& ID) const
{
	for(const auto& button : _buttons)
	{
		if(ID == button->getID())
		{
			return button;
		}
	}

	Logger::throwError("GuiScreen::getButton");
}

shared_ptr<GuiRectangle> GuiScreen::getRectangle(const string& ID) const
{
	for(const auto& rectangle : _rectangles)
	{
		if(ID == rectangle->getID())
		{
			return rectangle;
		}
	}

	Logger::throwError("GuiScreen::getRectangle");
}

shared_ptr<GuiTextField> GuiScreen::getTextField(const string& ID) const
{
	for(const auto& textField : _textFields)
	{
		if(ID == textField->getID())
		{
			return textField;
		}
	}

	Logger::throwError("GuiScreen::getTextField");
}

const vector<shared_ptr<GuiScrollingList>>& GuiScreen::getScrollingLists() const
{
	return _scrollingLists;
}

const vector<shared_ptr<GuiWriteField>>& GuiScreen::getWriteFields() const
{
	return _writeFields;
}

const vector<shared_ptr<GuiButton>>& GuiScreen::getButtons() const
{
	return _buttons;
}

const vector<shared_ptr<GuiRectangle>>& GuiScreen::getRectangles() const
{
	return _rectangles;
}

const vector<shared_ptr<GuiTextField>>& GuiScreen::getTextFields() const
{
	return _textFields;
}