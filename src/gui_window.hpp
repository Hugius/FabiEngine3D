#pragma once

#include "engine_interface.hpp"
#include "gui_screen.hpp"

class GuiWindow final
{
public:
	GuiWindow(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size, const fvec3& color);
	~GuiWindow();

	void createScreen(const string& id);
	void deleteScreen(const string& id);
	void setActiveScreen(const string& id);
	void update(bool isHoverable);

	const vector<shared_ptr<GuiScreen>>& getScreens() const;

	const shared_ptr<GuiScreen> getScreen(const string& id) const;
	const shared_ptr<GuiScreen> getActiveScreen() const;

	const string& getId() const;
	const string& getEntityId() const;
	const string& getParentId() const;

	const fvec3& getInitialColor() const;

	const fvec2& getInitialPosition() const;
	const fvec2& getInitialSize() const;

	const bool isHovered() const;

private:
	const string _id;
	const string _entityId;
	const string _parentId;
	const fvec3 _initialColor;
	const fvec2 _initialPosition;
	const fvec2 _initialSize;

	vector<shared_ptr<GuiScreen>> _screens = {};

	shared_ptr<EngineInterface> _fe3d = nullptr;

	string _activeScreenId = "";
};