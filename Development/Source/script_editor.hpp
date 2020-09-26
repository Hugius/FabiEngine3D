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
		VARIABLE,
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
		EVENT_INPUT_MOUSE_TYPES,
		EVENT_INPUT_KEY_NAMES,
		EVENT_INPUT_MOUSE_BUTTONS,
		EVENT_INPUT_METHODS,

		// Collision event

		// Time event
		

		// Condition event

		// Camera actions
		ACTION_CAMERA_TYPES,
		ACTION_CAMERA_DIRECTIONS,
		ACTION_CAMERA_FOLLOWS,
		ACTION_CAMERA_METHODS,
		ACTION_CAMERA_TOGGLE,
		ACTION_CAMERA_VALUES,

		// Miscellaneous
		VARIABLE_CONSTANT,
		VARIABLE_TYPE,
		NONE
	};

	struct ChoiceList final
	{
		ChoiceList(ChoiceListSort listSort, ChoiceListType listType, int optionTotal, const vector<string> optionNamesList) : 
			sort(listSort), type(listType), total(optionTotal), optionNames(optionNamesList)
		{

		}

		const ChoiceListSort sort;
		const ChoiceListType type;

		const int total;

		const vector<string> optionNames;

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
	void _updateScriptLineAdding();
	void _updateScriptVariableAdding();
	void _updateMiscellaneous();
	void _generateScriptLineOverview(ScriptLine& scriptLine);
	void _generateScriptVariableOverview(ScriptVariable& scriptVariable);
	void _addChoiceList(ChoiceListSort listSort, ChoiceListType listType, int activeIndex = -1);
	void _addChoiceList(ChoiceListSort listSort, ChoiceListType listType, string headerName, vector<string> optionNames, int activeIndex = -1);
	void _removeChoiceList();
	void _clearChoiceLists();
	void _calibrateScriptLines();
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

	// Editor variables
	string _currentProjectName = "";
	string _currentScriptLineID = "";
	string _currentScriptVariableID = "";
	string _newScriptVariableID = "";
	const vec3 _cameraStartingPosition = vec3(0.0f, 0.0f, 10.0f);
	float _scrollingAcceleration = 0.0f;
	float _cameraAcceleration = 0.0f;
	const float _maxScrollingAcceleration = 0.3f;
	const float _optionBillboardHeight = 0.75f;
	unsigned int _pointLightCounter = 0;
	bool _allowedToAddScriptLine = false;
	bool _isCreatingScriptLine = false;
	bool _isUpdatingScriptLine = false;
	bool _isAddingScriptLine = false;
	bool _allowedToAddScriptVariable = false;
	bool _isCreatingScriptVariable = false;
	bool _isUpdatingScriptVariable = false;
	bool _isAddingScriptVariable = false;
	bool _isLoaded = false;
};