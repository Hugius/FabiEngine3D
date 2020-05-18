#include "engine_gui_global_screen.hpp"

EngineGuiGlobalScreen::EngineGuiGlobalScreen(FabiEngine3D& fe3d) :
	_fe3d(fe3d)
{

}

void EngineGuiGlobalScreen::update(float delta)
{
	// Update scrolling lists
	for (auto& scrollingList : _scrollingLists)
	{
		scrollingList->update(delta, true);
	}

	// Update writefields
	for (auto& writefield : _writeFields)
	{
		writefield->update(delta, true);
	}

	// Update buttons
	for (auto& button : _buttons)
	{
		button->update(delta, true);
	}
}

void EngineGuiGlobalScreen::addScrollingList(const string& ID, vec2 position, vec2 size, vec3 color,
	vec3 buttonColor, vec3 buttonHoverColor, vec3 textColor, vec3 textHoverColor, vec2 charSize)
{
	_scrollingLists.push_back(make_shared<EngineGuiScrollingList>(_fe3d, "globalScreen", ID, position, size, color, buttonColor, buttonHoverColor, textColor, textHoverColor, charSize));
}

void EngineGuiGlobalScreen::addWriteField(const string& ID, vec2 position, vec2 size, vec3 color, vec3 hoverColor, vec3 textColor, vec3 textHoverColor, 
	bool noNumbers, bool noCaps, bool noSpecials, bool noLetters)
{
	_writeFields.push_back(make_shared<EngineGuiWriteField>(_fe3d, "globalScreen", ID, position, size, color, hoverColor, textColor, textHoverColor, noNumbers, noCaps, noSpecials, noLetters));
}

void EngineGuiGlobalScreen::addButton(const string& ID, vec2 position, vec2 size, vec3 color, vec3 hoverColor, string textContent, vec3 textColor, vec3 textHoverColor)
{
	_buttons.push_back(make_shared<EngineGuiButton>(_fe3d, "globalScreen", ID, position, size, color, hoverColor, textContent, textColor, textHoverColor));
}

void EngineGuiGlobalScreen::addRectangle(const string& ID, vec2 position, vec2 size, vec3 color)
{
	_rectangles.push_back(make_shared<EngineGuiRectangle>(_fe3d, "globalScreen", ID, position, size, color));
}

void EngineGuiGlobalScreen::addTextfield(const string& ID, vec2 position, vec2 size, string textContent, vec3 textColor)
{
	_textfields.push_back(make_shared<EngineGuiTextfield>(_fe3d, "globalScreen", ID, position, size, textContent, textColor));
}

bool EngineGuiGlobalScreen::checkScrollingList(const string& ID)
{
	return getScrollingList(ID) != nullptr;
}

bool EngineGuiGlobalScreen::checkWriteField(const string& ID)
{
	return getWriteField(ID) != nullptr;
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
	for (auto& scrollingList : _scrollingLists)
	{
		if (ID == scrollingList->getID())
		{
			return scrollingList;
		}
	}

	return nullptr;
}

shared_ptr<EngineGuiWriteField> EngineGuiGlobalScreen::getWriteField(const string& ID)
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

shared_ptr<EngineGuiButton> EngineGuiGlobalScreen::getButton(const string& ID)
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

shared_ptr<EngineGuiRectangle> EngineGuiGlobalScreen::getRectangle(const string& ID)
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

shared_ptr<EngineGuiTextfield> EngineGuiGlobalScreen::getTextfield(const string& ID)
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

vector<shared_ptr<EngineGuiScrollingList>>& EngineGuiGlobalScreen::getScrollingLists()
{
	return _scrollingLists;
}

vector<shared_ptr<EngineGuiWriteField>>& EngineGuiGlobalScreen::getWriteFields()
{
	return _writeFields;
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
	_fe3d.logger_throwError("ScrollingList \"" + ID + "\" not deleted!");
}

void EngineGuiGlobalScreen::deleteWriteField(const string& ID)
{
	// Delete writefield
	for (size_t i = 0; i < _writeFields.size(); i++)
	{
		if (ID == _writeFields[i]->getID())
		{
			_writeFields.erase(_writeFields.begin() + i);
			return;
		}
	}

	// Error
	_fe3d.logger_throwError("WriteField \"" + ID + "\" not deleted!");
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
	_fe3d.logger_throwError("Button \"" + ID + "\" not deleted!");
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
	_fe3d.logger_throwError("Rectangle \"" + ID + "\" not deleted!");
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
	_fe3d.logger_throwError("Textfield \"" + ID + "\" not deleted!");
}