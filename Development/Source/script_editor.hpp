#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "script.hpp"
#include "script_executor.hpp"

class ScriptEditor final
{
public:
	ScriptEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, SceneEditor& sceneEditor, ModelEditor& modelEditor, 
		AnimationEditor& animationEditor, BillboardEditor& billboardEditor, AudioEditor& audioEditor, EnvironmentEditor& environmentEditor);
	~ScriptEditor() = default;

	void load();
	void unload();
	void update();
	void setCurrentProjectID(const string & projectName);
	void loadScriptsFromFile();
	void saveScriptsToFile();

	ScriptExecutor& getScriptExecutor(bool reloadScript);

	bool isLoaded();
	bool isWritingScript();

private:
	void _loadGUI();
	void _unloadGUI();
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
	string _currentProjectID = "";
	string _currentScriptFileID = "";
	float _scrollingAcceleration = 0.0f;
	bool _isEditorLoaded = false;
	bool _isScriptLoadedFromFile = false;
	bool _isWritingScript = false;
	bool _isSingleActionAllowed = true;
	bool _isContinuousActionAllowed = false;
	bool _wasGuiFocused = false;
	bool _hasClickedLMB = false;
	int _firstSelectedLineIndex = -1;
	int _lastSelectedLineIndex = -1;
	unsigned int _passedFrames = 0;
	
	// Editor constants
	static inline const string FONT_PATH = "engine_assets\\fonts\\font.ttf";
	static inline const Vec3 DEFAULT_CAMERA_POSITION = Vec3(0.0f, 0.0f, 10.0f);
	static inline const Vec3 SCRIPT_TEXT_STARTING_POSITION = Vec3(-11.0f, 6.0f, 0.5f);
	static inline const Vec3 LINE_NUMBER_COLOR = Vec3(0.0f, 1.0f, 0.0f);
	static inline const Vec3 CHARACTER_COLOR = Vec3(1.0f);
	static inline const Vec3 SELECTION_COLOR = Vec3(0.15f);
	static inline const Vec3 SEPARATOR_COLOR = Vec3(1.0f, 0.85f, 0.0f);
	static inline const Vec2 TEXT_CHARACTER_SIZE = Vec2(0.25f, 0.75f);
	static inline const unsigned int CONTINUOUS_TEXT_ACTION_FRAME_MINIMUM = 75;
	static inline const unsigned int CONTINUOUS_TEXT_ACTION_INTERVAL = 5;
	static inline const unsigned int MAX_PASSED_BAR_FRAMES = 50;
	static inline const unsigned int MAX_CHARACTERS_PER_LINE = 88;
	static inline const unsigned int MAX_LINE_AMOUNT = 100;
	static inline const unsigned int MAX_VISIBLE_LINES = 13;
	static inline const float SCROLLING_SPEED = 0.1f;
	static inline const float MAX_SCROLLING_ACCELERATION = 10.0f;
	static inline const float HORIZONTAL_CHARACTER_OFFSET = 0.25f;
	static inline const float VERTICAL_LINE_OFFSET = 1.0f;
	static inline const float HORIZONTAL_LINE_OFFSET = 1.0f;
	static inline const float CAMERA_OFFSET = (VERTICAL_LINE_OFFSET * (MAX_VISIBLE_LINES / 2.0f)) - (TEXT_CHARACTER_SIZE.y / 2.0f);
	static inline const float AABB_DEPTH = 0.05f;
	static inline const string LETTER_CHARACTERS = " abcdefghijklmnopqrstuvwxyz";
	static inline const vector<pair<char, char>> NUMBER_CHARACTERS =
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
	static inline const vector<pair<char, char>> SPECIAL_CHARACTERS =
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
	static inline const vector<InputType> ACTION_KEYS =
	{ 
		InputType::KEY_ENTER, InputType::KEY_BACKSPACE, InputType::KEY_DELETE, 
		InputType::KEY_LEFT, InputType::KEY_RIGHT, InputType::KEY_UP, InputType::KEY_DOWN
	};
};