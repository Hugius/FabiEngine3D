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
		INPUT_MOUSE_NAMES,
		INPUT_METHODS
	};

	struct ChoiceList final
	{
		ChoiceList(ChoiceListType typ, int tot) : type(typ), total(tot)
		{

		}

		const ChoiceListType type;

		const int total;

		int selected = -1;
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
	void _updateGUI();
	void _updateChoiceLists();
	void _updateNavigation();
	void _updateMiscellaneous();
	void _generateScriptLineInterface(ScriptLine& scriptLine);
	void _addChoiceList(ChoiceListType list);
	void _removeChoiceList();

	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui;
	shared_ptr<EngineGuiWindow> _leftWindow;
	shared_ptr<EngineGuiWindow> _rightWindow;
	Script _script;

	string _currentProjectName = "";
	string _currentScriptLineID = "";

	vector<ChoiceList> _choiceListStack;
	vector<string> _eventTypeNames;
	vector<string> _inputTypeNames;
	vector<string> _inputKeyNames;
	vector<string> _inputMouseNames;
	vector<string> _inputMethodNames;

	float _scrollingAcceleration = 0.0f;
	const float _maxScrollingAcceleration = 0.3f;
	const float _optionBillboardHeight = 0.75f;

	shared_ptr<ScriptEvent> _currentEventToAdd;
	bool _isCreatingScript = false;
	bool _isLoaded = false;
};