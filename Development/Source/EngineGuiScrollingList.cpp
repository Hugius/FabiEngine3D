#include "EngineGuiScrollingList.hpp"

EngineGuiScrollingList::EngineGuiScrollingList(
	FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color,
	vec3 buttonColor, vec3 buttonHoverColor, vec3 textColor, vec3 textHoverColor, float charWidth) :
	EngineGuiRectangle(fe3d, parentID, ID, position, size, color),
	_buttonColor(buttonColor),
	_buttonHoverColor(buttonHoverColor),
	_textColor(textColor),
	_textHoverColor(textHoverColor),
	_charWidth(charWidth)
{

}

void EngineGuiScrollingList::update(float delta, bool hoverable)
{
	_delta = delta;

	_updateScolling();
	_updateButtons(hoverable);
}

void EngineGuiScrollingList::addButton(const string& ID, string textContent)
{
	vec4 dimensions = _convertDimensions(vec2(0.0f, 0.9f - (_buttons.size() * 0.15f)), vec2(_charWidth * textContent.size(), 0.1f));
	_buttons.push_back(make_shared<EngineGuiButton>(_fe3d, _ID, ID, vec2(dimensions.x, dimensions.y), vec2(dimensions.z, dimensions.w), _buttonColor, _buttonHoverColor, textContent, _textColor, _textHoverColor));
}

void EngineGuiScrollingList::deleteButton(const string& ID)
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

void EngineGuiScrollingList::show()
{
	EngineGuiRectangle::show();

	// Show all buttons
	for (auto& button : _buttons)
	{
		button->show();
	}
}

void EngineGuiScrollingList::hide()
{
	EngineGuiRectangle::hide();

	// Hide all buttons
	for (auto& button : _buttons)
	{
		button->hide();
	}
}

bool EngineGuiScrollingList::isHovered()
{
	return _isHovered;
}

const string& EngineGuiScrollingList::getHoveredButtonID()
{
	return _hoveredButtonID;
}

void EngineGuiScrollingList::_updateHovering()
{
	// Convert dimensions to same space
	vec2 mousePos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getMousePos()));
	vec2 listPos = _fe3d.guiEntity_getPosition(_entityID);
	vec2 listSize = _fe3d.guiEntity_getSize(_entityID);

	// Check if cursor inside button
	if (mousePos.x > listPos.x - (listSize.x / 2.0f) && mousePos.x < listPos.x + (listSize.x / 2.0f)) // X axis
	{
		if (mousePos.y > listPos.y - (listSize.y / 2.0f) && mousePos.y < listPos.y + (listSize.y / 2.0f)) // Y axis
		{
			_isHovered = true;
		}
	}
}

void EngineGuiScrollingList::_updateButtons(bool hoverable)
{
	// Update buttons
	for (auto& button : _buttons)
	{
		button->update(_delta, hoverable);

		// Set hovered button ID
		if (button->isHovered())
		{
			_hoveredButtonID = button->getID();
		}
	}
}

void EngineGuiScrollingList::_updateScolling()
{
	if (_fe3d.input_getMouseWheelY() != 0)
	{

	}

	// Update
}

vec4 EngineGuiScrollingList::_convertDimensions(vec2 position, vec2 size)
{
	vec2 listPosition = _fe3d.guiEntity_getPosition(_entityID);
	vec2 listSize = _fe3d.guiEntity_getSize(_entityID);
	vec2 buttonPosition = listPosition + (position * (listSize / 2.0f));
	vec2 buttonSize = (size / 2.0f) * listSize;

	return vec4(buttonPosition, buttonSize);
}