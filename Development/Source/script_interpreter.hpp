#pragma once

#include "script.hpp"
#include "script_type.hpp"
#include "script_value.hpp"
#include "script_variable.hpp"
#include "script_condition_statement.hpp"
#include "model_editor.hpp"
#include "scene_editor.hpp"
#include "animation_editor.hpp"

class ScriptInterpreter
{
public:
	ScriptInterpreter(FabiEngine3D& fe3d, Script& script, SceneEditor& sceneEditor, ModelEditor& modelEditor, AnimationEditor& animationEditor);

	void load();
	void executeInitialization();
	void executeUpdate();
	void executeDestruction();
	void unload();

	bool hasThrownError();

private:
	// Core functions
	void _executeScript(const string& scriptID, ScriptType scriptType);

	// Value functions
	bool _isListValue(const string& valueString);
	bool _isVec3Value(const string& valueString);
	bool _isStringValue(const string& valueString);
	bool _isDecimalValue(const string& valueString);
	bool _isIntegerValue(const string& valueString);
	bool _isBooleanValue(const string& valueString);
	Vec3 _extractVec3FromString(const string& valueString);
	Ivec3 _extractVec3PartFromString(const string& valueString);
	int _extractListIndexFromString(const string& valueString, bool& isAccessingList);

	// Variable functions
	void _processVariableCreation(const string& scriptLine, ScriptVariableScope scope);
	void _processVariableAlteration(const string& scriptLine);
	void _processVariableArithmetic(const string& scriptLine);
	void _processVariableTypecast(const string& scriptLine);
	void _processStringConcatenation(const string& scriptLine);
	bool _isLocalVariableExisting(const string& variableID);
	bool _isGlobalVariableExisting(const string& variableID);
	ScriptVariable& _getLocalVariable(const string& variableID);
	ScriptVariable& _getGlobalVariable(const string& variableID);

	// If statement functions
	bool _checkConditionString(string conditionString);
	bool _validateCondition(ScriptValue& firstValue, string comparisonOperator, ScriptValue& secondValue);
	bool _compareValues(ScriptValue& firstValue, string comparisonOperator, ScriptValue& secondValue);

	// List functions
	bool _validateListIndex(ScriptVariable& list, unsigned int index);
	bool _validateListValueAmount(vector<ScriptValue> list, unsigned int amount);
	bool _validateListValueTypes(vector<ScriptValue> list, vector<ScriptValueType> types);
	vector<ScriptValue> _extractValuesFromListString(string listString);
	void _processListPush(const string& scriptLine);
	void _processListPull(const string& scriptLine);

	// Functioncall functions
	vector<ScriptValue> _processEngineFunctionCall(const string& scriptLine);
	vector<ScriptValue> _processMathematicalFunctionCall(const string& scriptLine);
	vector<ScriptValue> _processMiscellaneousFunctionCall(const string& scriptLine);
	bool _executeFe3dInputFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dCameraFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dPhysicsFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dSkyEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dTerrainEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dWaterEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dGameEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dBillboardEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dAabbEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dAnimationFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dMiscFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _validateFe3dGameEntity(const string& ID, bool previewEntity = false);
	bool _validateFe3dAabbEntity(const string& ID);

	// Miscellaneous functions
	ScriptConditionStatement* _getLastConditionStatement(vector<ScriptConditionStatement>& statements, unsigned int scopeDepth);
	unsigned int _countFrontSpaces(const string& scriptLineText);
	bool _validateScopeChange(unsigned int countedSpaces, const string& scriptLineText, unsigned int& scopeDepth);
	bool _validateKeyInputString(const string& inputString);
	bool _validateMouseInputString(const string& inputString);
	void _throwScriptError(const string& message);
	void _checkEngineWarnings();

	// Instances
	FabiEngine3D& _fe3d;
	Script& _script;
	SceneEditor& _sceneEditor;
	ModelEditor& _modelEditor;
	AnimationEditor& _animationEditor;

	// Stacks
	vector<vector<ScriptVariable>> _localVariablesStack;
	vector<string> _currentScriptIDsStack;
	vector<unsigned int> _currentLineIndexStack;

	// Vectors
	vector<string> _initScriptIDs;
	vector<string> _updateScriptIDs;
	vector<string> _destroyScriptIDs;
	vector<ScriptVariable> _globalVariables;

	// Strings
	string _initEntryID = "";
	string _updateEntryID = "";
	string _destroyEntryID = "";
	const string _metaKeyword			= "META";
	const string _executeKeyword		= "EXEC";
	const string _loopKeyword			= "LOOP";
	const string _breakKeyword			= "BREAK";
	const string _ifKeyword				= "IF";
	const string _elifKeyword			= "ELIF";
	const string _elseKeyword			= "ELSE";
	const string _globalKeyword			= "GLOB";
	const string _constKeyword			= "CONST";
	const string _editKeyword			= "EDIT";
	const string _listKeyword			= "LIST";
	const string _vec3Keyword			= "VEC3";
	const string _stringKeyword			= "STR";
	const string _decimalKeyword		= "DEC";
	const string _integerKeyword		= "INT";
	const string _booleanKeyword		= "BOOL";
	const string _isKeyword				= "IS";
	const string _notKeyword			= "NOT";
	const string _andKeyword			= "AND";
	const string _orKeyword				= "OR";
	const string _moreKeyword			= "MORE";
	const string _lessKeyword			= "LESS";
	const string _additionKeyword	    = "INCR";
	const string _subtractionKeyword	= "DECR";
	const string _multiplicationKeyword = "MUL";
	const string _divisionKeyword		= "DIV";
	const string _negationKeyword		= "NEG";
	const string _castingKeyword	    = "CAST";
	const string _concatenationKeyword  = "CONCAT";
	const string _pushingKeyword		= "PUSH";
	const string _pullingKeyword		= "PULL";
	const string _passKeyword			= "PASS";

	// Integers
	const unsigned int _spacesPerIndent = 4;
	const unsigned int _maxLoopsPerFrame = 1000;
	const unsigned int _maxExecutionDepth = 100;
	unsigned int _lastLoggerMessageCount = 0;
	unsigned int _executionDepth = 0;

	// Booleans
	bool _hasThrownError = false;
	bool _scopeHasChanged = false;
	bool _passedScopeChanger = false;

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