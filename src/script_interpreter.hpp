#pragma once

#include "sky_editor.hpp"
#include "terrain_editor.hpp"
#include "water_editor.hpp"
#include "model_editor.hpp"
#include "quad3d_editor.hpp"
#include "quad2d_editor.hpp"
#include "text3d_editor.hpp"
#include "text2d_editor.hpp"
#include "animation3d_editor.hpp"
#include "animation2d_editor.hpp"
#include "aabb_editor.hpp"
#include "pointlight_editor.hpp"
#include "spotlight_editor.hpp"
#include "captor_editor.hpp"
#include "sound3d_editor.hpp"
#include "sound2d_editor.hpp"
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
	void inject(shared_ptr<Quad2dEditor> quad2dEditor);
	void inject(shared_ptr<Text3dEditor> text3dEditor);
	void inject(shared_ptr<Text2dEditor> text2dEditor);
	void inject(shared_ptr<Animation3dEditor> animation3dEditor);
	void inject(shared_ptr<Animation2dEditor> animation2dEditor);
	void inject(shared_ptr<AabbEditor> aabbEditor);
	void inject(shared_ptr<PointlightEditor> pointlightEditor);
	void inject(shared_ptr<SpotlightEditor> spotlightEditor);
	void inject(shared_ptr<CaptorEditor> captorEditor);
	void inject(shared_ptr<Sound3dEditor> sound3dEditor);
	void inject(shared_ptr<Sound2dEditor> sound2dEditor);
	void inject(shared_ptr<WorldEditor> worldEditor);
	void inject(shared_ptr<CustomWorldBuilder> customWorldBuilder);
	void inject(shared_ptr<Duplicator> duplicator);
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
	void _processVariableCreation(const string & scriptLine, ScriptScopeType scope);
	void _processVariableAlteration(const string & scriptLine);
	void _processVariableArithmetic(const string & scriptLine);
	void _processVariableTypecast(const string & scriptLine);
	void _processListPush(const string & scriptLine);
	void _processListPull(const string & scriptLine);
	void _throwStartupError(const string & message);
	void _throwRuntimeError(const string & message);
	void _checkEngineWarnings(int lastLoggerMessageCount);
	void _performArithmeticOperation(shared_ptr<ScriptValue> leftValue, const string & operatorString, shared_ptr<ScriptValue> rightValue);

	const vector<shared_ptr<ScriptValue>> _extractValuesFromListString(const string & listString);
	const vector<shared_ptr<ScriptValue>> _processFe3dFunctionCall(const string & scriptLine);
	const vector<shared_ptr<ScriptValue>> _processMathFunctionCall(const string & scriptLine);
	const vector<shared_ptr<ScriptValue>> _processMiscFunctionCall(const string & scriptLine);

	const shared_ptr<ScriptVariable> _getLocalVariable(const string & variableId);
	const shared_ptr<ScriptVariable> _getGlobalVariable(const string & variableId) const;

	const string _limitIntegerString(const string & valueString) const;
	const string _limitDecimalString(const string & valueString) const;

	const int _countLeadingSpaces(const string & scriptLineText);
	const int _extractListIndexFromString(const string & valueString, bool & isAccessingList);
	const int _getLastConditionStatementIndex(const vector<ScriptConditionStatement> & statements, int scopeDepth) const;

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
	const bool _validateListIndex(shared_ptr<ScriptVariable> list, int index);
	const bool _validateArgumentCount(const vector<shared_ptr<ScriptValue>> & values, int count);
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
	const bool _executeFe3dCaptorSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
	const bool _executeFe3dCaptorGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues);
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
	const bool _validateFe3dSky(const string & skyId, bool isEditor);
	const bool _validateFe3dTerrain(const string & terrainId, bool isEditor);
	const bool _validateFe3dWater(const string & waterId, bool isEditor);
	const bool _validateFe3dModel(const string & modelId, bool isEditor);
	const bool _validateFe3dModelPart(const string & modelId, const string & partId);
	const bool _validateFe3dModelAabb(const string & modelId, const string & aabbId);
	const bool _validateFe3dQuad3d(const string & quad3dId, bool isEditor);
	const bool _validateFe3dQuad2d(const string & quad2dId, bool isEditor);
	const bool _validateFe3dText3d(const string & text3dId, bool isEditor);
	const bool _validateFe3dText2d(const string & text2dId, bool isEditor);
	const bool _validateFe3dAnimation3d(const string & animation3dId);
	const bool _validateFe3dAnimation2d(const string & animation2dId);
	const bool _validateFe3dAabb(const string & aabbId, bool isEditor);
	const bool _validateFe3dPointlight(const string & pointlightId, bool isEditor);
	const bool _validateFe3dSpotlight(const string & spotlightId, bool isEditor);
	const bool _validateFe3dCaptor(const string & captorId, bool isEditor);
	const bool _validateFe3dSound3d(const string & sound3dId, bool isEditor);
	const bool _validateFe3dSound2d(const string & sound2dId, bool isEditor);
	const bool _validateFe3dId(const string & id);
	const bool _validateScopeDepth(int currentLineScopeDepth, int & targetScopeDepth);
	const bool _validateKeyInputString(const string & inputString);
	const bool _validateMouseInputString(const string & inputString);
	const bool _validateSavesDirectory();

	static inline const unordered_map<string, MouseWheelType> mouse_wheel_types =
	{
		{"WHEEL_FORWARD", MouseWheelType::WHEEL_FORWARD},
		{"WHEEL_BACKWARD", MouseWheelType::WHEEL_BACKWARD},
	};
	static inline const unordered_map<string, MouseButtonType> mouse_button_types =
	{
		{"BUTTON_LEFT", MouseButtonType::BUTTON_LEFT},
		{"BUTTON_MIDDLE", MouseButtonType::BUTTON_MIDDLE},
		{"BUTTON_RIGHT", MouseButtonType::BUTTON_RIGHT},
	};
	static inline const unordered_map<string, KeyboardKeyType> keyboard_key_types =
	{
		{"KEY_BACKSPACE", KeyboardKeyType::KEY_BACKSPACE},
		{"KEY_TAB", KeyboardKeyType::KEY_TAB},
		{"KEY_ENTER", KeyboardKeyType::KEY_ENTER},
		{"KEY_SHIFT", KeyboardKeyType::KEY_SHIFT},
		{"KEY_CONTROL", KeyboardKeyType::KEY_CONTROL},
		{"KEY_ALT", KeyboardKeyType::KEY_ALT},
		{"KEY_CAPSLOCK", KeyboardKeyType::KEY_CAPSLOCK},
		{"KEY_ESCAPE", KeyboardKeyType::KEY_ESCAPE},
		{"KEY_SPACEBAR", KeyboardKeyType::KEY_SPACEBAR},
		{"KEY_PAGEUP", KeyboardKeyType::KEY_PAGEUP},
		{"KEY_PAGEDOWN", KeyboardKeyType::KEY_PAGEDOWN},
		{"KEY_END", KeyboardKeyType::KEY_END},
		{"KEY_HOME", KeyboardKeyType::KEY_HOME},
		{"KEY_LEFT", KeyboardKeyType::KEY_LEFT},
		{"KEY_UP", KeyboardKeyType::KEY_UP},
		{"KEY_RIGHT", KeyboardKeyType::KEY_RIGHT},
		{"KEY_DOWN", KeyboardKeyType::KEY_DOWN},
		{"KEY_INSERT", KeyboardKeyType::KEY_INSERT},
		{"KEY_DELETE", KeyboardKeyType::KEY_DELETE},
		{"KEY_0", KeyboardKeyType::KEY_0},
		{"KEY_1", KeyboardKeyType::KEY_1},
		{"KEY_2", KeyboardKeyType::KEY_2},
		{"KEY_3", KeyboardKeyType::KEY_3},
		{"KEY_4", KeyboardKeyType::KEY_4},
		{"KEY_5", KeyboardKeyType::KEY_5},
		{"KEY_6", KeyboardKeyType::KEY_6},
		{"KEY_7", KeyboardKeyType::KEY_7},
		{"KEY_8", KeyboardKeyType::KEY_8},
		{"KEY_9", KeyboardKeyType::KEY_9},
		{"KEY_A", KeyboardKeyType::KEY_A},
		{"KEY_B", KeyboardKeyType::KEY_B},
		{"KEY_C", KeyboardKeyType::KEY_C},
		{"KEY_D", KeyboardKeyType::KEY_D},
		{"KEY_E", KeyboardKeyType::KEY_E},
		{"KEY_F", KeyboardKeyType::KEY_F},
		{"KEY_G", KeyboardKeyType::KEY_G},
		{"KEY_H", KeyboardKeyType::KEY_H},
		{"KEY_I", KeyboardKeyType::KEY_I},
		{"KEY_J", KeyboardKeyType::KEY_J},
		{"KEY_K", KeyboardKeyType::KEY_K},
		{"KEY_L", KeyboardKeyType::KEY_L},
		{"KEY_M", KeyboardKeyType::KEY_M},
		{"KEY_N", KeyboardKeyType::KEY_N},
		{"KEY_O", KeyboardKeyType::KEY_O},
		{"KEY_P", KeyboardKeyType::KEY_P},
		{"KEY_Q", KeyboardKeyType::KEY_Q},
		{"KEY_R", KeyboardKeyType::KEY_R},
		{"KEY_S", KeyboardKeyType::KEY_S},
		{"KEY_T", KeyboardKeyType::KEY_T},
		{"KEY_U", KeyboardKeyType::KEY_U},
		{"KEY_V", KeyboardKeyType::KEY_V},
		{"KEY_W", KeyboardKeyType::KEY_W},
		{"KEY_X", KeyboardKeyType::KEY_X},
		{"KEY_Y", KeyboardKeyType::KEY_Y},
		{"KEY_Z", KeyboardKeyType::KEY_Z},
		{"KEY_NUMPAD0", KeyboardKeyType::KEY_NUMPAD0},
		{"KEY_NUMPAD1", KeyboardKeyType::KEY_NUMPAD1},
		{"KEY_NUMPAD2", KeyboardKeyType::KEY_NUMPAD2},
		{"KEY_NUMPAD3", KeyboardKeyType::KEY_NUMPAD3},
		{"KEY_NUMPAD4", KeyboardKeyType::KEY_NUMPAD4},
		{"KEY_NUMPAD5", KeyboardKeyType::KEY_NUMPAD5},
		{"KEY_NUMPAD6", KeyboardKeyType::KEY_NUMPAD6},
		{"KEY_NUMPAD7", KeyboardKeyType::KEY_NUMPAD7},
		{"KEY_NUMPAD8", KeyboardKeyType::KEY_NUMPAD8},
		{"KEY_NUMPAD9", KeyboardKeyType::KEY_NUMPAD9},
		{"KEY_MULTIPLY", KeyboardKeyType::KEY_MULTIPLY},
		{"KEY_ADD", KeyboardKeyType::KEY_ADD},
		{"KEY_SUBTRACT", KeyboardKeyType::KEY_SUBTRACT},
		{"KEY_DECIMAL", KeyboardKeyType::KEY_DECIMAL},
		{"KEY_DIVIDE", KeyboardKeyType::KEY_DIVIDE},
		{"KEY_F1", KeyboardKeyType::KEY_F1},
		{"KEY_F2", KeyboardKeyType::KEY_F2},
		{"KEY_F3", KeyboardKeyType::KEY_F3},
		{"KEY_F4", KeyboardKeyType::KEY_F4},
		{"KEY_F5", KeyboardKeyType::KEY_F5},
		{"KEY_F6", KeyboardKeyType::KEY_F6},
		{"KEY_F7", KeyboardKeyType::KEY_F7},
		{"KEY_F8", KeyboardKeyType::KEY_F8},
		{"KEY_F9", KeyboardKeyType::KEY_F9},
		{"KEY_F10", KeyboardKeyType::KEY_F10},
		{"KEY_F11", KeyboardKeyType::KEY_F11},
		{"KEY_F12", KeyboardKeyType::KEY_F12},
		{"KEY_F13", KeyboardKeyType::KEY_F13},
		{"KEY_F14", KeyboardKeyType::KEY_F14},
		{"KEY_F15", KeyboardKeyType::KEY_F15},
		{"KEY_F16", KeyboardKeyType::KEY_F16},
		{"KEY_F17", KeyboardKeyType::KEY_F17},
		{"KEY_F18", KeyboardKeyType::KEY_F18},
		{"KEY_F19", KeyboardKeyType::KEY_F19},
		{"KEY_F20", KeyboardKeyType::KEY_F20},
		{"KEY_F21", KeyboardKeyType::KEY_F21},
		{"KEY_F22", KeyboardKeyType::KEY_F22},
		{"KEY_F23", KeyboardKeyType::KEY_F23},
		{"KEY_F24", KeyboardKeyType::KEY_F24},
		{"KEY_SEMICOLON", KeyboardKeyType::KEY_SEMICOLON},
		{"KEY_PLUS", KeyboardKeyType::KEY_EQUAL},
		{"KEY_COMMA", KeyboardKeyType::KEY_COMMA},
		{"KEY_MINUS", KeyboardKeyType::KEY_MINUS},
		{"KEY_PERIOD", KeyboardKeyType::KEY_PERIOD},
		{"KEY_FORWARDSLASH", KeyboardKeyType::KEY_FORWARDSLASH},
		{"KEY_GRAVE", KeyboardKeyType::KEY_GRAVE},
		{"KEY_LEFTBRACKET", KeyboardKeyType::KEY_LEFTBRACKET},
		{"KEY_BACKWARDSLASH", KeyboardKeyType::KEY_BACKWARDSLASH},
		{"KEY_RIGHTBRACKET", KeyboardKeyType::KEY_RIGHTBRACKET},
		{"KEY_QUOTE", KeyboardKeyType::KEY_QUOTE},
	};

	static inline const string META_KEYWORD = "META";
	static inline const string EXIT_KEYWORD = "EXIT";
	static inline const string EXECUTE_KEYWORD = "EXECUTE";
	static inline const string LOOP_KEYWORD = "LOOP";
	static inline const string CONTINUE_KEYWORD = "CONTINUE";
	static inline const string BREAK_KEYWORD = "BREAK";
	static inline const string IF_KEYWORD = "IF";
	static inline const string ELIF_KEYWORD = "ELIF";
	static inline const string ELSE_KEYWORD = "ELSE";
	static inline const string GLOBAL_KEYWORD = "GLOB";
	static inline const string CONST_KEYWORD = "CNST";
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
	static inline const string ADD_KEYWORD = "ADD";
	static inline const string SUBTRACT_KEYWORD = "SUB";
	static inline const string MULTIPLY_KEYWORD = "MUL";
	static inline const string DIVIDE_KEYWORD = "DIV";
	static inline const string MODULO_KEYWORD = "MOD";
	static inline const string NEGATE_KEYWORD = "NEG";
	static inline const string CAST_KEYWORD = "CAST";
	static inline const string PUSH_KEYWORD = "PUSH";
	static inline const string PULL_KEYWORD = "PULL";
	static inline const string PASS_KEYWORD = "PASS";

	static inline constexpr float MIN_STRING_DECIMAL = -999999999.0f;
	static inline constexpr float MAX_STRING_DECIMAL = 999999999.0f;

	static inline constexpr int SPACES_PER_INDENT = 4;
	static inline constexpr int MAX_ITERATIONS_PER_LOOP = 1000;
	static inline constexpr int MAX_EXECUTION_DEPTH = 10;
	static inline constexpr int MIN_STRING_INTEGER = -999999999;
	static inline constexpr int MAX_STRING_INTEGER = 999999999;

	unordered_map<string, float> _debuggingTimes = {};
	unordered_map<int, unordered_map<string, shared_ptr<ScriptVariable>>> _localVariables = {};
	unordered_map<string, shared_ptr<ScriptVariable>> _globalVariables = {};

	vector<string> _currentScriptIdsStack = {};
	vector<string> _lineStringStreams = {};
	vector<string> _initializeScriptIds = {};
	vector<string> _updateScriptIds = {};
	vector<string> _terminateScriptIds = {};
	vector<int> _currentLineIndexStack = {};

	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<Script> _script = nullptr;
	shared_ptr<SkyEditor> _skyEditor = nullptr;
	shared_ptr<TerrainEditor> _terrainEditor = nullptr;
	shared_ptr<WaterEditor> _waterEditor = nullptr;
	shared_ptr<ModelEditor> _modelEditor = nullptr;
	shared_ptr<Quad3dEditor> _quad3dEditor = nullptr;
	shared_ptr<Quad2dEditor> _quad2dEditor = nullptr;
	shared_ptr<Text3dEditor> _text3dEditor = nullptr;
	shared_ptr<Text2dEditor> _text2dEditor = nullptr;
	shared_ptr<Animation3dEditor> _animation3dEditor = nullptr;
	shared_ptr<Animation2dEditor> _animation2dEditor = nullptr;
	shared_ptr<AabbEditor> _aabbEditor = nullptr;
	shared_ptr<PointlightEditor> _pointlightEditor = nullptr;
	shared_ptr<SpotlightEditor> _spotlightEditor = nullptr;
	shared_ptr<CaptorEditor> _captorEditor = nullptr;
	shared_ptr<Sound3dEditor> _sound3dEditor = nullptr;
	shared_ptr<Sound2dEditor> _sound2dEditor = nullptr;
	shared_ptr<WorldEditor> _worldEditor = nullptr;
	shared_ptr<CustomWorldBuilder> _customWorldBuilder = nullptr;
	shared_ptr<Duplicator> _duplicator = nullptr;

	string _currentProjectId = "";
	string _initEntryId = "";
	string _updateEntryId = "";
	string _terminateEntryId = "";

	int _engineFunctionCallCount = 0;
	int _executionDepth = 0;

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