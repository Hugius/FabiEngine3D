#pragma once

#include "engine_interface.hpp"
#include "gui_screen.hpp"

class GuiWindow final
{
public:
	GuiWindow(shared_ptr<EngineInterface> fe3d, const string& id, const string& parentId, const fvec2& position, const fvec2& size, const fvec3& color);
	~GuiWindow();

	void update(bool isFocused);
	void createScreen(const string& id);
	void deleteScreen(const string& id);
	void deleteScreens();
	void setActiveScreen(const string& id);

	const unordered_map<string, shared_ptr<GuiScreen>>& getScreens() const;

	const shared_ptr<GuiScreen> getScreen(const string& id) const;
	const shared_ptr<GuiScreen> getActiveScreen() const;

	const string& getId() const;
	const string& getParentId() const;

	const fvec3& getColor() const;

	const fvec2& getPosition() const;
	const fvec2& getSize() const;

	const bool hasScreen(const string& id) const;
	const bool isHovered() const;

private:
	void _updateHovering();

	const string _id;
	const string _parentId;
	const string _entityId;

	unordered_map<string, shared_ptr<GuiScreen>> _screens = {};

	shared_ptr<EngineInterface> _fe3d = nullptr;

	string _activeScreenId = "";

	bool _isHovered = false;
};