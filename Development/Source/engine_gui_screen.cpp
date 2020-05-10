#include "engine_gui_screen.hpp"

EngineGuiScreen::EngineGuiScreen(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size) :
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_parentPosition(position),
	_parentSize(size)
{

}

void EngineGuiScreen::update(float delta, bool hoverable)
{
	// Check if screen is active
	if (_isActive)
	{
		// Scrolling lists show
		for (auto& scrollingList : _scrollingLists)
		{
			scrollingList->show();
		}

		// WriteFields show
		for (auto& writefield : _writeFields)
		{
			writefield->show();
		}

		// Buttons show
		for (auto& button : _buttons)
		{
			button->show();
		}

		// Rectangles show
		for (auto& rectangle : _rectangles)
		{
			rectangle->show();
		}

		// Textfields show
		for (auto& textfield : _textfields)
		{
			textfield->show();
		}
	}
	else
	{
		// Scrolling lists hide
		for (auto& scrollingList : _scrollingLists)
		{
			scrollingList->hide();
		}

		// WriteFields hide
		for (auto& writefield : _writeFields)
		{
			writefield->hide();
		}

		// Buttons hide
		for (auto& button : _buttons)
		{
			button->hide();
		}

		// Rectangles hide
		for (auto& rectangle : _rectangles)
		{
			rectangle->hide();
		}

		// Textfields hide
		for (auto& textfield : _textfields)
		{
			textfield->hide();
		}
	}

	// Update scrolling lists
	for (auto& scrollingList : _scrollingLists)
	{
		scrollingList->update(delta, hoverable);
	}

	// Update writefields
	for (auto& writefield : _writeFields)
	{
		writefield->update(delta, hoverable);
	}

	// Update buttons
	for (auto& button : _buttons)
	{
		button->update(delta, hoverable);
	}
}

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

void EngineGuiScreen::addScrollingList(const string& ID, vec2 position, vec2 size, vec3 color,
	vec3 buttonColor, vec3 buttonHoverColor, vec3 textColor, vec3 textHoverColor, vec2 charSize)
{
	auto dimensions = _convertDimensions(position, size);
	_scrollingLists.push_back(make_shared<EngineGuiScrollingList>(_fe3d, _ID, ID, vec2(dimensions.x, dimensions.y), vec2(dimensions.z, dimensions.w), color, buttonColor, buttonHoverColor, textColor, textHoverColor, charSize));
}

void EngineGuiScreen::addWriteField(const string& ID, vec2 position, vec2 size, vec3 color, vec3 hoverColor, vec3 textColor, vec3 textHoverColor, 
	bool noNumbers, bool noCaps, bool noSpecials, bool noLetters)
{
	auto dimensions = _convertDimensions(position, size);
	_writeFields.push_back(make_shared<EngineGuiWriteField>(_fe3d, _ID, ID, vec2(dimensions.x, dimensions.y), vec2(dimensions.z, dimensions.w), color, hoverColor, textColor, textHoverColor, noNumbers, noCaps, noSpecials, noLetters));
}

void EngineGuiScreen::addButton(const string& ID, vec2 position, vec2 size, vec3 color, vec3 hoverColor, string textContent, vec3 textColor, vec3 textHoverColor)
{
	auto dimensions = _convertDimensions(position, size);
	_buttons.push_back(make_shared<EngineGuiButton>(_fe3d, _ID, ID, vec2(dimensions.x, dimensions.y), vec2(dimensions.z, dimensions.w), color, hoverColor, textContent, textColor, textHoverColor));
}

void EngineGuiScreen::addRectangle(const string& ID, vec2 position, vec2 size, vec3 color)
{
	auto dimensions = _convertDimensions(position, size);
	_rectangles.push_back(make_shared<EngineGuiRectangle>(_fe3d, _ID, ID, vec2(dimensions.x, dimensions.y), vec2(dimensions.z, dimensions.w), color));
}

void EngineGuiScreen::addTextfield(const string& ID, vec2 position, vec2 size, string textContent, vec3 textColor)
{
	auto dimensions = _convertDimensions(position, size);
	_textfields.push_back(make_shared<EngineGuiTextfield>(_fe3d, _ID, ID, vec2(dimensions.x, dimensions.y), vec2(dimensions.z, dimensions.w), textContent, textColor));
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

void EngineGuiScreen::deleteScrollingList(const string& ID)
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

void EngineGuiScreen::deleteWriteField(const string& ID)
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

void EngineGuiScreen::deleteButton(const string& ID)
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

void EngineGuiScreen::deleteRectangle(const string& ID)
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

void EngineGuiScreen::deleteTextfield(const string& ID)
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

vec4 EngineGuiScreen::_convertDimensions(vec2 position, vec2 size)
{
	vec2 screenPosition = _parentPosition;
	vec2 screenSize = _parentSize;
	vec2 buttonPosition = screenPosition + (position * (screenSize / 2.0f));
	vec2 buttonSize = (size / 2.0f) * screenSize;

	return vec4(buttonPosition, buttonSize);
}