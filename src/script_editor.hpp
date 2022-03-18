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
	void _updateTextSelector();
	void _updateScriptFileCreating();
	void _updateScriptFileChoosing();
	void _updateScriptFileRenaming();
	void _updateScriptSearching();
	void _updateDisplay();
	void _updateCamera();
	void _updateMiscellaneous();
	void _createScriptDisplayEntities();
	void _deleteScriptDisplayEntities();

	static inline const string FONT_MAP_PATH = "engine\\assets\\image\\font_map\\font.tga";
	static inline const string ALPHABET_CHARACTERS = " abcdefghijklmnopqrstuvwxyz";
	vector<string> _scriptFileNamesToDelete;
	vector<string> _copyClipboard;
	vector<string> _loadedQuadIds;
	vector<string> _loadedTextIds;
	vector<string> _loadedAabbIds;
	string _currentScriptFileId = "";

	static inline const fvec3 TEXT_STARTING_POSITION = fvec3(-12.0f, 6.0, 0.0f);
	static inline const fvec3 LINE_NUMBER_COLOR = fvec3(0.25f, 0.25f, 1.0f);
	static inline const fvec3 SEPARATOR_COLOR = fvec3(1.0f, 0.85f, 0.0f);
	static inline const fvec3 SELECTION_COLOR = fvec3(0.1f, 0.1f, 0.1f);
	static inline const fvec3 DEFAULT_TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 COMMENT_TEXT_COLOR = fvec3(0.0f, 0.75f, 0.0f);

	static inline const fvec2 TEXT_CHARACTER_SIZE = fvec2(0.25f, 0.75f);

	static inline constexpr float CW = 0.115f;
	static inline constexpr float CH = 0.0875f;
	static inline constexpr float CHARACTER_OFFSET = 0.25f;
	static inline constexpr float HORIZONTAL_LINE_OFFSET = 1.0f;
	static inline constexpr float VERTICAL_LINE_OFFSET = 1.0f;
	static inline constexpr float CAMERA_FOV = 70.0f;
	static inline constexpr float CAMERA_YAW = 270.0f;
	static inline constexpr float CAMERA_PITCH = 0.0f;
	static inline constexpr float AABB_DEPTH = 0.0001f;
	static inline constexpr float CAMERA_DISTANCE = 10.0f;

	static inline constexpr unsigned int MAX_LINE_COUNT = 99;
	static inline constexpr unsigned int BLOOM_QUALITY = 1;

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

	string _characterSelectionRootAabbId = "";

	bool _isScriptLoadedFromFile = false;
	bool _isWritingScript = false;
	bool _isCreatingScriptFile = false;
	bool _isChoosingScriptFile = false;
	bool _isRenamingScriptFile = false;
	bool _isSearchingScriptFile = false;
	bool _hasTextChanged = false;

	shared_ptr<Script> _script = nullptr;
};