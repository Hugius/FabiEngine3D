#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "script.hpp"

class ScriptEditor final
{
	enum class ChoiceListType
	{
		EVENT_TYPES,

		INPUT_TYPES,
		INPUT_KEY_NAMES,
		INPUT_MOUSE_NAMES
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

	const Script& getScript();

private:
	void addChoiceList(ChoiceListType list);
	void removeChoiceList();

	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui;
	shared_ptr<EngineGuiWindow> _leftWindow;
	Script _script;

	string _currentProjectName = "";

	vector<std::pair<ChoiceListType, int>> _choiceListStack;
	vector<string> _eventTypeNames;
	vector<string> _inputTypeNames;
	vector<string> _inputKeyNames;
	vector<string> _inputMouseNames;

	float _scrollingAcceleration = 0.0f;
	const float _maxScrollingAcceleration = 0.3f;
	const float _optionBillboardHeight = 0.75f;

	bool _isLoaded = false;
};