#pragma once

#include "script.hpp"
#include "script_type.hpp"
#include "script_value.hpp"
#include "script_variable.hpp"
#include "script_condition_statement.hpp"
#include "model_editor.hpp"
#include "scene_editor.hpp"
#include "animation_editor.hpp"
#include "billboard_editor.hpp"
#include "audio_editor.hpp"

class ScriptInterpreter
{
public:
	ScriptInterpreter(FabiEngine3D& fe3d, Script& script, SceneEditor& sceneEditor, ModelEditor& modelEditor,
		AnimationEditor& animationEditor, BillboardEditor& billboardEditor, AudioEditor& audioEditor, EnvironmentEditor& environmentEditor);

	void load();
	void executeInitialization();
	void executeUpdate(bool debug);
	void executeDestruction();
	void unload();
	void setCurrentProjectID(const string& projectName);

	bool hasThrownError();
	bool gameMustStop();

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
	bool _executeFe3dRaycastFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dCollisionFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dSkyEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dTerrainEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dWaterEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dModelEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dBillboardEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dAabbEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dLightEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dGuiEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dTextEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dAudioEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dAnimationFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dLightingFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dGraphicsFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dMusicFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dFilesystemFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dSceneFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _executeFe3dMiscFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	bool _validateFe3dSkyEntity();
	bool _validateFe3dTerrainEntity();
	bool _validateFe3dWaterEntity();
	bool _validateFe3dModelEntity(const string& ID, bool previewEntity = false);
	bool _validateFe3dBillboardEntity(const string& ID, bool previewEntity = false);
	bool _validateFe3dAabbEntity(const string& ID);
	bool _validateFe3dLightEntity(const string& ID);
	bool _validateFe3dGuiEntity(const string& ID);
	bool _validateFe3dTextEntity(const string& ID);
	bool _validateFe3dAudioEntity(const string& ID, bool previewEntity = false);

	// Miscellaneous functions
	ScriptConditionStatement* _getLastConditionStatement(vector<ScriptConditionStatement>& statements, unsigned int scopeDepth);
	string _limitIntegerString(const string& valueString);
	string _limitDecimalString(const string& valueString);
	unsigned int _countFrontSpaces(const string& scriptLineText);
	bool _validateScopeChange(unsigned int countedSpaces, const string& scriptLineText, unsigned int& scopeDepth);
	bool _validateKeyInputString(const string& inputString);
	bool _validateMouseInputString(const string& inputString);
	bool _validateCurrentProject();
	Vec2 _convertGuiPositionToViewport(Vec2 position);
	Vec2 _convertGuiPositionFromViewport(Vec2 position);
	Vec2 _convertGuiSizeToViewport(Vec2 size);
	Vec2 _convertGuiSizeFromViewport(Vec2 size);
	void _throwScriptError(const string& message);
	void _checkEngineWarnings();

	// Instances
	FabiEngine3D& _fe3d;
	Script& _script;
	SceneEditor& _sceneEditor;
	ModelEditor& _modelEditor;
	AnimationEditor& _animationEditor;
	BillboardEditor& _billboardEditor;
	AudioEditor& _audioEditor;
	EnvironmentEditor& _environmentEditor;

	// Dictionaries
	map<string, float> _debuggingTimes;

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
	string _currentProjectID = "";
	string _initEntryID = "";
	string _updateEntryID = "";
	string _destroyEntryID = "";
	static inline const string META_KEYWORD = "META";
	static inline const string EXECUTE_KEYWORD = "EXEC";
	static inline const string LOOP_KEYWORD = "LOOP";
	static inline const string BREAK_KEYWORD = "BREAK";
	static inline const string IF_KEYWORD = "IF";
	static inline const string ELIF_KEYWORD = "ELIF";
	static inline const string ELSE_KEYWORD = "ELSE";
	static inline const string GLOBAL_KEYWORD = "GLOB";
	static inline const string CONST_KEYWORD = "CONST";
	static inline const string EDIT_KEYWORD = "EDIT";
	static inline const string LIST_KEYWORD = "LIST";
	static inline const string VEC3_KEYWORD = "VEC3";
	static inline const string STRING_KEYWORD = "STR";
	static inline const string DECIMAL_KEYWORD = "DEC";
	static inline const string INTEGER_KEYWORD = "INT";
	static inline const string BOOLEAN_KEYWORD = "BOOL";
	static inline const string IS_KEYWORD = "IS";
	static inline const string NOT_KEYWORD = "NOT";
	static inline const string AND_KEYWORD = "AND";
	static inline const string OR_KEYWORD = "OR";
	static inline const string MORE_KEYWORD = "MORE";
	static inline const string LESS_KEYWORD = "LESS";
	static inline const string ADDITION_KEYWORD = "INCR";
	static inline const string SUBTRACTION_KEYWORD = "DECR";
	static inline const string MULTIPLICATION_KEYWORD = "MUL";
	static inline const string DIVISION_KEYWORD = "DIV";
	static inline const string NEGATION_KEYWORD = "NEG";
	static inline const string CASTING_KEYWORD = "CAST";
	static inline const string PUSHING_KEYWORD = "PUSH";
	static inline const string PULLING_KEYWORD = "PULL";
	static inline const string PASS_KEYWORD = "PASS";

