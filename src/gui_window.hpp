#pragma once

#include "engine_interface.hpp"
#include "gui_screen.hpp"

class GuiWindow final
{
public:
	GuiWindow(shared_ptr<EngineInterface> fe3d, const string & id, const string & parentId, const fvec2 & position, const fvec2 & size, const fvec3 & color);
	~GuiWindow();

	void update(bool isInteractable);
	void createScreen(const string & screenId);
	void deleteScreen(const string & screenId);
	void deleteScreens();
	void setActiveScreen(const string & screenId);

	const unordered_map<string, shared_ptr<GuiScreen>> & getScreens() const;

	const shared_ptr<GuiScreen> getScreen(const string & screenId) const;
	const shared_ptr<GuiScreen> getActiveScreen() const;

	const string & getId() const;
	const string & getParentId() const;

	const fvec3 & getColor() const;

	const fvec2 & getPosition() const;
	const fvec2 & getSize() const;

	const bool hasScreen(const string & screenId) const;
	const bool isHovered() const;

private:
	void _updateHovering(bool isInteractable);

	const string _id;
	const string _parentId;
	const string _quad2dId;

	unordered_map<string, shared_ptr<GuiScreen>> _screens = {};

	shared_ptr<EngineInterface> _fe3d = nullptr;

	string _activeScreenId = "";

	bool _isHovered = false;
};