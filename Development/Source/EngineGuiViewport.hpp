#pragma once

#include "FabiEngine3D.hpp"
#include "EngineGuiWindow.hpp"

class EngineGuiViewport final
{
public:
	EngineGuiViewport(FabiEngine3D& fe3d, const string& ID, vec2 position, vec2 size);

	void update(float delta);

	const string& getID();

	void addWindow(const string& ID, vec2 position, vec2 size);
	
	vector<shared_ptr<EngineGuiWindow>>& getWindows();

	shared_ptr<EngineGuiWindow> getWindow(const string& ID);

private:
	FabiEngine3D& _fe3d;

	string _ID = "";

	vector<shared_ptr<EngineGuiWindow>> _windows;
};