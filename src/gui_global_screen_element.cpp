#include "gui_global_screen.hpp"
#include "logger.hpp"

void GuiGlobalScreen::createScrollingList(const string& ID, fvec2 position, fvec2 size, fvec3 color,
										  fvec3 buttonColor, fvec3 buttonHoverColor, fvec3 textColor, fvec3 textHoverColor, fvec2 charSize, bool isCentered)
{
	_scrollingLists.push_back(make_shared<GuiScrollingList>(_fe3d, "globalscreen", ID, position, size, color, buttonColor, buttonHoverColor, textColor, textHoverColor, charSize, isCentered));
}

void GuiGlobalScreen::createWriteField(const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 hoverColor, fvec3 textColor, fvec3 textHoverColor,
									   bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered)
{
	_writeFields.push_back(make_shared<GuiWriteField>(_fe3d, "globalscreen", ID, position, size, color, hoverColor, textColor, textHoverColor, noNumbers, noCaps, noSpecials, noLetters, minusAllowed, isCentered));
}

void GuiGlobalScreen::createButton(const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 hoverColor, string textContent, fvec3 textColor, fvec3 textHoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered)
{
	_buttons.push_back(make_shared<GuiButton>(_fe3d, "globalscreen", ID, position, size, color, hoverColor, textContent, textColor, textHoverColor, isSizeIncreaseEnabled, isColorChangeEnabled, isCentered));
}

void GuiGlobalScreen::createButton(const string& ID, fvec2 position, fvec2 size, const string& texturePath, fvec3 hoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered)
{
	_buttons.push_back(make_shared<GuiButton>(_fe3d, "globalscreen", ID, position, size, texturePath, hoverColor, isSizeIncreaseEnabled, isColorChangeEnabled, isCentered));
}

void GuiGlobalScreen::createRectangle(const string& ID, fvec2 position, fvec2 size, fvec3 color, bool isCentered)
{
	_rectangles.push_back(make_shared<GuiRectangle>(_fe3d, "globalscreen", ID, position, size, color, isCentered));
}

void GuiGlobalScreen::createRectangle(const string& ID, fvec2 position, fvec2 size, const string& texturePath, bool isCentered)
{
	_rectangles.push_back(make_shared<GuiRectangle>(_fe3d, "globalscreen", ID, position, size, texturePath, isCentered));
}

void GuiGlobalScreen::createTextField(const string& ID, fvec2 position, fvec2 size, string textContent, fvec3 textColor, bool isCentered, bool isDynamic)
{
	_textFields.push_back(make_shared<GuiTextField>(_fe3d, "globalscreen", ID, position, size, textContent, textColor, isCentered, isDynamic));
}

const bool GuiGlobalScreen::isScrollingListExisting(const string& ID) const
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

const bool GuiGlobalScreen::isWriteFieldExisting(const string& ID) const
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

const bool GuiGlobalScreen::isButtonExisting(const string& ID) const
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

const bool GuiGlobalScreen::isRectangleExisting(const string& ID) const
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

const bool GuiGlobalScreen::isTextFieldExisting(const string& ID) const
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

shared_ptr<GuiScrollingList> GuiGlobalScreen::getScrollingList(const string& ID) const
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
	Logger::throwError("GuiGlobalScreen::getScrollingList");
}

shared_ptr<GuiWriteField> GuiGlobalScreen::getWriteField(const string& ID) const
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
	Logger::throwError("GuiGlobalScreen::getWriteField");
}

shared_ptr<GuiButton> GuiGlobalScreen::getButton(const string& ID) const
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
	Logger::throwError("GuiGlobalScreen::getButton");
}

shared_ptr<GuiRectangle> GuiGlobalScreen::getRectangle(const string& ID) const
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
	Logger::throwError("GuiGlobalScreen::getRectangle");
}

shared_ptr<GuiTextField> GuiGlobalScreen::getTextField(const string& ID) const
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
	Logger::throwError("GuiGlobalScreen::getTextField");
}

const vector<shared_ptr<GuiScrollingList>>& GuiGlobalScreen::getScrollingLists() const
{
	return _scrollingLists;
}

const vector<shared_ptr<GuiWriteField>>& GuiGlobalScreen::getWriteFields() const
{
	return _writeFields;
}

const vector<shared_ptr<GuiButton>>& GuiGlobalScreen::getButtons() const
{
	return _buttons;
}

const vector<shared_ptr<GuiRectangle>>& GuiGlobalScreen::getRectangles() const
{
	return _rectangles;
}

const vector<shared_ptr<GuiTextField>>& GuiGlobalScreen::getTextFields() const
{
	return _textFields;
}

void GuiGlobalScreen::deleteScrollingList(const string& ID)
{
	// Delete scrolling list
	for(size_t i = 0; i < _scrollingLists.size(); i++)
	{
		if(ID == _scrollingLists[i]->getID())
		{
			_scrollingLists.erase(_scrollingLists.begin() + i);
			return;
		}
	}

	// Error
	Logger::throwError("GuiGlobalScreen::deleteScrollingList");
}

void GuiGlobalScreen::deleteWriteField(const string& ID)
{
	// Delete write field
	for(size_t i = 0; i < _writeFields.size(); i++)
	{
		if(ID == _writeFields[i]->getID())
		{
			_writeFields.erase(_writeFields.begin() + i);
			return;
		}
	}

	// Error
	Logger::throwError("GuiGlobalScreen::deleteWriteField");
}

void GuiGlobalScreen::deleteButton(const string& ID)
{
	// Delete button
	for(size_t i = 0; i < _buttons.size(); i++)
	{
		if(ID == _buttons[i]->getID())
		{
			_buttons.erase(_buttons.begin() + i);
			return;
		}
	}

	// Error
	Logger::throwError("GuiGlobalScreen::deleteButton");
}

void GuiGlobalScreen::deleteRectangle(const string& ID)
{
	// Delete rectangle
	for(size_t i = 0; i < _rectangles.size(); i++)
	{
		if(ID == _rectangles[i]->getID())
		{
			_rectangles.erase(_rectangles.begin() + i);
			return;
		}
	}

	// Error
	Logger::throwError("GuiGlobalScreen::deleteRectangle");
}

void GuiGlobalScreen::deleteTextField(const string& ID)
{
	// Delete text field
	for(size_t i = 0; i < _textFields.size(); i++)
	{
		if(ID == _textFields[i]->getID())
		{
			_textFields.erase(_textFields.begin() + i);
			return;
		}
	}

	// Error
	Logger::throwError("GuiGlobalScreen::deleteTextField");
}