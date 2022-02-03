#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "script_editor.hpp"
#include "left_viewport_controller.hpp"
#include "tools.hpp"
#include "configuration.hpp"

void ScriptEditor::_load()
{
	_fe3d->camera_reset();
	_fe3d->camera_setPosition(CAMERA_POSITION);
	_fe3d->camera_setFov(CAMERA_FOV);
	_fe3d->camera_setYaw(270.0f);
	_fe3d->camera_setPitch(0.0f);

	_fe3d->gfx_setBloomEnabled(true);
	_fe3d->gfx_setBloomType(BloomType::PARTS);
	_fe3d->gfx_setBloomIntensity(0.95f);
	_fe3d->gfx_setBloomBlurCount(2);
	_fe3d->gfx_setBloomQuality(BLOOM_QUALITY);
}

void ScriptEditor::_unload()
{
	_fe3d->gfx_setBloomEnabled(false);
	_fe3d->gfx_setBloomType(BloomType::EVERYTHING);
	_fe3d->gfx_setBloomIntensity(0.0f);
	_fe3d->gfx_setBloomBlurCount(0);
	_fe3d->gfx_setBloomQuality(0);

	_fe3d->quad3d_deleteAll();
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
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = Math::calculateDistributedPositions(7, CH);
	leftWindow->createScreen("scriptEditorMenuMain");
	leftWindow->getScreen("scriptEditorMenuMain")->createTextField("lineCount", fvec2(0.0f, positions[0]), TEXT_SIZE("Lines: 0"), "Lines: 0", fvec3(1.0f), true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("search", fvec2(0.0f, positions[1]), TEXT_SIZE("Search"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Search", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("create", fvec2(0.0f, positions[2]), TEXT_SIZE("Create Script"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[3]), TEXT_SIZE("Edit Script"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("rename", fvec2(0.0f, positions[4]), TEXT_SIZE("Rename Script"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Rename Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[5]), TEXT_SIZE("Delete Script"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("back", fvec2(0.0f, positions[6]), TEXT_SIZE("Go Back"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
}

void ScriptEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("scriptEditorMenuMain");
}

void ScriptEditor::update()
{

	if(isLoaded())
	{
		_updateGUI();
	}
	if(isLoaded())
	{
		_updateScriptFileCreating();
	}
	if(isLoaded())
	{
		_updateScriptFileChoosing();
	}
	if(isLoaded())
	{
		_updateScriptFileRenaming();
	}
	if(isLoaded())
	{
		_updateScriptSearching();
	}
	if(isLoaded())
	{
		_updateTextWriter();
	}
	if(isLoaded())
	{
		_updateMiscellaneous();
	}
}