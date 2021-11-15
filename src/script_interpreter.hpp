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
#include "animation_editor.hpp"
#include "billboard_editor.hpp"
#include "audio_editor.hpp"
#include "world_editor.hpp"

class ScriptInterpreter final
{
public:
	ScriptInterpreter(FabiEngine3D& fe3d, Script& script, SkyEditor& skyEditor, TerrainEditor& terrainEditor,
					  WaterEditor& waterEditor, ModelEditor& modelEditor, AnimationEditor& animationEditor,
					  BillboardEditor& billboardEditor, AudioEditor& audioEditor, WorldEditor& worldEditor);

	// Voids
	void setCurrentProjectID(const string& projectID);
	void load();
	void executeInitialization();
	void executeUpdate(bool debug);
	void executeDestruction();
	void unload();

	// Booleans
	const bool hasThrownError() const;
	const bool gameMustStop() const;

private:
	// Voids
	void _executeScript(const string& scriptID, ScriptType scriptType);
	void _processVariableCreation(const string& scriptLine, ScriptVariableScope scope);
	void _processVariableAlteration(const string& scriptLine);
	void _processVariableArithmetic(const string& scriptLine);
	void _processVariableTypecast(const string& scriptLine);
	void _processListPush(const string& scriptLine);
	void _processListPull(const string& scriptLine);
	void _throwScriptError(const string& message);
	void _checkEngineWarnings(unsigned int lastLoggerMessageCount);

	// Strings
	const string _limitIntegerString(const string& valueString) const;
	const string _limitDecimalString(const string& valueString) const;

	// Vectors
	const Vec3 _extractVec3FromString(const string& valueString);
	const Ivec3 _extractVec3PartFromString(const string& valueString) const;
	const Vec2 _convertGuiPositionToViewport(Vec2 position) const;
	const Vec2 _convertGuiPositionFromViewport(Vec2 position) const;
	const Vec2 _convertGuiSizeToViewport(Vec2 size) const;
	const Vec2 _convertGuiSizeFromViewport(Vec2 size) const;

	// Integers
	const int _extractListIndexFromString(const string& valueString, bool& isAccessingList);
	const unsigned int _countFrontSpaces(const string& scriptLineText);

	// Booleans
	const bool _isListValue(const string& valueString) const;
	const bool _isVec3Value(const string& valueString) const;
	const bool _isStringValue(const string& valueString) const;
	const bool _isDecimalValue(const string& valueString) const;
	const bool _isIntegerValue(const string& valueString) const;
	const bool _isBooleanValue(const string& valueString) const;
	const bool _isLocalVariableExisting(const string& variableID);
	const bool _isGlobalVariableExisting(const string& variableID) const;
	const bool _checkConditionString(const string& conditionString);
	const bool _validateCondition(ScriptValue& firstValue, const string& comparisonOperator, ScriptValue& secondValue);
	const bool _compareValues(ScriptValue& firstValue, const string& comparisonOperator, ScriptValue& secondValue) const;
	const bool _validateListIndex(ScriptVariable& list, unsigned int index);
	const bool _validateListValueCount(const vector<ScriptValue>& values, unsigned int count);
	const bool _validateListValueTypes(const vector<ScriptValue>& values, const vector<ScriptValueType>& types);
	const bool _executeFe3dInputGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dCameraSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dCameraGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dRaycastSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dRaycastGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dCollisionSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dCollisionGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dSkySetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dSkyGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dTerrainSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dTerrainGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dWaterSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dWaterGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dModelSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dModelGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dBillboardSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dBillboardGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dAabbSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dAabbGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dPointlightSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dPointlightGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dSpotlightSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dSpotlightGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dReflectionSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dReflectionGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dImageSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dImageGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dTextSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dTextGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dSoundSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dSoundGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dLightingSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dLightingGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dGraphicsSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dGraphicsGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dMusicSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dMusicGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dFilesystemSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dFilesystemGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dWorldSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dWorldGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dServerSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dServerGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dClientSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dClientGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dMiscSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _executeFe3dMiscGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues);
	const bool _validateFe3dSky();
	const bool _validateFe3dTerrain();
	const bool _validateFe3dWater();
	const bool _validateFe3dModel(const string& ID, bool isPreview);
	const bool _validateFe3dBillboard(const string& ID, bool isPreview);
	const bool _validateFe3dSound(const string& ID, bool isPreview);
	const bool _validateFe3dAabb(const string& ID);
	const bool _validateFe3dPointlight(const string& ID);
	const bool _validateFe3dSpotlight(const string& ID);
	const bool _validateFe3dReflection(const string& ID);
	const bool _validateFe3dImage(const string& ID);
	const bool _validateFe3dText(const string& ID);
	const bool _validateScopeChange(unsigned int countedSpaces, const string& scriptLineText, unsigned int& scopeDepth);
	const bool _validateKeyInputString(const string& inputString);
	const bool _validateMouseInputString(const string& inputString);
	const bool _validateSavesDirectory() const;

	// Miscellaneous
	const vector<ScriptValue> _extractValuesFromListString(const string& listString);
	const vector<ScriptValue> _processEngineFunctionCall(const string& scriptLine);
	const vector<ScriptValue> _processMathematicalFunctionCall(const string& scriptLine);
	const vector<ScriptValue> _processMiscellaneousFunctionCall(const string& scriptLine);
	ScriptVariable& _getLocalVariable(const string& variableID);
	ScriptVariable& _getGlobalVariable(const string& variableID);
	ScriptConditionStatement* _getLastConditionStatement(vector<ScriptConditionStatement>& statements, unsigned int scopeDepth) const;

	// Strings
	static inline const string META_KEYWORD = "META";
	static inline const string EXECUTE_KEYWORD = "EXEC";
	static inline const string LOOP_KEYWORD = "LOOP";
	static inline const string CONTINUE_KEYWORD = "CONTINUE";
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
	vector<string> _currentScriptIDsStack;
	vector<string> _lineStringStreams;
	vector<string> _initScriptIDs;
	vector<string> _updateScriptIDs;
	vector<string> _destroyScriptIDs;
	string _currentProjectID = "";
	string _initEntryID = "";
	string _updateEntryID = "";
	string _destroyEntryID = "";

	// Decimals
	map<string, float> _debuggingTimes;

	// Integers
	static inline const unsigned int SPACES_PER_INDENT = 4;
	static inline const unsigned int MAX_ITERATIONS_PER_LOOP = 1000;
	static inline const unsigned int MAX_EXECUTION_DEPTH = 10;
	vector<unsigned int> _currentLineIndexStack;
	unsigned int _engineFunctionCallCount = 0;
	unsigned int _executionDepth = 0;

	// Booleans
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
	bool _isExecutingDestruction = false;

	// Miscellaneous
	unordered_map<unsigned int, unordered_map<string, ScriptVariable>> _localVariables;
	unordered_map<string, ScriptVariable> _globalVariables;
	FabiEngine3D& _fe3d;
	Script& _script;
	SkyEditor& _skyEditor;
	TerrainEditor& _terrainEditor;
	WaterEditor& _waterEditor;
	ModelEditor& _modelEditor;
	AnimationEditor& _animationEditor;
	BillboardEditor& _billboardEditor;
	AudioEditor& _audioEditor;
	WorldEditor& _worldEditor;
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