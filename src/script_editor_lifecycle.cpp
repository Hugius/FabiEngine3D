#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "script_editor.hpp"
#include "left_viewport_controller.hpp"
#include "tools.hpp"
#include "configuration.hpp"

void ScriptEditor::_load()
{
	_fe3d->quad3d_create("selection", true);
	_fe3d->quad3d_setVisible("selection", false);
	_fe3d->quad3d_setColor("selection", SELECTION_COLOR);

	_fe3d->text3d_create("cursor", FONT_MAP_PATH, true);
	_fe3d->text3d_setVisible("cursor", false);
	_fe3d->text3d_setContent("cursor", "|");
	_fe3d->text3d_setSize("cursor", CHAR_SIZE);
	_fe3d->text3d_setMinTextureAlpha("cursor", 0.05f);

	_fe3d->graphics_setBloomEnabled(true);
	_fe3d->graphics_setBloomType(BloomType::PARTS);
	_fe3d->graphics_setBloomIntensity(0.95f);
	_fe3d->graphics_setBloomBlurCount(2);
	_fe3d->graphics_setBloomQuality(BLOOM_QUALITY);

	_fe3d->camera_setFov(CAMERA_FOV);
	_fe3d->camera_setYaw(CAMERA_YAW);
	_fe3d->camera_setPitch(CAMERA_PITCH);
	_fe3d->camera_setPosition(fvec3(0.0f, 0.0f, CAMERA_DISTANCE));

	_fe3d->raycast_setAabbIntersectionEnabled(true);
}

void ScriptEditor::_unload()
{
	for(const auto & id : _loadedQuadIds)
	{
		_fe3d->quad3d_delete(id);
	}

	for(const auto & id : _loadedTextIds)
	{
		_fe3d->text3d_delete(id);
	}

	for(const auto & id : _loadedAabbIds)
	{
		_fe3d->aabb_delete(id);
	}

	_fe3d->quad3d_delete("selection");

	_fe3d->text3d_delete("cursor");

	_fe3d->graphics_setBloomEnabled(false);
	_fe3d->graphics_setBloomType(BloomType::EVERYTHING);
	_fe3d->graphics_setBloomIntensity(0.0f);
	_fe3d->graphics_setBloomBlurCount(0);
	_fe3d->graphics_setBloomQuality(0);

	_fe3d->camera_reset();

	_fe3d->raycast_setAabbIntersectionEnabled(false);

	_script->clear();

	_loadedQuadIds.clear();
	_loadedTextIds.clear();
	_loadedAabbIds.clear();
	_currentScriptFileId = "";
	_firstSelectionAabbId = "";
	_secondSelectionAabbId = "";
	_isWritingScript = false;
	_hasTextChanged = false;
	_selectionType = {};
}

void ScriptEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = Mathematics::calculateDistributedPositions(8, CH, false);
	leftWindow->createScreen("scriptEditorMenuMain");
	leftWindow->getScreen("scriptEditorMenuMain")->createTextField("lineCount", fvec2(0.0f, positions[0]), TEXT_SIZE("Lines: 0"), "Lines: 0", fvec3(1.0f), true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("search", fvec2(0.0f, positions[1]), TEXT_SIZE("Search"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Search", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("create", fvec2(0.0f, positions[2]), TEXT_SIZE("Create Script"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[3]), TEXT_SIZE("Edit Script"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("rename", fvec2(0.0f, positions[4]), TEXT_SIZE("Rename Script"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Rename Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("clear", fvec2(0.0f, positions[5]), TEXT_SIZE("Clear Script"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[6]), TEXT_SIZE("Delete Script"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("back", fvec2(0.0f, positions[7]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
}

void ScriptEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("scriptEditorMenuMain");
}

void ScriptEditor::update()
{
	if(isLoaded())
	{
		_updateMenu();
	}
	if(isLoaded())
	{
		_updateScriptSearching();
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
		_updateScriptDeleting();
	}
	if(isLoaded())
	{
		_updateTextWriter();
	}
	if(isLoaded())
	{
		_updateTextSelector();
	}
	if(isLoaded())
	{
		_updateDisplay();
	}
	if(isLoaded())
	{
		_updateCamera();
	}
	if(isLoaded())
	{
		_updateCursor();
	}
}