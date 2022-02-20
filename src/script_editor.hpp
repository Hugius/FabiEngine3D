#pragma once

#include "base_editor.hpp"
#include "script.hpp"

class ScriptEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void inject(shared_ptr<Script> script);

	void update();

	const bool loadScriptFiles(bool isLoggingEnabled);
	const bool saveScriptFiles();
	const bool isWritingScript() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateGUI();
	void _updateTextWriter();
	void _updateTextSelector(string& newCharacters, unsigned int& cursorLineIndex, unsigned int& cursorCharIndex, int& hoveredLineIndex, bool& textHasChanged);
	void _updateScriptFileCreating();
	void _updateScriptFileChoosing();
	void _updateScriptFileRenaming();
	void _updateScriptSearching();
	void _updateMiscellaneous();
	void _reloadScriptTextDisplay(bool reloadAabbs);
	void _copySelectedText();

	static inline const string FONT_MAP_PATH = "engine\\assets\\image\\font_map\\font.tga";
	static inline const string ALPHABET_CHARACTERS = " abcdefghijklmnopqrstuvwxyz";
	vector<string> _scriptFileNamesToDelete;
	vector<string> _copyClipboard;
	string _currentScriptFileId = "";

	static inline const fvec3 CAMERA_POSITION = fvec3(0.0f, 0.0f, 10.0f);
	static inline const fvec3 SCRIPT_TEXT_STARTING_POSITION = fvec3(-11.0f, 6.0f, 0.5f);
	static inline const fvec3 SELECTION_COLOR = fvec3(0.075f);
	static inline const fvec3 LINE_NUMBER_COLOR = fvec3(0.25f, 0.25f, 1.0f);
	static inline const fvec3 SEPARATOR_COLOR = fvec3(1.0f, 0.85f, 0.0f);
	static inline const fvec3 DEFAULT_TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 COMMENT_TEXT_COLOR = fvec3(0.0f, 0.75f, 0.0f);

	static inline const fvec2 TEXT_CHARACTER_SIZE = fvec2(0.25f, 0.75f);

	static inline constexpr float CW = 0.115f;
	static inline constexpr float CH = 0.0875f;
	static inline constexpr float SCROLLING_SPEED = 0.1f;
	static inline constexpr float MAX_SCROLLING_ACCELERATION = 10.0f;
	static inline constexpr float HORIZONTAL_CHARACTER_OFFSET = 0.25f;
	static inline constexpr float HORIZONTAL_LINE_OFFSET = 1.0f;
	static inline constexpr float VERTICAL_LINE_OFFSET = 1.0f;
	static inline constexpr float CAMERA_OFFSET = 0.25f;
	static inline constexpr float CAMERA_FOV = 71.0f;
	static inline constexpr float SELECTION_DEPTH = 0.001f;
	static inline constexpr float AABB_DEPTH = 0.01f;
	float _scrollingAcceleration = 0.0f;

	int _firstSelectedLineIndex = -1;
	int _lastSelectedLineIndex = -1;

	static inline constexpr unsigned int CONTINUOUS_TEXT_ACTION_FRAME_MINIMUM = 75;
	static inline constexpr unsigned int CONTINUOUS_TEXT_ACTION_INTERVAL = 5;
	static inline constexpr unsigned int MAX_PASSED_BAR_FRAMES = 50;
	static inline constexpr unsigned int MAX_CHARACTERS_PER_LINE = 88;
	static inline constexpr unsigned int MAX_LINE_COUNT = 100;
	static inline constexpr unsigned int MAX_VISIBLE_LINES = 13;
	static inline constexpr unsigned int BLOOM_QUALITY = 1;
	unsigned int _passedFrames = 0;

	static inline const unordered_map<char, char> NUMBER_CHARACTERS =
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
	static inline const unordered_map<char, char> SPECIAL_CHARACTERS =
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

	bool _isScriptLoadedFromFile = false;
	bool _isWritingScript = false;
	bool _isSingleActionAllowed = true;
	bool _isContinuousActionAllowed = false;
	bool _wasGuiFocused = false;
	bool _hasClickedLMB = false;
	bool _isCreatingScriptFile = false;
	bool _isChoosingScriptFile = false;
	bool _isRenamingScriptFile = false;
	bool _isSearchingScriptFile = false;

	InputType _activeActionKey = InputType::NONE;
	static inline const vector<InputType> ACTION_KEYS =
	{
		InputType::KEY_ENTER,
		InputType::KEY_BACKSPACE,
		InputType::KEY_DELETE,
		InputType::KEY_LEFT,
		InputType::KEY_RIGHT,
		InputType::KEY_UP,
		InputType::KEY_DOWN
	};

	shared_ptr<Script> _script = nullptr;
};