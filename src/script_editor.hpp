#pragma once

#include "base_editor.hpp"
#include "script.hpp"
#include "script_selection_type.hpp"

class ScriptEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void inject(shared_ptr<Script> script);

	const bool loadScriptFiles(bool isLoggingEnabled);
	const bool saveScriptFiles();
	const bool isWritingScript() const;

private:
	void _load();
	void _update();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMenu();
	void _updateTextWriter();
	void _updateTextSelector();
	void _updateScriptSearching();
	void _updateScriptFileCreating();
	void _updateScriptFileChoosing();
	void _updateScriptFileRenaming();
	void _updateScriptDeleting();
	void _updateDisplay();
	void _updateCamera();
	void _updateCursor();
	void _createDisplayContent();
	void _deleteDisplayContent();
	void _clearDisplay();
	void _clearSelection();

	static inline const string SELECTION_ID = "@@selection";
	static inline const string CARET_ID = "@@caret";
	static inline const string FONT_MAP_PATH = "engine\\assets\\image\\font_map\\font.tga";
	static inline const string CURSOR_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\cursor_caret.tga";

	static inline const fvec3 LINE_NUMBER_COLOR = fvec3(0.25f, 0.25f, 1.0f);
	static inline const fvec3 SEPARATOR_COLOR = fvec3(1.0f, 0.85f, 0.0f);
	static inline const fvec3 SELECTION_COLOR = fvec3(0.1f, 0.1f, 0.1f);
	static inline const fvec3 DEFAULT_TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 COMMENT_TEXT_COLOR = fvec3(0.0f, 0.75f, 0.0f);
	static inline const fvec3 ROOT_TEXT_POSITION = fvec3(-12.0f, 6.0, 0.0f);

	static inline const fvec2 CARET_SIZE = fvec2(0.25f, 0.75f);
	static inline const fvec2 CHAR_SIZE = fvec2(0.25f, 0.75f);

	static inline constexpr float CHAR_OFFSET = 0.25f;
	static inline constexpr float HORIZONTAL_LINE_OFFSET = 1.0f;
	static inline constexpr float VERTICAL_LINE_OFFSET = 1.0f;
	static inline constexpr float CAMERA_FOV = 70.0f;
	static inline constexpr float CAMERA_YAW = 270.0f;
	static inline constexpr float CAMERA_PITCH = 0.0f;
	static inline constexpr float AABB_DEPTH = 0.0001f;
	static inline constexpr float CAMERA_DISTANCE = 10.0f;
	static inline constexpr float BLOOM_INTENSITY = 0.95f;
	static inline constexpr float CARET_MIN_ALPHA = 0.05f;

	static inline constexpr int MAX_LINE_COUNT = 99;
	static inline constexpr int BLOOM_BLUR_COUNT = 3;
	static inline constexpr int BLOOM_QUALITY = 1;

	static inline const BloomType BLOOM_TYPE = BloomType::PARTS;

	vector<string> _loadedQuad3dIds = {};
	vector<string> _loadedText3dIds = {};
	vector<string> _loadedAabbIds = {};

	shared_ptr<Script> _script = nullptr;

	string _currentScriptFileId = "";
	string _firstSelectionAabbId = "";
	string _secondSelectionAabbId = "";
	string _selectionClipboard = "";

	bool _isWritingScript = false;
	bool _hasTextChanged = false;

	ScriptSelectionType _selectionType = {};
};