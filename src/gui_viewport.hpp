#pragma once

#include "engine_interface.hpp"
#include "gui_window.hpp"

class GuiViewport final
{
public:
	GuiViewport(shared_ptr<EngineInterface> fe3d, const string& id, const fvec2& position, const fvec2& size, const fvec3& color);
	~GuiViewport();

	void update(bool isHoverable);
	void createWindow(const string& id, const fvec2& position, const fvec2& size, const fvec3& color);
	void deleteWindow(const string& id);

	const vector<shared_ptr<GuiWindow>>& getWindows() const;

	const shared_ptr<GuiWindow> getWindow(const string& id) const;

	const string& getId();
	const string& getEntityId();

	const fvec3& getInitialColor() const;

	const fvec2& getInitialPosition() const;
	const fvec2& getInitialSize() const;

	const bool isHovered() const;

private:
	const string _id;
	const string _entityId;
	const fvec3 _initialColor;
	const fvec2 _initialPosition;
	const fvec2 _initialSize;

	vector<shared_ptr<GuiWindow>> _windows = {};

	shared_ptr<EngineInterface> _fe3d = nullptr;
};