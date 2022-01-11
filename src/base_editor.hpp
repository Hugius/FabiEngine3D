#pragma once

#include "engine_interface.hpp"
#include "gui_manager.hpp"

class BaseEditor
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void inject(shared_ptr<GuiManager> gui);

	virtual void setCurrentProjectID(const string& projectID) = 0;
	virtual void load() = 0;
	virtual void update() = 0;
	virtual void unload() = 0;

	virtual const bool isLoaded() const = 0;

protected:
	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<GuiManager> _gui = nullptr;
};