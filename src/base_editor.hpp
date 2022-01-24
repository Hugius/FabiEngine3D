#pragma once

#include "engine_interface.hpp"
#include "gui_manager.hpp"

class BaseEditor
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void inject(shared_ptr<GuiManager> gui);

	virtual void setCurrentProjectId(const string& projectId) = 0;
	virtual void load() = 0;
	virtual void update() = 0;
	virtual void unload() = 0;

protected:
	virtual void _loadGUI() = 0;
	virtual void _unloadGUI() = 0;

	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<GuiManager> _gui = nullptr;

	bool _isEditorLoaded = false;
};