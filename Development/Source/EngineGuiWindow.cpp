#include "EngineGuiWindow.hpp"

EngineGuiWindow::EngineGuiWindow(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size) :
	_fe3d(fe3d),
	_ID(ID),
	_entityID(parentID + "_" + ID),
	_parentID(parentID)
{
	fe3d.guiEntity_add(_entityID, vec3(0.5f), position, 0.0f, size, false);
}

void EngineGuiWindow::update()
{
	for (auto& screen : _screens)
	{
		screen.update();
	}
}

const string& EngineGuiWindow::getID()
{
	return _ID;
}

const string& EngineGuiWindow::getEntityID()
{
	return _entityID;
}

const string& EngineGuiWindow::getParentID()
{
	return _parentID;
}

void EngineGuiWindow::addScreen(const string& ID, bool active)
{
	vec2 windowPosition = _fe3d.guiEntity_getPosition(_entityID);
	vec2 windowSize = _fe3d.guiEntity_getSize(_entityID);
	_screens.push_back(EngineGuiScreen(_fe3d, _ID, ID, windowPosition, windowSize));

	// Set as active screen
	if (active)
	{
		_activeScreenID = ID;
	}
}

void EngineGuiWindow::setActiveScreen(const string& ID)
{
	_activeScreenID = ID;
}

vector<EngineGuiScreen>& EngineGuiWindow::getScreens()
{
	return _screens;
}

EngineGuiScreen& EngineGuiWindow::getActiveScreen()
{
	return getScreen(_activeScreenID);
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

	_fe3d.logger_throwError("GUI screen requested: \"" + ID + "\" not found in window \"" + _ID + "\"");
}