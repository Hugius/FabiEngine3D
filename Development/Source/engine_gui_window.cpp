#include "engine_gui_window.hpp"

EngineGuiWindow::EngineGuiWindow(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color) :
	_fe3d(fe3d),
	_ID(ID),
	_entityID("@" + parentID + "_" + ID),
	_parentID(parentID),
	_originalPosition(position),
	_originalSize(size)
{
	fe3d.guiEntity_add(_entityID, color, position, 0.0f, size, true);
}

void EngineGuiWindow::update(bool hoverable)
{
	for (auto& screen : _screens)
	{
		screen->update(hoverable);
	}
}

bool EngineGuiWindow::isHovered()
{
	// Check if entity is visible anyway
	if (_fe3d.guiEntity_isVisible(_entityID))
	{
		// Convert dimensions to same space
		Vec2 mousePos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPosition()));
		Vec2 buttonPos = _fe3d.guiEntity_getPosition(_entityID);
		Vec2 buttonSize = _fe3d.guiEntity_getSize(_entityID);

		// Check if cursor inside entity
		if (mousePos.x > buttonPos.x - (buttonSize.x / 2.0f) && mousePos.x < buttonPos.x + (buttonSize.x / 2.0f)) // X axis
		{
			if (mousePos.y > buttonPos.y - (buttonSize.y / 2.0f) && mousePos.y < buttonPos.y + (buttonSize.y / 2.0f)) // Y axis
			{
				return true;
			}
		}
	}

	return false;
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

const Vec2 EngineGuiWindow::getOriginalPosition()
{
	return _originalPosition;
}

const Vec2 EngineGuiWindow::getOriginalSize()
{
	return _originalSize;
}

void EngineGuiWindow::addScreen(const string& ID)
{
	// Check if already exists
	for (auto& screen : _screens)
	{
		if (screen->getID() == ID)
		{
			_fe3d.logger_throwError("Screen creation: screen \"" + ID + "\" already exists!");
		}
	}

	// Add new screen
	Vec2 windowPosition = _fe3d.guiEntity_getPosition(_entityID);
	Vec2 windowSize = _fe3d.guiEntity_getSize(_entityID);
	_screens.push_back(make_shared<EngineGuiScreen>(_fe3d, _parentID + "_" + _ID, ID, windowPosition, windowSize));
	getScreen(ID)->hide();
}

void EngineGuiWindow::setActiveScreen(const string& ID)
{
	// Hide old active screen if possible
	if (_activeScreenID != "")
	{
		getActiveScreen()->hide();
	}

	// Show new active screen
	_activeScreenID = ID;
	getActiveScreen()->show();
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