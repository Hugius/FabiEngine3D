#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_window.hpp"

class EngineGuiViewport final
{
public:
	EngineGuiViewport(FabiEngine3D& fe3d, const string& ID, Vec2 position, Vec2 size, Vec3 color);

	void update(bool hoverable);

	bool isHovered();

	const string& getID();

	void addWindow(const string& ID, Vec2 position, Vec2 size, Vec3 color);
	
	vector<shared_ptr<EngineGuiWindow>>& getWindows();

	shared_ptr<EngineGuiWindow> getWindow(const string& ID);

private:
	FabiEngine3D& _fe3d;

	string _ID = "";

	vector<shared_ptr<EngineGuiWindow>> _windows;
};