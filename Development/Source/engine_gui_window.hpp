#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_screen.hpp"

class EngineGuiWindow final
{
public:
	EngineGuiWindow(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color);

	void addScreen(const string& ID);
	void setActiveScreen(const string& ID);
	void update(bool hoverable);

	bool isHovered();

	const string& getID();
	const string& getEntityID();
	const string& getParentID();

	const Vec2 getOriginalPosition();
	const Vec2 getOriginalSize();

	vector<shared_ptr<EngineGuiScreen>>& getScreens();

	shared_ptr<EngineGuiScreen> getActiveScreen();
	shared_ptr<EngineGuiScreen> getScreen(const string& ID);

private:
	FabiEngine3D& _fe3d;

	const string _ID;
	const string _entityID;
	const string _parentID;

	const Vec2 _originalPosition;
	const Vec2 _originalSize;

	string _activeScreenID = "";

	vector<shared_ptr<EngineGuiScreen>> _screens;
};