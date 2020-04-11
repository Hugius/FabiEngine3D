#include "EngineGuiWindow.hpp"

EngineGuiWindow::EngineGuiWindow(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size, vec3 color) :
	_fe3d(fe3d),
	_ID(ID),
	_entityID(parentID + "_" + ID),
	_parentID(parentID)
{
	fe3d.guiEntity_add(_entityID, color, position, 0.0f, size, true);
}

void EngineGuiWindow::update(float delta, bool hoverable)
{
	for (auto& screen : _screens)
	{
		screen->update(delta, hoverable);
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

void EngineGuiWindow::addScreen(const string& ID)
{
	vec2 windowPosition = _fe3d.guiEntity_getPosition(_entityID);
	vec2 windowSize = _fe3d.guiEntity_getSize(_entityID);
	_screens.push_back(make_shared<EngineGuiScreen>(_fe3d, _ID, ID, windowPosition, windowSize));
}

void EngineGuiWindow::setActiveScreen(const string& ID)
{
	_activeScreenID = ID;
}

vector<shared_ptr<EngineGuiScreen>>& EngineGuiWindow::getScreens()
{
	return _screens;
}

shared_ptr<EngineGuiScreen> EngineGuiWindow::getActiveScreen()
{
	return getScreen(_activeScreenID);
}

shared_ptr<EngineGuiScreen> EngineGuiWindow::getScreen(const string& ID)
{
	for (auto& screen : _screens)
	{
		if (ID == screen->getID())
		{
			return screen;
		}
	}

	return nullptr;
}