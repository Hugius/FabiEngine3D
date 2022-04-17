#pragma once

#include "sky_editor.hpp"
#include "terrain_editor.hpp"
#include "water_editor.hpp"
#include "model_editor.hpp"
#include "quad3d_editor.hpp"
#include "text3d_editor.hpp"
#include "quad2d_editor.hpp"
#include "text2d_editor.hpp"
#include "animation3d_editor.hpp"
#include "animation2d_editor.hpp"
#include "sound_editor.hpp"
#include "world_editor.hpp"
#include "script.hpp"
#include "script_type.hpp"
#include "script_value.hpp"
#include "script_variable.hpp"
#include "script_condition_statement.hpp"
#include "custom_world_builder.hpp"

class ScriptInterpreter final
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void inject(shared_ptr<Script> script);
	void inject(shared_ptr<SkyEditor> skyEditor);
	void inject(shared_ptr<TerrainEditor> terrainEditor);
	void inject(shared_ptr<WaterEditor> waterEditor);
	void inject(shared_ptr<ModelEditor> modelEditor);
	void inject(shared_ptr<Quad3dEditor> quad3dEditor);
	void inject(shared_ptr<Text3dEditor> text3dEditor);
	void inject(shared_ptr<Quad2dEditor> quad2dEditor);
	void inject(shared_ptr<Text2dEditor> text2dEditor);
	void inject(shared_ptr<Animation2dEditor> animation2dEditor);
	void inject(shared_ptr<Animation3dEditor> animation3dEditor);
	void inject(shared_ptr<SoundEditor> soundEditor);
	void inject(shared_ptr<WorldEditor> worldEditor);
	void inject(shared_ptr<CustomWorldBuilder> customWorldBuilder);
	void inject(shared_ptr<WorldHelper> worldHelper);
	void setCurrentProjectId(const string & projectId);
	void load();
	void executeInitializeScripts();
	void executeUpdateScripts(bool isDebugging);
	void executeTerminateScripts();
	void unload();

	const bool hasThrownError() const;
	const bool mustStopApplication() const;

