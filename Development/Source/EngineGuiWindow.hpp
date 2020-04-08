#pragma once

#include "FabiEngine3D.hpp"
#include "EngineGuiScreen.hpp"

class EngineGuiWindow
{
public:
	EngineGuiWindow(FabiEngine3D& fe3d, const string& parentID, const string& ID, vec2 position, vec2 size);

	const string& getID();
	const string& getParentID();

	void addScreen(const string& ID, vec2 position, vec2 size);

	vector<EngineGuiScreen>& getScreens();

	EngineGuiScreen& getScreen(const string& ID);

private:
	FabiEngine3D& FE3D;

	const string _ID;
	const string _parentID;

	vector<EngineGuiScreen> _screens;
};