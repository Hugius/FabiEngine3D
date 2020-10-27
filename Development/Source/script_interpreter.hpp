#pragma once

#include "script.hpp"
#include "scene_editor.hpp"
#include "script_type.hpp"
#include "script_value.hpp"
#include "script_variable.hpp"

class ScriptInterpreter
{
public:
	ScriptInterpreter(FabiEngine3D& fe3d, Script& script, SceneEditor& sceneEditor);

	void load();
	void executeInitialization();
	void executeUpdate();
	void executeDestruction();
	void unload();

	bool hasThrownError();

private:
	// Functions
	void _executeScript(const string& scriptID, ScriptType scriptType);
	void _processVariableDefinition(const string& scriptLine, ScriptVariableScope scope);
	void _throwScriptError(const string& message);
	bool _isString(const string& value);
	bool _isDecimal(const string& value);
	bool _isInteger(const string& value);
	bool _isBoolean(const string& value);
	bool _isLocalVariableExisting(const string& variableID);
	bool _isGlobalVariableExisting(const string& variableID);
	bool _checkIfStatement(string condition);
	bool _validateArguments(vector<ScriptValue> arguments, vector<ScriptValueType> types);
	ScriptVariable& _getLocalVariable(const string& variableID);
	ScriptVariable& _getGlobalVariable(const string& variableID);
	vector<ScriptValue> _executeEngineFunction(const string& scriptLine);
	vector<ScriptValue> _extractArguments(string argumentString);

	// Instances
	FabiEngine3D& _fe3d;
	Script& _script;
	SceneEditor& _sceneEditor;

	// Stacks
	vector<vector<ScriptVariable>> _localVariablesStack;
	vector<string> _currentScriptStackIDs;
	vector<unsigned int> _currentLineStackIndices;

	// Vectors
	vector<string> _initScriptIDs;
	vector<string> _updateScriptIDs;
	vector<string> _destroyScriptIDs;
	vector<ScriptVariable> _globalVariables;

	// Strings
	string _initEntryID = "";
	string _updateEntryID = "";
	string _destroyEntryID = "";
	const string _metaKeyword	 = "META";
	const string _executeKeyword = "EXEC";
	const string _ifKeyword      = "IF";
	const string _elseifKeyword  = "ELIF";
	const string _elseKeyword    = "ELSE";
	const string _globalKeyword  = "GLOB";
	const string _constKeyword   = "CONST";
	const string _stringKeyword  = "STR";
	const string _decimalKeyword = "DEC";
	const string _integerKeyword = "INT";
	const string _booleanKeyword = "BOOL";
	const string _isKeyword		 = "IS";
	const string _notKeyword	 = "NOT";
	const string _andKeyword	 = "AND";
	const string _orKeyword		 = "OR";
	const string _moreKeyword    = "MORE";
	const string _lessKeyword    = "LESS";

	// Booleans
	bool _hasThrownError = false;

	// String to input type map
	static inline const map<string, InputType> _keyInputStringMap =
	{
		{"KEY_A", InputType::KEY_A},
		{"KEY_B", InputType::KEY_B},
		{"KEY_C", InputType::KEY_C},
		{"KEY_D", InputType::KEY_D},
		{"KEY_E", InputType::KEY_E},
		{"KEY_F", InputType::KEY_F},
		{"KEY_G", InputType::KEY_G},
		{"KEY_H", InputType::KEY_H},
		{"KEY_I", InputType::KEY_I},
		{"KEY_J", InputType::KEY_J},
		{"KEY_K", InputType::KEY_K},
		{"KEY_L", InputType::KEY_L},
		{"KEY_M", InputType::KEY_M},
		{"KEY_N", InputType::KEY_N},
		{"KEY_O", InputType::KEY_O},
		{"KEY_P", InputType::KEY_P},
		{"KEY_Q", InputType::KEY_Q},
		{"KEY_R", InputType::KEY_R},
		{"KEY_S", InputType::KEY_S},
		{"KEY_T", InputType::KEY_T},
		{"KEY_U", InputType::KEY_U},
		{"KEY_V", InputType::KEY_V},
		{"KEY_W", InputType::KEY_W},
		{"KEY_X", InputType::KEY_X},
		{"KEY_Y", InputType::KEY_Y},
		{"KEY_Z", InputType::KEY_Z},
		{"KEY_LSHIFT", InputType::KEY_LSHIFT},
		{"KEY_RSHIFT", InputType::KEY_RSHIFT},
		{"KEY_LCTRL", InputType::KEY_LCTRL},
		{"KEY_RCTRL", InputType::KEY_RCTRL},
		{"KEY_SPACE", InputType::KEY_SPACE},
		{"KEY_ENTER", InputType::KEY_ENTER},
		{"KEY_BACKSPACE", InputType::KEY_BACKSPACE},
		{"KEY_CAPSLOCK", InputType::KEY_CAPSLOCK},
		{"KEY_TAB", InputType::KEY_TAB},
		{"KEY_LEFT", InputType::KEY_LEFT},
		{"KEY_RIGHT", InputType::KEY_RIGHT},
		{"KEY_UP", InputType::KEY_UP},
		{"KEY_DOWN", InputType::KEY_DOWN},
		{"KEY_0", InputType::KEY_0},
		{"KEY_1", InputType::KEY_1},
		{"KEY_2", InputType::KEY_2},
		{"KEY_3", InputType::KEY_3},
		{"KEY_4", InputType::KEY_4},
		{"KEY_5", InputType::KEY_5},
		{"KEY_6", InputType::KEY_6},
		{"KEY_7", InputType::KEY_7},
		{"KEY_8", InputType::KEY_8},
		{"KEY_9", InputType::KEY_9},
	};

	static inline const map<string, InputType> _mouseInputStringMap =
	{
		{"BUTTON_LEFT", InputType::MOUSE_BUTTON_LEFT},
		{"BUTTON_MIDDLE", InputType::MOUSE_BUTTON_MIDDLE},
		{"BUTTON_RIGHT", InputType::MOUSE_BUTTON_RIGHT},
	};
};