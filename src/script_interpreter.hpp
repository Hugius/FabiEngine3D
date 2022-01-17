#pragma once

#include "script.hpp"
#include "script_type.hpp"
#include "script_value.hpp"
#include "script_variable.hpp"
#include "script_condition_statement.hpp"
#include "sky_editor.hpp"
#include "terrain_editor.hpp"
#include "water_editor.hpp"
#include "model_editor.hpp"
#include "billboard_editor.hpp"
#include "quad_editor.hpp"
#include "text_editor.hpp"
#include "animation3d_editor.hpp"
#include "animation2d_editor.hpp"
#include "sound_editor.hpp"
#include "world_editor.hpp"

class ScriptInterpreter final
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void inject(shared_ptr<Script> script);
	void inject(shared_ptr<SkyEditor> skyEditor);
	void inject(shared_ptr<TerrainEditor> terrainEditor);
	void inject(shared_ptr<WaterEditor> waterEditor);
	void inject(shared_ptr<ModelEditor> modelEditor);
	void inject(shared_ptr<BillboardEditor> billboardEditor);
	void inject(shared_ptr<QuadEditor> quadEditor);
	void inject(shared_ptr<TextEditor> textEditor);
	void inject(shared_ptr<Animation2dEditor> animation2dEditor);
	void inject(shared_ptr<Animation3dEditor> animation3dEditor);
	void inject(shared_ptr<SoundEditor> soundEditor);
	void inject(shared_ptr<WorldEditor> worldEditor);

	void setCurrentProjectID(const string& projectID);
	void load();
	void executeInitializeScripts();
	void executeUpdateScripts(bool isDebugging);
	void executeTerminateScripts();
	void unload();

	const bool hasThrownError() const;
	const bool gameMustStop() const;