	// Integers
	static inline const unsigned int SPACES_PER_INDENT = 4;
	static inline const unsigned int MAX_LOOPS_PER_FRAME = 1000;
	static inline const unsigned int MAX_EXECUTION_DEPTH = 100;
	unsigned int _lastLoggerMessageCount = 0;
	unsigned int _executionDepth = 0;

	// Booleans
	bool _hasThrownError = false;
	bool _gameMustStop = false;
	bool _scopeHasChanged = false;
	bool _passedScopeChanger = false;
	bool _isDebugging = false;

	// String to input type map
	static inline const map<string, InputType> KEY_INPUT_STRING_MAP =
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
		{"KEY_ENTER", InputType::KEY_ENTER},
		{"KEY_ESCAPE", InputType::KEY_ESCAPE},
		{"KEY_BACKSPACE", InputType::KEY_BACKSPACE},
		{"KEY_TAB", InputType::KEY_TAB},
		{"KEY_LALT", InputType::KEY_LALT},
		{"KEY_RALT", InputType::KEY_RALT},
		{"KEY_LCTRL", InputType::KEY_LCTRL},
		{"KEY_RCTRL", InputType::KEY_RCTRL},
		{"KEY_LSHIFT", InputType::KEY_LSHIFT},
		{"KEY_RSHIFT", InputType::KEY_RSHIFT},
		{"KEY_CAPSLOCK", InputType::KEY_CAPSLOCK},
		{"KEY_F1", InputType::KEY_F1},
		{"KEY_F2", InputType::KEY_F2},
		{"KEY_F3", InputType::KEY_F3},
		{"KEY_F4", InputType::KEY_F4},
		{"KEY_F5", InputType::KEY_F5},
		{"KEY_F6", InputType::KEY_F6},
		{"KEY_F7", InputType::KEY_F7},
		{"KEY_F8", InputType::KEY_F8},
		{"KEY_F9", InputType::KEY_F9},
		{"KEY_F1", InputType::KEY_F10},
		{"KEY_F11", InputType::KEY_F11},
		{"KEY_F12", InputType::KEY_F12},
		{"KEY_RIGHT", InputType::KEY_RIGHT},
		{"KEY_LEFT", InputType::KEY_LEFT},
		{"KEY_DOWN", InputType::KEY_DOWN},
		{"KEY_UP", InputType::KEY_UP},
		{"KEY_DELETE", InputType::KEY_DELETE},
		{"KEY_COLON", InputType::KEY_COLON},
		{"KEY_SEMICOLON", InputType::KEY_SEMICOLON},
		{"KEY_LESS", InputType::KEY_LESS},
		{"KEY_EQUALS", InputType::KEY_EQUALS},
		{"KEY_GREATER", InputType::KEY_GREATER},
		{"KEY_QUESTION", InputType::KEY_QUESTION},
		{"KEY_AT", InputType::KEY_AT},
		{"KEY_LEFTBRACKET", InputType::KEY_LEFTBRACKET},
		{"KEY_BACKSLASH", InputType::KEY_BACKSLASH},
		{"KEY_RIGHTBRACKET", InputType::KEY_RIGHTBRACKET},
		{"KEY_CARET", InputType::KEY_CARET},
		{"KEY_UNDERSCORE", InputType::KEY_UNDERSCORE},
		{"KEY_BACKQUOTE", InputType::KEY_BACKQUOTE},
		{"KEY_SPACE", InputType::KEY_SPACE},
		{"KEY_EXCLAMATION", InputType::KEY_EXCLAMATION},
		{"KEY_DOUBLEQUOTE", InputType::KEY_DOUBLEQUOTE},
		{"KEY_HASH", InputType::KEY_HASH},
		{"KEY_PERCENT", InputType::KEY_PERCENT},
		{"KEY_DOLLAR", InputType::KEY_DOLLAR},
		{"KEY_AMPERSAND", InputType::KEY_AMPERSAND},
		{"KEY_QUOTE", InputType::KEY_QUOTE},
		{"KEY_LEFTPARENTHESIS", InputType::KEY_LEFTPARENTHESIS},
		{"KEY_RIGHTPARENTHESIS", InputType::KEY_RIGHTPARENTHESIS},
		{"KEY_ASTERISK", InputType::KEY_ASTERISK},
		{"KEY_PLUS", InputType::KEY_PLUS},
		{"KEY_COMMA", InputType::KEY_COMMA},
		{"KEY_MINUS", InputType::KEY_MINUS},
		{"KEY_PERIOD", InputType::KEY_PERIOD},
		{"KEY_SLASH", InputType::KEY_SLASH}
	};

	static inline const map<string, InputType> MOUSE_INPUT_STRING_MAP =
	{
		{"BUTTON_LEFT", InputType::MOUSE_BUTTON_LEFT},
		{"BUTTON_MIDDLE", InputType::MOUSE_BUTTON_MIDDLE},
		{"BUTTON_RIGHT", InputType::MOUSE_BUTTON_RIGHT},
	};
};