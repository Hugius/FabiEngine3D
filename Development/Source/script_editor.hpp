#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class ScriptEditor final
{
	enum class Header
	{
		EVENT_CLASS,
		EVENT_TYPE,
		EVENT_NAME,
		ACTION_CLASS,
		ACTION_TYPE,
		ACTION_NAME,
		TOTAL
	};

public:
	ScriptEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui);
	~ScriptEditor() = default;

	void initializeGUI();
	void load();
	void save();
	void unload();
	void update();
	void setCurrentProjectName(const string & projectName);

	bool isLoaded();

private:
	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui;
	shared_ptr<EngineGuiWindow> _leftWindow;

	string _currentProjectName = "";

	bool _isLoaded = false;

	Header _currentHeader = Header::EVENT_CLASS;
};