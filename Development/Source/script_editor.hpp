#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "script.hpp"
#include "script_executor.hpp"
#include "script_event_initialization.hpp"
#include "script_event_input.hpp"
#include "script_event_time.hpp"
#include "script_event_collision.hpp"
#include "script_event_condition.hpp"
#include "script_action_camera.hpp"

class ScriptEditor final
{
	enum class ChoiceListSort
	{
		EVENT,
		ACTION,
		NONE
	};

	enum class ChoiceListType
	{
		// Types
		EVENT_TYPES,
		ACTION_TYPES,

		// Initialization eventt
		EVENT_INITIALIZATION,

		// Input event
		EVENT_INPUT_TYPES,
		EVENT_INPUT_KEY_NAMES,
		EVENT_INPUT_MOUSE_NAMES,
		EVENT_INPUT_METHODS,

		// Collision event

		// Time event
		

		// Condition event

		// Camera actions
		ACTION_CAMERA_TYPES,
		ACTION_CAMERA_DIRECTIONS,
		ACTION_CAMERA_METHODS,

		NONE
	};

	struct ChoiceList final
	{
		ChoiceList(ChoiceListSort listSort, ChoiceListType listType, int optionTotal) : sort(listSort), type(listType), total(optionTotal)
		{

		}

		const ChoiceListSort sort;
		const ChoiceListType type;

		const int total;

		int selectedOptionIndex = -1;
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
	shared_ptr<ScriptExecutor> getScriptExecutor();

	bool isLoaded();

private:
	void _updateGUI();
	void _updateChoiceLists();
	void _updateNavigation();
	void _updateMiscellaneous();
	void _generateScriptLineOverview(ScriptLine& scriptLine);
	void _addChoiceList(ChoiceListSort listSort, ChoiceListType list, int activeIndex = -1);
	void _removeChoiceList();
	void _clearChoiceLists();
	void _addNewScriptLine(const string& newID);
	void _loadScriptFromFile();
	void _saveScriptToFile();
	void _unloadScript();

	// General stuff
	FabiEngine3D& _fe3d;
	shared_ptr<EngineGuiManager> _gui = nullptr;
	shared_ptr<EngineGuiWindow> _leftWindow = nullptr;
	shared_ptr<EngineGuiWindow> _rightWindow = nullptr;
	shared_ptr<ScriptEvent> _currentEventToAdd = nullptr;
	shared_ptr<ScriptExecutor> _scriptExecutor = nullptr;
	shared_ptr<Script> _script = nullptr;

	// Option names for front-end
	vector<ChoiceList> _choiceListStack;
	vector<string> _eventTypeNames;
	vector<string> _inputTypeNames;
	vector<string> _inputKeyNames;
	vector<string> _inputMouseNames;
	vector<string> _inputMethodNames;

	// Editor variables
	string _currentProjectName = "";
	string _currentScriptLineID = "";
	const vec3 _cameraStartingPosition = vec3(0.0f, 0.0f, 10.0f);
	float _scrollingAcceleration = 0.0f;
	float _cameraAcceleration = 0.0f;
	const float _maxScrollingAcceleration = 0.3f;
	const float _optionBillboardHeight = 0.75f;
	unsigned int _pointLightCounter = 0;
	bool _allowedToAddScript = false;
	bool _isCreatingScript = false;
	bool _isLoaded = false;
};