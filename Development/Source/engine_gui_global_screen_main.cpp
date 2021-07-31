#include "engine_gui_global_screen.hpp"
#include "logger.hpp"

EngineGuiGlobalScreen::EngineGuiGlobalScreen(FabiEngine3D& fe3d) :
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

	// Update writefields
	for (const auto& writefield : _writefields)
	{
		writefield->update(true);
	}

	// Update buttons
	for (const auto& button : _buttons)
	{
		button->update(true);
	}

	// Miscellaneous
	_updateValueFilling();
}

void EngineGuiGlobalScreen::createScrollingList(const string& ID, Vec2 position, Vec2 size, Vec3 color,
	Vec3 buttonColor, Vec3 buttonHoverColor, Vec3 textColor, Vec3 textHoverColor, Vec2 charSize)
{
	_scrollingLists.push_back(make_shared<EngineGuiScrollingList>(_fe3d, "globalscreen", ID, position, size, color, buttonColor, buttonHoverColor, textColor, textHoverColor, charSize));
}

void EngineGuiGlobalScreen::createWritefield(const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor, Vec3 textColor, Vec3 textHoverColor, 
	bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed)
{
	_writefields.push_back(make_shared<EngineGuiWritefield>(_fe3d, "globalscreen", ID, position, size, color, hoverColor, textColor, textHoverColor, noNumbers, noCaps, noSpecials, noLetters, minusAllowed));
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

void EngineGuiGlobalScreen::createTextfield(const string& ID, Vec2 position, Vec2 size, string textContent, Vec3 textColor, bool isCentered)
{
	_textfields.push_back(make_shared<EngineGuiTextfield>(_fe3d, "globalscreen", ID, position, size, textContent, textColor, isCentered));
}

bool EngineGuiGlobalScreen::checkScrollingList(const string& ID)
{
	return getScrollingList(ID) != nullptr;
}

bool EngineGuiGlobalScreen::checkWritefield(const string& ID)
{
	return getWritefield(ID) != nullptr;
}

bool EngineGuiGlobalScreen::checkButton(const string& ID)
{
	return getButton(ID) != nullptr;
}

bool EngineGuiGlobalScreen::checkRectangle(const string& ID)
{
	return getRectangle(ID) != nullptr;
}

bool EngineGuiGlobalScreen::checkTextfield(const string& ID)
{
	return getTextfield(ID) != nullptr;
}

shared_ptr<EngineGuiScrollingList> EngineGuiGlobalScreen::getScrollingList(const string& ID)
{
	for (const auto& scrollingList : _scrollingLists)
	{
		if (ID == scrollingList->getID())
		{
			return scrollingList;
		}
	}

	return nullptr;
}

shared_ptr<EngineGuiWritefield> EngineGuiGlobalScreen::getWritefield(const string& ID)
{
	for (const auto& writefield : _writefields)
	{
		if (ID == writefield->getID())
		{
			return writefield;
		}
	}

	return nullptr;
}

shared_ptr<EngineGuiButton> EngineGuiGlobalScreen::getButton(const string& ID)
{
	for (const auto& button : _buttons)
	{
		if (ID == button->getID())
		{
			return button;
		}
	}

	return nullptr;
}

shared_ptr<EngineGuiRectangle> EngineGuiGlobalScreen::getRectangle(const string& ID)
{
	for (const auto& rectangle : _rectangles)
	{
		if (ID == rectangle->getID())
		{
			return rectangle;
		}
	}

	return nullptr;
}

shared_ptr<EngineGuiTextfield> EngineGuiGlobalScreen::getTextfield(const string& ID)
{
	for (const auto& textfield : _textfields)
	{
		if (ID == textfield->getID())
		{
			return textfield;
		}
	}

	return nullptr;
}

vector<shared_ptr<EngineGuiScrollingList>>& EngineGuiGlobalScreen::getScrollingLists()
{
	return _scrollingLists;
}

vector<shared_ptr<EngineGuiWritefield>>& EngineGuiGlobalScreen::getWritefields()
{
	return _writefields;
}

vector<shared_ptr<EngineGuiButton>>& EngineGuiGlobalScreen::getButtons()
{
	return _buttons;
}

vector<shared_ptr<EngineGuiRectangle>>& EngineGuiGlobalScreen::getRectangles()
{
	return _rectangles;
}

vector<shared_ptr<EngineGuiTextfield>>& EngineGuiGlobalScreen::getTextfields()
{
	return _textfields;
}

void EngineGuiGlobalScreen::deleteScrollingList(const string& ID)
{
	// Delete scrollingList
	for (size_t i = 0; i < _scrollingLists.size(); i++)
	{
		if (ID == _scrollingLists[i]->getID())
		{
			_scrollingLists.erase(_scrollingLists.begin() + i);
			return;
		}
	}

	// Error
	Logger::throwError("Cannot not delete scrollingList with ID \"" + ID + "\"!");
}

void EngineGuiGlobalScreen::deleteWritefield(const string& ID)
{
	// Delete writefield
	for (size_t i = 0; i < _writefields.size(); i++)
	{
		if (ID == _writefields[i]->getID())
		{
			_writefields.erase(_writefields.begin() + i);
			return;
		}
	}

	// Error
	Logger::throwError("Cannot not delete writefield with ID \"" + ID + "\"!");
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
	Logger::throwError("Cannot not delete button with ID \"" + ID + "\"!");
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
	Logger::throwError("Cannot not delete rectangle with ID \"" + ID + "\"!");
}

void EngineGuiGlobalScreen::deleteTextfield(const string& ID)
{
	// Delete textfield
	for (size_t i = 0; i < _textfields.size(); i++)
	{
		if (ID == _textfields[i]->getID())
		{
			_textfields.erase(_textfields.begin() + i);
			return;
		}
	}

	// Error
	Logger::throwError("Cannot not delete textfield with ID \"" + ID + "\"!");
}