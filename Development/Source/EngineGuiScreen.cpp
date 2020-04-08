#include "EngineGuiScreen.hpp"

EngineGuiScreen::EngineGuiScreen(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size) :
	FE3D(fe3d),
	_parentID(parentID),
	_ID(ID)
{
	fe3d.guiEntity_add(ID, "screen.png", position, 0.0f, size, false);
}

const string& EngineGuiScreen::getID()
{
	return _ID;
}

const string& EngineGuiScreen::getParentID()
{
	return _parentID;
}

void EngineGuiScreen::addButton(const string& ID, vec2 position, vec2 size)
{
	vec2 screenPosition = FE3D.guiEntity_getPosition(_ID);
	vec2 screenSize = FE3D.guiEntity_getSize(_ID);
	vec2 buttonPosition = screenPosition + (FE3D.misc_convertFromNDC(position) * screenSize);
	vec2 buttonSize = size * screenSize;
	_buttons.push_back(EngineGuiButton(FE3D, ID, buttonPosition, buttonSize));
}

vector<EngineGuiButton>& EngineGuiScreen::getButtons()
{
	return _buttons;
}