#pragma once

#include "fe3d.hpp"
#include "engine_gui_screen.hpp"

class EngineGuiWindow final
{
public:
	EngineGuiWindow(FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color);
	~EngineGuiWindow();

	// Voids
	void createScreen(const string& ID);
	void deleteScreen(const string& ID);
	void setActiveScreen(const string& ID);
	void update(bool hoverable);

	// Strings
	const string& getID() const;
	const string& getEntityID() const;
	const string& getParentID() const;

	// Vectors
	const Vec2 getInitialPosition() const;
	const Vec2 getInitialSize() const;

	// Booleans
	const bool isHovered() const;

	// Miscellaneous
	const vector<shared_ptr<EngineGuiScreen>>& getScreens() const;
	shared_ptr<EngineGuiScreen> getScreen(const string& ID) const;
	shared_ptr<EngineGuiScreen> getActiveScreen() const;

private:
	// Strings
	const string _ID;
	const string _entityID;
	const string _parentID;
	string _activeScreenID = "";

	// Vectors
	const Vec2 _initialPosition;
	const Vec2 _initialSize;

	// Miscellaneous
	vector<shared_ptr<EngineGuiScreen>> _screens;
	FabiEngine3D& _fe3d;
};