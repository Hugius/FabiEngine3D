#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "script.hpp"
#include "script_executor.hpp"

class ScriptEditor final
{
public:
	ScriptEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, SceneEditor& sceneEditor, ModelEditor& modelEditor, 
		AnimationEditor& animationEditor, BillboardEditor& billboardEditor);
	~ScriptEditor() = default;

	void initializeGUI();
	void load();
	void unload();
	void update();
	void setCurrentProjectName(const string & projectName);
	void loadScriptsFromFile();
	void saveScriptsToFile();

	ScriptExecutor& getScriptExecutor(bool reloadScript);

	bool isLoaded();
	bool isWritingScript();

private:
	void _updateGUI();
	void _updateTextWriter();
	void _updateTextSelector(string& newCharacters, unsigned int& cursorLineIndex,
		unsigned int& cursorCharIndex, int& hoveredLineIndex, bool& textHasChanged);
	void _updateMiscellaneous();
	void _reloadScriptTextDisplay(bool reloadAabbs);
	void _copySelectedText();

	// Core variables
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
	Script _script;
	ScriptExecutor _scriptExecutor;

	// Editor variables
	vector<string> _scriptFileNamesToDelete;
	vector<string> _copyClipboard;
	InputType _activeActionKey = InputType::NONE;
	string _currentProjectName = "";
	string _currentScriptFileID = "";
	float _scrollingAcceleration = 0.0f;
	bool _isEditorLoaded = false;
	bool _isScriptLoadedFromFile = false;
	bool _isWritingScript = false;
	bool _singleActionAllowed = true;
	bool _continuousActionAllowed = false;
	bool _wasGuiFocused = false;
	bool _hasClickedLMB = false;
	int _firstSelectedLineIndex = -1;
	int _lastSelectedLineIndex = -1;
	unsigned int _passedFrames = 0;
	
	// Editor constants
	const string _fontPath = "engine\\fonts\\font.ttf";
	const Vec3 _cameraStartingPosition = Vec3(0.0f, 0.0f, 10.0f);
	const Vec3 _scriptTextStartingPosition = Vec3(-11.0f, 6.0f, 0.5f);
	const Vec3 _lineNumberColor = Vec3(0.0f, 1.0f, 0.0f);
	const Vec3 _characterColor = Vec3(1.0f);
	const Vec3 _selectionColor = Vec3(0.25f);
	const Vec2 _textCharacterSize = Vec2(0.25f, 0.75f);
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
	const float _horizontalLineOffset = 1.0f;
	const float _cameraOffset = (_verticalLineOffset * (_maxVisibleLines / 2.0f)) - (_textCharacterSize.y / 2.0f);
	const float _aabbDepth = 0.05f;
	const string _allWritableCharacters = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*().,/;\'[]\\-=><?:\"{}|_+";
	const string _letterCharacters = " abcdefghijklmnopqrstuvwxyz";
	const vector<pair<char, char>> _numberCharacters =
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
	const vector<pair<char, char>> _specialCharacters =
	{
		{'.', '>'  },
		{',', '<'  },
		{'/', '?'  },
		{';', ':'  },
		{'\'', '\"'},
		{'[', '{'  },
		{']', '}'  },
		{'\\', '|' },
		{'-', '_'  },
		{'=', '+'  }
	};
	const vector<InputType> _actionKeys =
	{ 
		InputType::KEY_ENTER, InputType::KEY_BACKSPACE, InputType::KEY_DELETE, 
		InputType::KEY_LEFT, InputType::KEY_RIGHT, InputType::KEY_UP, InputType::KEY_DOWN
	};
};