private:
	void _executeScript(const string & scriptId, ScriptType scriptType);
	void _processVariableCreation(const string & scriptLine, ScriptVariableScope scope);
	void _processVariableAlteration(const string & scriptLine);
	void _processVariableArithmetic(const string & scriptLine);
	void _processVariableTypecast(const string & scriptLine);
	void _processListPush(const string & scriptLine);
	void _processListPull(const string & scriptLine);
	void _throwStartupError(const string & message);
	void _throwRuntimeError(const string & message);
	void _checkEngineWarnings(unsigned int lastLoggerMessageCount);
	void _performArithmeticOperation(shared_ptr<ScriptValue> leftValue, const string & operatorString, shared_ptr<ScriptValue> rightValue);

	const vector<shared_ptr<ScriptValue>> _extractValuesFromListString(const string & listString);
	const vector<shared_ptr<ScriptValue>> _processFe3dFunctionCall(const string & scriptLine);
	const vector<shared_ptr<ScriptValue>> _processMathFunctionCall(const string & scriptLine);
	const vector<shared_ptr<ScriptValue>> _processMiscFunctionCall(const string & scriptLine);

	const shared_ptr<ScriptVariable> _getLocalVariable(const string & variableId);
	const shared_ptr<ScriptVariable> _getGlobalVariable(const string & variableId) const;

	const string _limitIntegerString(const string & valueString) const;
	const string _limitDecimalString(const string & valueString) const;

	const unsigned int _countLeadingSpaces(const string & scriptLineText);

	const int _extractListIndexFromString(const string & valueString, bool & isAccessingList);
	const int _getLastConditionStatementIndex(const vector<ScriptConditionStatement> & statements, unsigned int scopeDepth) const;

	const bool _isListValue(const string & valueString) const;
	const bool _isStringValue(const string & valueString) const;
	const bool _isDecimalValue(const string & valueString) const;
	const bool _isIntegerValue(const string & valueString) const;
	const bool _isBooleanValue(const string & valueString) const;
	const bool _isLocalVariableExisting(const string & variableId);
	const bool _isGlobalVariableExisting(const string & variableId) const;
	const bool _checkConditionString(const string & conditionString);
	const bool _validateCondition(shared_ptr<ScriptValue> firstValue, const string & comparisonOperator, shared_ptr<ScriptValue> secondValue);
	const bool _compareValues(shared_ptr<ScriptValue> firstValue, const string & comparisonOperator, shared_ptr<ScriptValue> secondValue) const;
	const bool _validateListIndex(const shared_ptr<ScriptVariable> list, unsigned int index);
	const bool _validateArgumentCount(const vector<shared_ptr<ScriptValue>> & values, unsigned int count);
	const bool _validateArgumentTypes(const vector<shared_ptr<ScriptValue>> & values, const vector<ScriptValueType> & types);
	const bool _executeFe3dSkySetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dSkyGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dTerrainSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dTerrainGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dWaterSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dWaterGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dModelSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dModelGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dQuad3dSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dQuad3dGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dText3dSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dText3dGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dAabbSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dAabbGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dQuad2dSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dQuad2dGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dText2dSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dText2dGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dPointlightSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dPointlightGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dSpotlightSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dSpotlightGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dReflectionSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dReflectionGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dSound3dSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dSound3dGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dSound2dSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dSound2dGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dGraphicsSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dGraphicsGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dWorldSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dWorldGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dInputGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dCameraSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dCameraGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dRaycastSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dRaycastGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dCollisionSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dCollisionGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dServerSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dServerGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dClientSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dClientGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dFilesystemSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dFilesystemGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dClockSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dClockGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dUncategorizedSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dUncategorizedGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _validateFe3dSky(const string & id, bool isTemplate);
	const bool _validateFe3dTerrain(const string & id, bool isTemplate);
	const bool _validateFe3dWater(const string & id, bool isTemplate);
	const bool _validateFe3dModel(const string & id, bool isTemplate);
	const bool _validateFe3dModelPart(const string & modelId, const string & partId);
	const bool _validateFe3dQuad3d(const string & id, bool isTemplate);
	const bool _validateFe3dText3d(const string & id, bool isTemplate);
	const bool _validateFe3dQuad2d(const string & id, bool isTemplate);
	const bool _validateFe3dText2d(const string & id, bool isTemplate);
	const bool _validateFe3dAabb(const string & id);
	const bool _validateFe3dPointlight(const string & id);
	const bool _validateFe3dSpotlight(const string & id);
	const bool _validateFe3dReflection(const string & id);
	const bool _validateFe3dSound3d(const string & id, bool isTemplate);
	const bool _validateFe3dSound2d(const string & id, bool isTemplate);
	const bool _validateFe3dAnimation2d(const string & id);
	const bool _validateFe3dAnimation3d(const string & id);
	const bool _validateFe3dId(const string & id);
	const bool _validateScopeChange(unsigned int countedSpaces, const string & scriptLineText, unsigned int & scopeDepth);
	const bool _validateKeyInputString(const string & inputString);
	const bool _validateMouseInputString(const string & inputString);
	const bool _validateSavesDirectory();

	static inline const unordered_map<string, MouseWheel> MOUSE_WHEELS =
	{
		{"WHEEL_FORWARD", MouseWheel::WHEEL_FORWARD},
		{"WHEEL_BACKWARD", MouseWheel::WHEEL_BACKWARD},
	};
	static inline const unordered_map<string, MouseButton> MOUSE_BUTTONS =
	{
		{"BUTTON_LEFT", MouseButton::BUTTON_LEFT},
		{"BUTTON_MIDDLE", MouseButton::BUTTON_MIDDLE},
		{"BUTTON_RIGHT", MouseButton::BUTTON_RIGHT},
	};
	static inline const unordered_map<string, KeyboardKey> KEYBOARD_KEYS =
	{
		{"KEY_BACKSPACE", KeyboardKey::KEY_BACKSPACE},
		{"KEY_TAB", KeyboardKey::KEY_TAB},
		{"KEY_ENTER", KeyboardKey::KEY_ENTER},
		{"KEY_SHIFT", KeyboardKey::KEY_SHIFT},
		{"KEY_CONTROL", KeyboardKey::KEY_CONTROL},
		{"KEY_ALT", KeyboardKey::KEY_ALT},
		{"KEY_CAPSLOCK", KeyboardKey::KEY_CAPSLOCK},
		{"KEY_ESCAPE", KeyboardKey::KEY_ESCAPE},
		{"KEY_SPACEBAR", KeyboardKey::KEY_SPACEBAR},
		{"KEY_PAGEUP", KeyboardKey::KEY_PAGEUP},
		{"KEY_PAGEDOWN", KeyboardKey::KEY_PAGEDOWN},
		{"KEY_END", KeyboardKey::KEY_END},
		{"KEY_HOME", KeyboardKey::KEY_HOME},
		{"KEY_LEFT", KeyboardKey::KEY_LEFT},
		{"KEY_UP", KeyboardKey::KEY_UP},
		{"KEY_RIGHT", KeyboardKey::KEY_RIGHT},
		{"KEY_DOWN", KeyboardKey::KEY_DOWN},
		{"KEY_INSERT", KeyboardKey::KEY_INSERT},
		{"KEY_DELETE", KeyboardKey::KEY_DELETE},
		{"KEY_0", KeyboardKey::KEY_0},
		{"KEY_1", KeyboardKey::KEY_1},
		{"KEY_2", KeyboardKey::KEY_2},
		{"KEY_3", KeyboardKey::KEY_3},
		{"KEY_4", KeyboardKey::KEY_4},
		{"KEY_5", KeyboardKey::KEY_5},
		{"KEY_6", KeyboardKey::KEY_6},
		{"KEY_7", KeyboardKey::KEY_7},
		{"KEY_8", KeyboardKey::KEY_8},
		{"KEY_9", KeyboardKey::KEY_9},
		{"KEY_A", KeyboardKey::KEY_A},
		{"KEY_B", KeyboardKey::KEY_B},
		{"KEY_C", KeyboardKey::KEY_C},
		{"KEY_D", KeyboardKey::KEY_D},
		{"KEY_E", KeyboardKey::KEY_E},
		{"KEY_F", KeyboardKey::KEY_F},
		{"KEY_G", KeyboardKey::KEY_G},
		{"KEY_H", KeyboardKey::KEY_H},
		{"KEY_I", KeyboardKey::KEY_I},
		{"KEY_J", KeyboardKey::KEY_J},
		{"KEY_K", KeyboardKey::KEY_K},
		{"KEY_L", KeyboardKey::KEY_L},
		{"KEY_M", KeyboardKey::KEY_M},
		{"KEY_N", KeyboardKey::KEY_N},
		{"KEY_O", KeyboardKey::KEY_O},
		{"KEY_P", KeyboardKey::KEY_P},
		{"KEY_Q", KeyboardKey::KEY_Q},
		{"KEY_R", KeyboardKey::KEY_R},
		{"KEY_S", KeyboardKey::KEY_S},
		{"KEY_T", KeyboardKey::KEY_T},
		{"KEY_U", KeyboardKey::KEY_U},
		{"KEY_V", KeyboardKey::KEY_V},
		{"KEY_W", KeyboardKey::KEY_W},
		{"KEY_X", KeyboardKey::KEY_X},
		{"KEY_Y", KeyboardKey::KEY_Y},
		{"KEY_Z", KeyboardKey::KEY_Z},
		{"KEY_NUMPAD0", KeyboardKey::KEY_NUMPAD0},
		{"KEY_NUMPAD1", KeyboardKey::KEY_NUMPAD1},
		{"KEY_NUMPAD2", KeyboardKey::KEY_NUMPAD2},
		{"KEY_NUMPAD3", KeyboardKey::KEY_NUMPAD3},
		{"KEY_NUMPAD4", KeyboardKey::KEY_NUMPAD4},
		{"KEY_NUMPAD5", KeyboardKey::KEY_NUMPAD5},
		{"KEY_NUMPAD6", KeyboardKey::KEY_NUMPAD6},
		{"KEY_NUMPAD7", KeyboardKey::KEY_NUMPAD7},
		{"KEY_NUMPAD8", KeyboardKey::KEY_NUMPAD8},
		{"KEY_NUMPAD9", KeyboardKey::KEY_NUMPAD9},
		{"KEY_MULTIPLY", KeyboardKey::KEY_MULTIPLY},
		{"KEY_ADD", KeyboardKey::KEY_ADD},
		{"KEY_SUBTRACT", KeyboardKey::KEY_SUBTRACT},
		{"KEY_DECIMAL", KeyboardKey::KEY_DECIMAL},
		{"KEY_DIVIDE", KeyboardKey::KEY_DIVIDE},
		{"KEY_F1", KeyboardKey::KEY_F1},
		{"KEY_F2", KeyboardKey::KEY_F2},
		{"KEY_F3", KeyboardKey::KEY_F3},
		{"KEY_F4", KeyboardKey::KEY_F4},
		{"KEY_F5", KeyboardKey::KEY_F5},
		{"KEY_F6", KeyboardKey::KEY_F6},
		{"KEY_F7", KeyboardKey::KEY_F7},
		{"KEY_F8", KeyboardKey::KEY_F8},
		{"KEY_F9", KeyboardKey::KEY_F9},
		{"KEY_F10", KeyboardKey::KEY_F10},
		{"KEY_F11", KeyboardKey::KEY_F11},
		{"KEY_F12", KeyboardKey::KEY_F12},
		{"KEY_F13", KeyboardKey::KEY_F13},
		{"KEY_F14", KeyboardKey::KEY_F14},
		{"KEY_F15", KeyboardKey::KEY_F15},
		{"KEY_F16", KeyboardKey::KEY_F16},
		{"KEY_F17", KeyboardKey::KEY_F17},
		{"KEY_F18", KeyboardKey::KEY_F18},
		{"KEY_F19", KeyboardKey::KEY_F19},
		{"KEY_F20", KeyboardKey::KEY_F20},
		{"KEY_F21", KeyboardKey::KEY_F21},
		{"KEY_F22", KeyboardKey::KEY_F22},
		{"KEY_F23", KeyboardKey::KEY_F23},
		{"KEY_F24", KeyboardKey::KEY_F24},
		{"KEY_SEMICOLON", KeyboardKey::KEY_SEMICOLON},
		{"KEY_PLUS", KeyboardKey::KEY_EQUAL},
		{"KEY_COMMA", KeyboardKey::KEY_COMMA},
		{"KEY_MINUS", KeyboardKey::KEY_MINUS},
		{"KEY_PERIOD", KeyboardKey::KEY_PERIOD},
		{"KEY_FORWARDSLASH", KeyboardKey::KEY_FORWARDSLASH},
		{"KEY_GRAVE", KeyboardKey::KEY_GRAVE},
		{"KEY_LEFTBRACKET", KeyboardKey::KEY_LEFTBRACKET},
		{"KEY_BACKWARDSLASH", KeyboardKey::KEY_BACKWARDSLASH},
		{"KEY_RIGHTBRACKET", KeyboardKey::KEY_RIGHTBRACKET},
		{"KEY_QUOTE", KeyboardKey::KEY_QUOTE},
	};

	static inline const string META_KEYWORD = "META";
	static inline const string EXECUTE_KEYWORD = "EXECUTE";
	static inline const string LOOP_KEYWORD = "LOOP";
	static inline const string CONTINUE_KEYWORD = "CONTINUE";
	static inline const string BREAK_KEYWORD = "BREAK";
	static inline const string IF_KEYWORD = "IF";
	static inline const string ELIF_KEYWORD = "ELIF";
	static inline const string ELSE_KEYWORD = "ELSE";
	static inline const string GLOBAL_KEYWORD = "GLOB";
	static inline const string CONST_KEYWORD = "CONST";
	static inline const string EDIT_KEYWORD = "EDIT";
	static inline const string LIST_KEYWORD = "LST";
	static inline const string STRING_KEYWORD = "STR";
	static inline const string DECIMAL_KEYWORD = "DEC";
	static inline const string INTEGER_KEYWORD = "INT";
	static inline const string BOOLEAN_KEYWORD = "BOL";
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
	static inline const string MODULO_KEYWORD = "MOD";
	static inline const string NEGATION_KEYWORD = "NEG";
	static inline const string CASTING_KEYWORD = "CAST";
	static inline const string PUSHING_KEYWORD = "PUSH";
	static inline const string PULLING_KEYWORD = "PULL";
	static inline const string PASS_KEYWORD = "PASS";

	static inline constexpr unsigned int SPACES_PER_INDENT = 4;
	static inline constexpr unsigned int MAX_ITERATIONS_PER_LOOP = 1000;
	static inline constexpr unsigned int MAX_EXECUTION_DEPTH = 10;

	unordered_map<string, float> _debuggingTimes = {};
	unordered_map<unsigned int, unordered_map<string, shared_ptr<ScriptVariable>>> _localVariables = {};
	unordered_map<string, shared_ptr<ScriptVariable>> _globalVariables = {};

	vector<string> _currentScriptIdsStack = {};
	vector<string> _lineStringStreams = {};
	vector<string> _initializeScriptIds = {};
	vector<string> _updateScriptIds = {};
	vector<string> _terminateScriptIds = {};
	vector<unsigned int> _currentLineIndexStack = {};

	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<Script> _script = nullptr;
	shared_ptr<SkyEditor> _skyEditor = nullptr;
	shared_ptr<TerrainEditor> _terrainEditor = nullptr;
	shared_ptr<WaterEditor> _waterEditor = nullptr;
	shared_ptr<ModelEditor> _modelEditor = nullptr;
	shared_ptr<Quad3dEditor> _quad3dEditor = nullptr;
	shared_ptr<Text3dEditor> _text3dEditor = nullptr;
	shared_ptr<Quad2dEditor> _quad2dEditor = nullptr;
	shared_ptr<Text2dEditor> _text2dEditor = nullptr;
	shared_ptr<Animation2dEditor> _animation2dEditor = nullptr;
	shared_ptr<Animation3dEditor> _animation3dEditor = nullptr;
	shared_ptr<SoundEditor> _soundEditor = nullptr;
	shared_ptr<WorldEditor> _worldEditor = nullptr;
	shared_ptr<CustomWorldBuilder> _customWorldBuilder = nullptr;
	shared_ptr<WorldHelper> _worldHelper = nullptr;

	string _currentProjectId = "";
	string _initEntryId = "";
	string _updateEntryId = "";
	string _terminateEntryId = "";

	unsigned int _engineFunctionCallCount = 0;
	unsigned int _executionDepth = 0;

	bool _hasThrownError = false;
	bool _mustStopApplication = false;
	bool _hasPassedLoopStatement = false;
	bool _hasPassedIfStatement = false;
	bool _hasPassedElifStatement = false;
	bool _hasPassedElseStatement = false;
	bool _mustIgnoreDeeperScope = false;
	bool _isDebugging = false;
	bool _isExecutingInitialization = false;
	bool _isExecutingUpdate = false;
	bool _isExecutingTerminate = false;
};