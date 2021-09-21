#include "engine_gui_global_screen.hpp"
#include "logger.hpp"

EngineGuiGlobalScreen::EngineGuiGlobalScreen(FabiEngine3D& fe3d)
	:
	_fe3d(fe3d)
{

}

void EngineGuiGlobalScreen::update()
{
	// Update scrolling lists
	for (const auto& scrollingList : _scrollingLists)
	{
		scrollingList->update(true);
	}

	// Update writeFields
	for (const auto& writeField : _writeFields)
	{
		writeField->update(true);
	}

	// Update buttons
	for (const auto& button : _buttons)
	{
		button->update(true);
	}

	// Miscellaneous
	_updateValueFormDeleting();
}

void EngineGuiGlobalScreen::createScrollingList(const string& ID, Vec2 position, Vec2 size, Vec3 color,
	Vec3 buttonColor, Vec3 buttonHoverColor, Vec3 textColor, Vec3 textHoverColor, Vec2 charSize)
{
	_scrollingLists.push_back(make_shared<EngineGuiScrollingList>(_fe3d, "globalscreen", ID, position, size, color, buttonColor, buttonHoverColor, textColor, textHoverColor, charSize));
}

void EngineGuiGlobalScreen::createWriteField(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, Vec3 textColor, Vec3 textHoverColor, 
	bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed)
{
	_writeFields.push_back(make_shared<EngineGuiWriteField>(_fe3d, "globalscreen", ID, position, size, color, hoverColor, textColor, textHoverColor, noNumbers, noCaps, noSpecials, noLetters, minusAllowed));
}

void EngineGuiGlobalScreen::createButton(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, string textContent, Vec3 textColor, Vec3 textHoverColor)
{
	_buttons.push_back(make_shared<EngineGuiButton>(_fe3d, "globalscreen", ID, position, size, color, hoverColor, textContent, textColor, textHoverColor));
}

void EngineGuiGlobalScreen::createButton(const string& ID, Vec2 position, Vec2 size, const string& texturePath, Vec3 hoverColor)
{
	_buttons.push_back(make_shared<EngineGuiButton>(_fe3d, "globalscreen", ID, position, size, texturePath, hoverColor));
}

void EngineGuiGlobalScreen::createRectangle(const string& ID, Vec2 position, Vec2 size, Vec3 color)
{
	_rectangles.push_back(make_shared<EngineGuiRectangle>(_fe3d, "globalscreen", ID, position, size, color));
}

void EngineGuiGlobalScreen::createRectangle(const string& ID, Vec2 position, Vec2 size, const string& texturePath)
{
	_rectangles.push_back(make_shared<EngineGuiRectangle>(_fe3d, "globalscreen", ID, position, size, texturePath));
}

void EngineGuiGlobalScreen::createTextField(const string& ID, Vec2 position, Vec2 size, string textContent, Vec3 textColor, bool isCentered)
{
	_textFields.push_back(make_shared<EngineGuiTextField>(_fe3d, "globalscreen", ID, position, size, textContent, textColor, isCentered));
}

bool EngineGuiGlobalScreen::isScrollingListExisting(const string& ID)
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

bool EngineGuiGlobalScreen::isWriteFieldExisting(const string& ID)
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

bool EngineGuiGlobalScreen::isButtonExisting(const string& ID)
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

bool EngineGuiGlobalScreen::isRectangleExisting(const string& ID)
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

bool EngineGuiGlobalScreen::isTextFieldExisting(const string& ID)
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

shared_ptr<EngineGuiScrollingList> EngineGuiGlobalScreen::getScrollingList(const string& ID)
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
	Logger::throwError("EngineGuiGlobalScreen::getScrollingList");
}

shared_ptr<EngineGuiWriteField> EngineGuiGlobalScreen::getWriteField(const string& ID)
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
	Logger::throwError("EngineGuiGlobalScreen::getWriteField");
}

shared_ptr<EngineGuiButton> EngineGuiGlobalScreen::getButton(const string& ID)
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
	Logger::throwError("EngineGuiGlobalScreen::getButton");
}

shared_ptr<EngineGuiRectangle> EngineGuiGlobalScreen::getRectangle(const string& ID)
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
	Logger::throwError("EngineGuiGlobalScreen::getRectangle");
}

shared_ptr<EngineGuiTextField> EngineGuiGlobalScreen::getTextField(const string& ID)
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
	Logger::throwError("EngineGuiGlobalScreen::getTextField");
}

const vector<shared_ptr<EngineGuiScrollingList>>& EngineGuiGlobalScreen::getScrollingLists()
{
	return _scrollingLists;
}

const vector<shared_ptr<EngineGuiWriteField>>& EngineGuiGlobalScreen::getWriteFields()
{
	return _writeFields;
}

const vector<shared_ptr<EngineGuiButton>>& EngineGuiGlobalScreen::getButtons()
{
	return _buttons;
}

const vector<shared_ptr<EngineGuiRectangle>>& EngineGuiGlobalScreen::getRectangles()
{
	return _rectangles;
}

const vector<shared_ptr<EngineGuiTextField>>& EngineGuiGlobalScreen::getTextFields()
{
	return _textFields;
}

void EngineGuiGlobalScreen::deleteScrollingList(const string& ID)
{
	// Delete scrolling list
	for (size_t i = 0; i < _scrollingLists.size(); i++)
	{
		if (ID == _scrollingLists[i]->getID())
		{
			_scrollingLists.erase(_scrollingLists.begin() + i);
			return;
		}
	}

	// Error
	Logger::throwError("EngineGuiGlobalScreen::deleteScrollingList");
}

void EngineGuiGlobalScreen::deleteWriteField(const string& ID)
{
	// Delete write field
	for (size_t i = 0; i < _writeFields.size(); i++)
	{
		if (ID == _writeFields[i]->getID())
		{
			_writeFields.erase(_writeFields.begin() + i);
			return;
		}
	}

	// Error
	Logger::throwError("EngineGuiGlobalScreen::deleteWriteField");
}

void EngineGuiGlobalScreen::deleteButton(const string& ID)
{
	// Delete button
	for (size_t i = 0; i < _buttons.size(); i++)
	{
		if (ID == _buttons[i]->getID())
		{
			_buttons.erase(_buttons.begin() + i);
			return;
		}
	}

	// Error
	Logger::throwError("EngineGuiGlobalScreen::deleteButton");
}

void EngineGuiGlobalScreen::deleteRectangle(const string& ID)
{
	// Delete rectangle
	for (size_t i = 0; i < _rectangles.size(); i++)
	{
		if (ID == _rectangles[i]->getID())
		{
			_rectangles.erase(_rectangles.begin() + i);
			return;
		}
	}

	// Error
	Logger::throwError("EngineGuiGlobalScreen::deleteRectangle");
}

void EngineGuiGlobalScreen::deleteTextField(const string& ID)
{
	// Delete text field
	for (size_t i = 0; i < _textFields.size(); i++)
	{
		if (ID == _textFields[i]->getID())
		{
			_textFields.erase(_textFields.begin() + i);
			return;
		}
	}

	// Error
	Logger::throwError("EngineGuiGlobalScreen::deleteTextField");
}