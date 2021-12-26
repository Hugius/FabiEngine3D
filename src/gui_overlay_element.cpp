#include "gui_overlay.hpp"
#include "logger.hpp"

void GuiOverlay::createScrollingList(const string& ID, fvec2 position, fvec2 size, fvec3 color,
									 fvec3 buttonColor, fvec3 buttonHoverColor, fvec3 textColor, fvec3 textHoverColor, fvec2 charSize, bool isCentered)
{
	_scrollingLists.push_back(make_shared<GuiScrollingList>(_fe3d, "overlay", ID, position, size, color, buttonColor, buttonHoverColor, textColor, textHoverColor, charSize, isCentered));
}

void GuiOverlay::createWriteField(const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 hoverColor, fvec3 textColor, fvec3 textHoverColor,
								  bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered)
{
	_writeFields.push_back(make_shared<GuiWriteField>(_fe3d, "overlay", ID, position, size, color, hoverColor, textColor, textHoverColor, noNumbers, noCaps, noSpecials, noLetters, minusAllowed, isCentered));
}

void GuiOverlay::createButton(const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 hoverColor, string textContent, fvec3 textColor, fvec3 textHoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered)
{
	_buttons.push_back(make_shared<GuiButton>(_fe3d, "overlay", ID, position, size, color, hoverColor, textContent, textColor, textHoverColor, isSizeIncreaseEnabled, isColorChangeEnabled, isCentered));
}

void GuiOverlay::createButton(const string& ID, fvec2 position, fvec2 size, const string& texturePath, fvec3 hoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered)
{
	_buttons.push_back(make_shared<GuiButton>(_fe3d, "overlay", ID, position, size, texturePath, hoverColor, isSizeIncreaseEnabled, isColorChangeEnabled, isCentered));
}

void GuiOverlay::createRectangle(const string& ID, fvec2 position, fvec2 size, fvec3 color, bool isCentered)
{
	_rectangles.push_back(make_shared<GuiRectangle>(_fe3d, "overlay", ID, position, size, color, isCentered));
}

void GuiOverlay::createRectangle(const string& ID, fvec2 position, fvec2 size, const string& texturePath, bool isCentered)
{
	_rectangles.push_back(make_shared<GuiRectangle>(_fe3d, "overlay", ID, position, size, texturePath, isCentered));
}

void GuiOverlay::createTextField(const string& ID, fvec2 position, fvec2 size, string textContent, fvec3 textColor, bool isCentered)
{
	_textFields.push_back(make_shared<GuiTextField>(_fe3d, "overlay", ID, position, size, textContent, textColor, isCentered));
}

const bool GuiOverlay::isScrollingListExisting(const string& ID) const
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

const bool GuiOverlay::isWriteFieldExisting(const string& ID) const
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

const bool GuiOverlay::isButtonExisting(const string& ID) const
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

const bool GuiOverlay::isRectangleExisting(const string& ID) const
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

const bool GuiOverlay::isTextFieldExisting(const string& ID) const
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

shared_ptr<GuiScrollingList> GuiOverlay::getScrollingList(const string& ID) const
{
	for(const auto& scrollingList : _scrollingLists)
	{
		if(ID == scrollingList->getID())
		{
			return scrollingList;
		}
	}

	Logger::throwError("GuiOverlay::getScrollingList");
}

shared_ptr<GuiWriteField> GuiOverlay::getWriteField(const string& ID) const
{
	for(const auto& writeField : _writeFields)
	{
		if(ID == writeField->getID())
		{
			return writeField;
		}
	}

	Logger::throwError("GuiOverlay::getWriteField");
}

shared_ptr<GuiButton> GuiOverlay::getButton(const string& ID) const
{
	for(const auto& button : _buttons)
	{
		if(ID == button->getID())
		{
			return button;
		}
	}

	Logger::throwError("GuiOverlay::getButton");
}

shared_ptr<GuiRectangle> GuiOverlay::getRectangle(const string& ID) const
{
	for(const auto& rectangle : _rectangles)
	{
		if(ID == rectangle->getID())
		{
			return rectangle;
		}
	}

	Logger::throwError("GuiOverlay::getRectangle");
}

shared_ptr<GuiTextField> GuiOverlay::getTextField(const string& ID) const
{
	for(const auto& textField : _textFields)
	{
		if(ID == textField->getID())
		{
			return textField;
		}
	}

	Logger::throwError("GuiOverlay::getTextField");
}

const vector<shared_ptr<GuiScrollingList>>& GuiOverlay::getScrollingLists() const
{
	return _scrollingLists;
}

const vector<shared_ptr<GuiWriteField>>& GuiOverlay::getWriteFields() const
{
	return _writeFields;
}

const vector<shared_ptr<GuiButton>>& GuiOverlay::getButtons() const
{
	return _buttons;
}

const vector<shared_ptr<GuiRectangle>>& GuiOverlay::getRectangles() const
{
	return _rectangles;
}

const vector<shared_ptr<GuiTextField>>& GuiOverlay::getTextFields() const
{
	return _textFields;
}

void GuiOverlay::deleteScrollingList(const string& ID)
{
	for(size_t i = 0; i < _scrollingLists.size(); i++)
	{
		if(ID == _scrollingLists[i]->getID())
		{
			_scrollingLists.erase(_scrollingLists.begin() + i);
			return;
		}
	}

	Logger::throwError("GuiOverlay::deleteScrollingList");
}

void GuiOverlay::deleteWriteField(const string& ID)
{
	for(size_t i = 0; i < _writeFields.size(); i++)
	{
		if(ID == _writeFields[i]->getID())
		{
			_writeFields.erase(_writeFields.begin() + i);
			return;
		}
	}

	Logger::throwError("GuiOverlay::deleteWriteField");
}

void GuiOverlay::deleteButton(const string& ID)
{
	for(size_t i = 0; i < _buttons.size(); i++)
	{
		if(ID == _buttons[i]->getID())
		{
			_buttons.erase(_buttons.begin() + i);
			return;
		}
	}

	Logger::throwError("GuiOverlay::deleteButton");
}

void GuiOverlay::deleteRectangle(const string& ID)
{
	for(size_t i = 0; i < _rectangles.size(); i++)
	{
		if(ID == _rectangles[i]->getID())
		{
			_rectangles.erase(_rectangles.begin() + i);
			return;
		}
	}

	Logger::throwError("GuiOverlay::deleteRectangle");
}

void GuiOverlay::deleteTextField(const string& ID)
{
	for(size_t i = 0; i < _textFields.size(); i++)
	{
		if(ID == _textFields[i]->getID())
		{
			_textFields.erase(_textFields.begin() + i);
			return;
		}
	}

	Logger::throwError("GuiOverlay::deleteTextField");
}