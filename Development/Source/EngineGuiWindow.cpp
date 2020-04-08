#include "EngineGuiWindow.hpp"

EngineGuiWindow::EngineGuiWindow(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size) :
	FE3D(fe3d),
	_parentID(parentID),
	_ID(ID)
{
	fe3d.guiEntity_add(ID, "window.png", position, 0.0f, size, false);
}

const string& EngineGuiWindow::getID()
{
	return _ID;
}

const string& EngineGuiWindow::getParentID()
{
	return _parentID;
}

void EngineGuiWindow::addScreen(const string& ID, vec2 position, vec2 size)
{
	vec2 windowPosition = FE3D.guiEntity_getPosition(_ID);
	vec2 windowSize = FE3D.guiEntity_getSize(_ID);
	vec2 screenPosition = windowPosition + (FE3D.misc_convertFromNDC(position) * windowSize);
	vec2 screenSize = size * windowSize;
	_screens.push_back(EngineGuiScreen(FE3D, ID, screenPosition, screenSize));
}

vector<EngineGuiScreen>& EngineGuiWindow::getScreens()
{
	return _screens;
}

EngineGuiScreen& EngineGuiWindow::getScreen(const string& ID)
{
	for (auto& screen : _screens)
	{
		if (ID == screen.getID())
		{
			return screen;
		}
	}

	FE3D.logger_throwError("GUI screen requested: \"" + ID + "\" not found in window \"" + _ID + "\"");
}