private:
	void _executeScript(const string& scriptID, ScriptType scriptType);
	void _processVariableCreation(const string& scriptLine, ScriptVariableScope scope);
	void _processVariableAlteration(const string& scriptLine);
	void _processVariableArithmetic(const string& scriptLine);
	void _processVariableTypecast(const string& scriptLine);
	void _processListPush(const string& scriptLine);
	void _processListPull(const string& scriptLine);
	void _throwScriptError(const string& message);
	void _checkEngineWarnings(unsigned int lastLoggerMessageCount);
	void _performArithmeticOperation(ScriptValue& leftValue, const string& operatorString, ScriptValue& rightValue);

	const string _limitIntegerString(const string& valueString) const;
	const string _limitDecimalString(const string& valueString) const;

	const int _extractListIndexFromString(const string& valueString, bool& isAccessingList);

	const unsigned int _countLeadingSpaces(const string& scriptLineText);

	const bool _isListValue(const string& valueString) const;
	const bool _isStringValue(const string& valueString) const;
	const bool _isDecimalValue(const string& valueString) const;
	const bool _isIntegerValue(const string& valueString) const;
	const bool _isBooleanValue(const string& valueString) const;
	const bool _isLocalVariableExisting(const string& variableID);
	const bool _isGlobalVariableExisting(const string& variableID) const;
	const bool _checkConditionString(const string& conditionString);
	const bool _validateCondition(ScriptValue& firstValue, const string& comparisonOperator, ScriptValue& secondValue);
	const bool _compareValues(ScriptValue& firstValue, const string& comparisonOperator, ScriptValue& secondValue) const;
	const bool _validateListIndex(const ScriptVariable& list, unsigned int index);
	const bool _validateArgumentCount(const vector<ScriptValue>& values, unsigned int count);
	const bool _validateArgumentTypes(const vector<ScriptValue>& values, const vector<ScriptValueType>& types);
	const bool _executeFe3dSkySetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dSkyGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dTerrainSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dTerrainGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dWaterSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dWaterGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dModelSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dModelGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dBillboardSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dBillboardGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dAabbSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dAabbGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dQuadSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dQuadGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dTextSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dTextGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dPointlightSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dPointlightGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dSpotlightSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dSpotlightGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dReflectionSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dReflectionGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dAnimation3dSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dAnimation3dGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dAnimation2dSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dAnimation2dGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dSound2dSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dSound2dGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dSound3dSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dSound3dGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dLightingSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dLightingGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dGraphicsSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dGraphicsGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dWorldSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dWorldGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dInputGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dCameraSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dCameraGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dRaycastSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dRaycastGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dCollisionSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dCollisionGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dServerSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dServerGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dClientSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dClientGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dFilesystemSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dFilesystemGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dMiscSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _executeFe3dMiscGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues);
	const bool _validateFe3dSky();
	const bool _validateFe3dTerrain();
	const bool _validateFe3dWater();
	const bool _validateFe3dModel(const string& ID, bool isTemplate);
	const bool _validateFe3dModelPart(const string& modelID, const string& partID);
	const bool _validateFe3dBillboard(const string& ID, bool isTemplate);
	const bool _validateFe3dSound3d(const string& ID, bool isTemplate);
	const bool _validateFe3dSound2d(const string& ID, bool isTemplate);
	const bool _validateFe3dAabb(const string& ID);
	const bool _validateFe3dQuad(const string& ID, bool isTemplate);
	const bool _validateFe3dText(const string& ID, bool isTemplate);
	const bool _validateFe3dPointlight(const string& ID);
	const bool _validateFe3dSpotlight(const string& ID);
	const bool _validateFe3dReflection(const string& ID);
	const bool _validateFe3dAnimation2d(const string& ID);
	const bool _validateFe3dAnimation3d(const string& ID);
	const bool _validateFe3dID(const string& ID);
	const bool _validateScopeChange(unsigned int countedSpaces, const string& scriptLineText, unsigned int& scopeDepth);
	const bool _validateKeyInputString(const string& inputString);
	const bool _validateMouseInputString(const string& inputString);
	const bool _validateSavesDirectory() const;

	const vector<ScriptValue> _extractValuesFromListString(const string& listString);
	const vector<ScriptValue> _processFe3dFunctionCall(const string& scriptLine);
	const vector<ScriptValue> _processMathFunctionCall(const string& scriptLine);
	const vector<ScriptValue> _processMiscFunctionCall(const string& scriptLine);
	ScriptVariable& _getLocalVariable(const string& variableID);
	ScriptVariable& _getGlobalVariable(const string& variableID);
	ScriptConditionStatement* _getLastConditionStatement(vector<ScriptConditionStatement>& statements, unsigned int scopeDepth) const;

	map<string, float> _debuggingTimes;

	unordered_map<unsigned int, unordered_map<string, ScriptVariable>> _localVariables;
	unordered_map<string, ScriptVariable> _globalVariables;

	vector<string> _currentScriptIDsStack;
	vector<string> _lineStringStreams;
	vector<string> _initializeScriptIDs;
	vector<string> _updateScriptIDs;
	vector<string> _terminateScriptIDs;
	vector<unsigned int> _currentLineIndexStack;

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
	string _currentProjectID = "";
	string _initEntryID = "";
	string _updateEntryID = "";
	string _terminateEntryID = "";

	static inline const unsigned int SPACES_PER_INDENT = 4;
	static inline const unsigned int MAX_ITERATIONS_PER_LOOP = 1000;
	static inline const unsigned int MAX_EXECUTION_DEPTH = 10;
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

	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<Script> _script = nullptr;
	shared_ptr<SkyEditor> _skyEditor = nullptr;
	shared_ptr<TerrainEditor> _terrainEditor = nullptr;
	shared_ptr<WaterEditor> _waterEditor = nullptr;
	shared_ptr<ModelEditor> _modelEditor = nullptr;
	shared_ptr<BillboardEditor> _billboardEditor = nullptr;
	shared_ptr<QuadEditor> _quadEditor = nullptr;
	shared_ptr<TextEditor> _textEditor = nullptr;
	shared_ptr<Animation2dEditor> _animation2dEditor = nullptr;
	shared_ptr<Animation3dEditor> _animation3dEditor = nullptr;
	shared_ptr<SoundEditor> _soundEditor = nullptr;
	shared_ptr<WorldEditor> _worldEditor = nullptr;

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
		{"BUTTON_RIGHT", InputType::MOUSE_BUTTON_RIGHT}
	};
};