#include "engine_gui_screen.hpp"
#include "logger.hpp"

void EngineGuiScreen::createScrollingList(const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 buttonColor, fvec3 buttonHoverColor, fvec3 textColor, fvec3 textHoverColor, fvec2 charSize, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_scrollingLists.push_back(make_shared<EngineGuiScrollingList>(_fe3d, _parentID + "_" + _ID, ID, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), color, buttonColor, buttonHoverColor, textColor, textHoverColor, charSize, isCentered));
}

void EngineGuiScreen::createWriteField(const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 hoverColor, fvec3 textColor, fvec3 textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_writeFields.push_back(make_shared<EngineGuiWriteField>(_fe3d, _parentID + "_" + _ID, ID, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), color, hoverColor, textColor, textHoverColor, noNumbers, noCaps, noSpecials, noLetters, minusAllowed, isCentered));
}

void EngineGuiScreen::createButton(const string& ID, fvec2 position, fvec2 size, fvec3 color, fvec3 hoverColor, string textContent, fvec3 textColor, fvec3 textHoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_buttons.push_back(make_shared<EngineGuiButton>(_fe3d, _parentID + "_" + _ID, ID, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), color, hoverColor, textContent, textColor, textHoverColor, isSizeIncreaseEnabled, isColorChangeEnabled, isCentered));
}

void EngineGuiScreen::createButton(const string& ID, fvec2 position, fvec2 size, const string& texturePath, fvec3 hoverColor, bool isSizeIncreaseEnabled, bool isColorChangeEnabled, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_buttons.push_back(make_shared<EngineGuiButton>(_fe3d, _parentID + "_" + _ID, ID, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), texturePath, hoverColor, isSizeIncreaseEnabled, isColorChangeEnabled, isCentered));
}

void EngineGuiScreen::createRectangle(const string& ID, fvec2 position, fvec2 size, fvec3 color, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_rectangles.push_back(make_shared<EngineGuiRectangle>(_fe3d, _parentID + "_" + _ID, ID, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), color, isCentered));
}

void EngineGuiScreen::createRectangle(const string& ID, fvec2 position, fvec2 size, const string& texturePath, bool isCentered)
{
	auto dimensions = _convertDimensions(position, size);
	_rectangles.push_back(make_shared<EngineGuiRectangle>(_fe3d, _parentID + "_" + _ID, ID, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), texturePath, isCentered));
}

void EngineGuiScreen::createTextField(const string& ID, fvec2 position, fvec2 size, string textContent, fvec3 textColor, bool isCentered, bool isDynamic)
{
	auto dimensions = _convertDimensions(position, size);
	_textFields.push_back(make_shared<EngineGuiTextField>(_fe3d, _parentID + "_" + _ID, ID, fvec2(dimensions.x, dimensions.y), fvec2(dimensions.z, dimensions.w), textContent, textColor, isCentered, isDynamic));
}

void EngineGuiScreen::deleteScrollingList(const string& ID)
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
	Logger::throwError("EngineGuiScreen::deleteScrollingList");
}

void EngineGuiScreen::deleteWriteField(const string& ID)
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
	Logger::throwError("EngineGuiScreen::deleteWriteField");
}

void EngineGuiScreen::deleteButton(const string& ID)
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
	Logger::throwError("EngineGuiScreen::deleteButton");
}

void EngineGuiScreen::deleteRectangle(const string& ID)
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
	Logger::throwError("EngineGuiScreen::deleteRectangle");
}

void EngineGuiScreen::deleteTextField(const string& ID)
{
	// Delete TextField
	for(size_t i = 0; i < _textFields.size(); i++)
	{
		if(ID == _textFields[i]->getID())
		{
			_textFields.erase(_textFields.begin() + i);
			return;
		}
	}

	// Error
	Logger::throwError("EngineGuiScreen::deleteTextField");
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