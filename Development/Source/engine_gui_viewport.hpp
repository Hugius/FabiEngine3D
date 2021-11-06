#pragma once

#include "fe3d.hpp"
#include "engine_gui_window.hpp"

class EngineGuiViewport final
{
public:
	EngineGuiViewport(FabiEngine3D& fe3d, const string& ID, Vec2 position, Vec2 size, Vec3 color);
	~EngineGuiViewport();

	// Voids
	void update(bool hoverable);
	void createWindow(const string& ID, Vec2 position, Vec2 size, Vec3 color);
	void deleteWindow(const string& ID);

	// Strings
	const string& getID();
	const string& getEntityID();

	// Booleans
	bool isHovered();

	// Miscellaneous
	vector<shared_ptr<EngineGuiWindow>>& getWindows();
	shared_ptr<EngineGuiWindow> getWindow(const string& ID);

private:
	// Strings
	const string _ID;
	const string _entityID;

	// Miscellaneous
	vector<shared_ptr<EngineGuiWindow>> _windows;
	FabiEngine3D& _fe3d;
};