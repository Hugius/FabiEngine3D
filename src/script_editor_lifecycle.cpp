#define TW(text) (static_cast<float>(string(text).size()) * CW)

#include "script_editor.hpp"
#include "left_viewport_controller.hpp"
#include "tools.hpp"

void ScriptEditor::load()
{
	_loadGUI();

	_fe3d->camera_reset();
	_fe3d->camera_setPosition(CAMERA_POSITION);
	_fe3d->camera_setFOV(CAMERA_FOV);
	_fe3d->camera_setYaw(270.0f);
	_fe3d->camera_setPitch(0.0f);

	_fe3d->gfx_enableBloom();
	_fe3d->gfx_setBloomType(BloomType::PARTS);
	_fe3d->gfx_setBloomIntensity(0.95f);
	_fe3d->gfx_setBloomBlurCount(2);
	_fe3d->gfx_setBloomQuality(BLOOM_QUALITY);

	_isEditorLoaded = true;
}

void ScriptEditor::unload()
{
	_unloadGUI();

	_fe3d->gfx_disableBloom(true);

	_fe3d->text3d_deleteAll();

	_fe3d->aabb_deleteAll();

	_script->clear();

	_scriptFileNamesToDelete.clear();
	_copyClipboard.clear();
	_currentScriptFileId = "";
	_scrollingAcceleration = 0.0f;
	_firstSelectedLineIndex = -1;
	_lastSelectedLineIndex = -1;
	_passedFrames = 0;
	_isEditorLoaded = false;
	_isScriptLoadedFromFile = false;
	_isWritingScript = false;
	_isSingleActionAllowed = true;
	_isContinuousActionAllowed = false;
	_wasGuiFocused = false;
	_hasClickedLMB = false;
	_isCreatingScriptFile = false;
	_isChoosingScriptFile = false;
	_isRenamingScriptFile = false;
	_isSearchingScriptFile = false;
	_activeActionKey = InputType::NONE;
}

void ScriptEditor::_loadGUI()
{
	auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = Math::calculateDistributedPositions(7, CH);
	leftWindow->createScreen("scriptEditorMenuMain");
	leftWindow->getScreen("scriptEditorMenuMain")->createTextField("lineCount", fvec2(0.0f, positions[0]), fvec2(TW("Lines: 0"), CH), "Lines: 0", fvec3(1.0f), true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("search", fvec2(0.0f, positions[1]), fvec2(TW("Search"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Search", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("create", fvec2(0.0f, positions[2]), fvec2(TW("Create Script"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[3]), fvec2(TW("Edit Script"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("rename", fvec2(0.0f, positions[4]), fvec2(TW("Rename Script"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Rename Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[5]), fvec2(TW("Delete Script"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("back", fvec2(0.0f, positions[6]), fvec2(TW("Go Back"), CH), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
}

void ScriptEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("scriptEditorMenuMain");
}

void ScriptEditor::update()
{

	if(_isEditorLoaded)
	{
		_updateGUI();
	}
	if(_isEditorLoaded)
	{
		_updateScriptFileCreating();
	}
	if(_isEditorLoaded)
	{
		_updateScriptFileChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateScriptFileRenaming();
	}
	if(_isEditorLoaded)
	{
		_updateScriptSearching();
	}
	if(_isEditorLoaded)
	{
		_updateTextWriter();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}