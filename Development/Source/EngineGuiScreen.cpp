#include "EngineGuiScreen.hpp"

EngineGuiScreen::EngineGuiScreen(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size) :
	_fe3d(fe3d),
	_ID(ID),
	_parentID(parentID),
	_parentPosition(position),
	_parentSize(size)
{

}

void EngineGuiScreen::update()
{
	// Update buttons
	for (auto& button : _buttons)
	{
		button.update();
		
		// Set hovered button ID
		if (button.isHovered())
		{
			_hoveredButtonID = button.getID();
		}
	}
}

const string& EngineGuiScreen::getID()
{
	return _ID;
}

const string& EngineGuiScreen::getParentID()
{
	return _parentID;
}

void EngineGuiScreen::addButton(const string& ID, vec2 position, vec2 size, vec3 color, string textContent, vec3 textColor)
{
	auto dimensions = _convertDimensions(position, size);
	_buttons.push_back(EngineGuiButton(_fe3d, _ID, ID, vec2(dimensions.x, dimensions.y), vec2(dimensions.z, dimensions.w), color, textContent, textColor));
}

void EngineGuiScreen::addRectangle(const string& ID, vec2 position, vec2 size, vec3 color)
{
	auto dimensions = _convertDimensions(position, size);
	_rectangles.push_back(EngineGuiRectangle(_fe3d, _ID, ID, vec2(dimensions.x, dimensions.y), vec2(dimensions.z, dimensions.w), color));
}

void EngineGuiScreen::addTextfield(const string& ID, vec2 position, vec2 size, string textContent, vec3 textColor)
{
	auto dimensions = _convertDimensions(position, size);
	_textfields.push_back(EngineGuiTextfield(_fe3d, _ID, ID, vec2(dimensions.x, dimensions.y), vec2(dimensions.z, dimensions.w), textContent, textColor));
}

vector<EngineGuiButton>& EngineGuiScreen::getButtons()
{
	return _buttons;
}

const string& EngineGuiScreen::getHoveredButtonID()
{
	return _hoveredButtonID;
}

vec4 EngineGuiScreen::_convertDimensions(vec2 position, vec2 size)
{
	vec2 screenPosition = _parentPosition;
	vec2 screenSize = _parentSize;
	vec2 buttonPosition = screenPosition + (_fe3d.misc_convertFromNDC(position) * screenSize);
	vec2 buttonSize = (size / 2.0f) * screenSize;

	return vec4(buttonPosition, buttonSize);
}

bool EngineGuiScreen::_isHovered(const string& ID)
{
	return false;
}
