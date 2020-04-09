#pragma once

#include "FabiEngine3D.hpp"
#include "EngineGuiWindow.hpp"

class EngineGuiViewport
{
public:
	EngineGuiViewport(FabiEngine3D& fe3d, const string& ID, vec2 position, vec2 size);

	void update();

	const string& getID();
	const string& getParentID();

	void setParentID(const string& ID);
	void addWindow(const string& ID, vec2 position, vec2 size);
	
	vector<EngineGuiWindow>& getWindows();

	EngineGuiWindow& getWindow(const string& ID);

private:
	FabiEngine3D& _fe3d;

	string _ID = "";
	string _parentID = "";

	vector<EngineGuiWindow> _windows;
};