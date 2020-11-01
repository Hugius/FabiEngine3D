#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "script.hpp"
#include "script_executor.hpp"

class ScriptEditor final
{
public:
	ScriptEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, SceneEditor& sceneEditor);
	~ScriptEditor() = default;

	void initializeGUI();
	void load();
	void save();
	void unload();
	void update();
	void setCurrentProjectName(const string & projectName);

	ScriptExecutor& getScriptExecutor();

	bool isLoaded();

private:
	void _updateGUI();
	void _updateTextWriter();
	void _updateMiscellaneous();
	void _loadScriptsFromFile();
	void _saveScriptToFile();
	void _reloadScriptTextDisplay();

	// Core variables
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
	Script _script;
	ScriptExecutor _scriptExecutor;

	// Editor variables
	string _currentProjectName = "";
	string _currentScriptFileID = "";
	float _scrollingAcceleration = 0.0f;
	bool _isLoaded = false;
	bool _isScriptLoadedFromFile = false;
	bool _isWritingScript = false;

	// Miscellaneous variables
	vector<string> _scriptFileNamesToDelete;
	
	// Editor constants
	const string _fontPath = "engine\\fonts\\lucida.ttf";
	const vec3 _cameraStartingPosition = vec3(0.0f, 0.0f, 10.0f);
	const vec3 _scriptTextStartingPosition = vec3(-11.0f, 6.0f, 0.5f);
	const vec3 _lineNumberColor = vec3(0.0f, 1.0f, 0.0f);
	const vec3 _characterColor = vec3(1.0f);
	const vec2 _textCharacterSize = vec2(0.25f, 0.75f);
	const unsigned int _continuousTextActionFrameMinimum = 75;
	const unsigned int _continuousTextActionInterval = 5;
	const unsigned int _maxPassedBarFrames = 50;
	const unsigned int _maxCharactersPerLine = 88;
	const unsigned int _maxLineAmount = 100;
	const unsigned int _maxVisibleLines = 13;
	const float _scrollingSpeed = 0.1f;
	const float _maxScrollingAcceleration = 10.0f;
	const float _horizontalCharacterOffset = 0.25f;
	const float _verticalLineOffset = 1.0f;
	const float _horizontalLineOffset = 0.5f;
	const float _cameraOffset = (_verticalLineOffset * (_maxVisibleLines / 2.0f)) - (_textCharacterSize.y / 2.0f);
	const string letterCharacters = " abcdefghijklmnopqrstuvwxyz";
	const map<char, char> numberCharacterMap =
	{
		{'0', ')'},
		{'1', '!'},
		{'2', '@'},
		{'3', '#'},
		{'4', '$'},
		{'5', '%'},
		{'6', '^'},
		{'7', '&'},
		{'8', '*'},
		{'9', '('}
	};
	const map<char, char> specialCharacterMap =
	{
		{'.', '>'},
		{',', '<'},
		{'/', '?'},
		{';', ':'},
		{'\'', '\"'},
		{'[', '{'},
		{']', '}'},
		{'\\', '|'},
		{'-', '_'},
		{'=', '+'}
	};
};