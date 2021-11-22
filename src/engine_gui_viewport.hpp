#pragma once

#include "fe3d.hpp"
#include "engine_gui_window.hpp"

class EngineGuiViewport final
{
public:
	EngineGuiViewport(FabiEngine3D& fe3d, const string& ID, fvec2 position, fvec2 size, fvec3 color);
	~EngineGuiViewport();

	// VOID
	void update(bool hoverable);
	void createWindow(const string& ID, fvec2 position, fvec2 size, fvec3 color);
	void deleteWindow(const string& ID);

	// STRING
	const string& getID();
	const string& getEntityID();

	// BOOL
	const bool isHovered() const;

	// MISCELLANEOUS
	const vector<shared_ptr<EngineGuiWindow>>& getWindows() const;
	shared_ptr<EngineGuiWindow> getWindow(const string& ID) const;

private:
	// STRING
	const string _ID;
	const string _entityID;

	// MISCELLANEOUS
	vector<shared_ptr<EngineGuiWindow>> _windows;
	FabiEngine3D& _fe3d;
};