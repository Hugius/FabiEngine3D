#pragma once

#include "engine_interface.hpp"
#include "gui_screen.hpp"

class GuiWindow final
{
public:
	GuiWindow(shared_ptr<EngineInterface> fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size, const fvec3& color);
	~GuiWindow();

	void createScreen(const string& ID);
	void deleteScreen(const string& ID);
	void setActiveScreen(const string& ID);
	void update(bool isHoverable);

	const string& getID() const;
	const string& getEntityID() const;
	const string& getParentID() const;

	const fvec3& getInitialColor() const;

	const fvec2 getInitialPosition() const;
	const fvec2 getInitialSize() const;

	const bool isHovered() const;

	const vector<shared_ptr<GuiScreen>>& getScreens() const;
	shared_ptr<GuiScreen> getScreen(const string& ID) const;
	shared_ptr<GuiScreen> getActiveScreen() const;

private:
	const string _ID;
	const string _entityID;
	const string _parentID;
	string _activeScreenID = "";

	const fvec3 _initialColor;

	const fvec2 _initialPosition;
	const fvec2 _initialSize;

	vector<shared_ptr<GuiScreen>> _screens;

	shared_ptr<EngineInterface> _fe3d = nullptr;
};