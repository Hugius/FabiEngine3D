#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)
#define POSITIONS(count) Mathematics::calculateDistributedPositions(count, CH, false)

#include "script_editor.hpp"
#include "tools.hpp"
#include "configuration.hpp"

void ScriptEditor::_load()
{
	_fe3d->quad3d_create(SELECTION_ID, true);
	_fe3d->quad3d_setVisible(SELECTION_ID, false);
	_fe3d->quad3d_setColor(SELECTION_ID, SELECTION_COLOR);

	_fe3d->text3d_create(CARET_ID, FONT_MAP_PATH, true);
	_fe3d->text3d_setVisible(CARET_ID, false);
	_fe3d->text3d_setContent(CARET_ID, "|");
	_fe3d->text3d_setSize(CARET_ID, CARET_SIZE);
	_fe3d->text3d_setMinTextureAlpha(CARET_ID, CARET_MIN_TEXTURE_ALPHA);

	_fe3d->graphics_setBloomEnabled(true);
	_fe3d->graphics_setBloomType(BLOOM_TYPE);
	_fe3d->graphics_setBloomIntensity(BLOOM_INTENSITY);
	_fe3d->graphics_setBloomBlurCount(BLOOM_BLUR_COUNT);
	_fe3d->graphics_setBloomQuality(BLOOM_QUALITY);

	_fe3d->camera_setFov(CAMERA_FOV);
	_fe3d->camera_setYaw(CAMERA_YAW);
	_fe3d->camera_setPitch(CAMERA_PITCH);
	_fe3d->camera_setPosition(fvec3(0.0f, 0.0f, CAMERA_DISTANCE));

	_fe3d->raycast_setAabbIntersectionEnabled(true);
}

void ScriptEditor::_unload()
{
	for(const auto & quad3dId : _loadedQuad3dIds)
	{
		_fe3d->quad3d_delete(quad3dId);
	}

	for(const auto & text3dId : _loadedText3dIds)
	{
		_fe3d->text3d_delete(text3dId);
	}

	for(const auto & aabbId : _loadedAabbIds)
	{
		_fe3d->aabb_delete(aabbId);
	}

	_fe3d->quad3d_delete(SELECTION_ID);

	_fe3d->text3d_delete(CARET_ID);

	_fe3d->graphics_setBloomEnabled(false);
	_fe3d->graphics_setBloomType(BloomType::EVERYTHING);
	_fe3d->graphics_setBloomIntensity(0.0f);
	_fe3d->graphics_setBloomBlurCount(0);
	_fe3d->graphics_setBloomQuality(0);

	_fe3d->camera_reset();

	_fe3d->raycast_setAabbIntersectionEnabled(false);

	_script->clear();

	_loadedQuad3dIds.clear();
	_loadedText3dIds.clear();
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
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	rightWindow->createScreen("scriptEditorMenuMain");
	rightWindow->getScreen("scriptEditorMenuMain")->createTextField("lineCount", fvec2(0.0f, POSITIONS(8)[0]), TEXT_SIZE("Lines: 0"), "Lines: 0", fvec3(1.0f), true);
	rightWindow->getScreen("scriptEditorMenuMain")->createButton("search", fvec2(0.0f, POSITIONS(8)[1]), TEXT_SIZE("Search"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Search", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("scriptEditorMenuMain")->createButton("create", fvec2(0.0f, POSITIONS(8)[2]), TEXT_SIZE("Create Script"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("scriptEditorMenuMain")->createButton("edit", fvec2(0.0f, POSITIONS(8)[3]), TEXT_SIZE("Edit Script"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("scriptEditorMenuMain")->createButton("rename", fvec2(0.0f, POSITIONS(8)[4]), TEXT_SIZE("Rename Script"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Rename Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("scriptEditorMenuMain")->createButton("clear", fvec2(0.0f, POSITIONS(8)[5]), TEXT_SIZE("Clear Script"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Clear Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("scriptEditorMenuMain")->createButton("delete", fvec2(0.0f, POSITIONS(8)[6]), TEXT_SIZE("Delete Script"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Script", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("scriptEditorMenuMain")->createButton("back", fvec2(0.0f, POSITIONS(8)[7]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("empty");

	rightWindow->setActiveScreen("scriptEditorMenuMain");
}

void ScriptEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	rightWindow->deleteScreen("scriptEditorMenuMain");

	leftWindow->setActiveScreen("main");
	rightWindow->setActiveScreen("main");
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