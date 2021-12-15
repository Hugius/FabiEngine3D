#pragma once

#include "fe3d.hpp"
#include "gui_window.hpp"

class GuiViewport final
{
public:
	GuiViewport(FabiEngine3D& fe3d, const string& ID, fvec2 position, fvec2 size, fvec3 color);
	~GuiViewport();

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
	const vector<shared_ptr<GuiWindow>>& getWindows() const;
	shared_ptr<GuiWindow> getWindow(const string& ID) const;

private:
	// STRING
	const string _ID;
	const string _entityID;

	// MISCELLANEOUS
	vector<shared_ptr<GuiWindow>> _windows;
	FabiEngine3D& _fe3d;
};