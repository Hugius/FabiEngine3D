#include "script_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

#define TW(text) VPC::calculateTextWidth(text, CW)

ScriptEditor::ScriptEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, SkyEditor& skyEditor, TerrainEditor& terrainEditor, WaterEditor& waterEditor, ModelEditor& modelEditor, AnimationEditor& animationEditor, BillboardEditor& billboardEditor, AudioEditor& audioEditor, SceneEditor& sceneEditor)
	:
	_fe3d(fe3d),
	_gui(gui),
	_script(fe3d),
	_scriptExecutor(fe3d, _script, skyEditor, terrainEditor, waterEditor, modelEditor, animationEditor, billboardEditor, audioEditor, sceneEditor)
{

}

void ScriptEditor::load()
{
	// GUI
	_loadGUI();

	// Camera
	_fe3d.camera_reset();
	_fe3d.camera_setPosition(CAMERA_POSITION);
	_fe3d.camera_setFOV(CAMERA_FOV);
	_fe3d.camera_setYaw(-90.0f);
	_fe3d.camera_setPitch(0.0f);

	// Background
	_fe3d.skyEntity_selectMainSky("");
	_fe3d.misc_setMainRenderingColor(BACKGROUND_COLOR);

	// Default graphics
	_fe3d.gfx_enableBloom(BloomType::PARTS, 1.0f, 2);

	// Save bloom size
	_originalBloomSize = _fe3d.gfx_getBloomSize();
	_fe3d.gfx_setBloomSize(BLOOM_SIZE);

	// Save anti aliasing state
	_wasAntiAliasingEnabled = _fe3d.gfx_isAntiAliasingEnabled();
	if (_wasAntiAliasingEnabled)
	{
		_fe3d.gfx_disableAntiAliasing(true);
	}

	// Miscellaneous
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("scriptEditorControls");
	_isEditorLoaded = true;
}

void ScriptEditor::unload()
{
	// GUI
	_unloadGUI();

	// Background
	_fe3d.skyEntity_selectMainSky("@@engineBackground");
	_fe3d.misc_setMainRenderingColor(Vec3(0.0f));

	// Default graphics
	_fe3d.gfx_disableBloom(true);

	// Reset bloom size
	_fe3d.gfx_setBloomSize(_originalBloomSize);

	// Reset anti aliasing
	if (_wasAntiAliasingEnabled)
	{
		_fe3d.gfx_enableAntiAliasing();
	}

	// Delete created entities
	_fe3d.modelEntity_deleteAll();
	_fe3d.billboardEntity_deleteAll();
	_fe3d.aabbEntity_deleteAll();
	_fe3d.lightEntity_deleteAll();

	// Unload script
	_script.reset();

	// Reset editor properties
	_scriptFilenamesToDelete.clear();
	_copyClipboard.clear();
	_currentScriptFileID = "";
	_scrollingAcceleration = 0.0f;
	_firstSelectedLineIndex = -1;
	_lastSelectedLineIndex = -1;
	_passedFrames = 0;
	_originalBloomSize = 0;
	_isEditorLoaded = false;
	_wasAntiAliasingEnabled = false;
	_isScriptLoadedFromFile = false;
	_isWritingScript = false;
	_isSingleActionAllowed = true;
	_isContinuousActionAllowed = false;
	_wasGuiFocused = false;
	_hasClickedLMB = false;
	_activeActionKey = InputType::NONE;

	// Miscellaneous
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
}

void ScriptEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: scriptEditorMenuMain
	auto positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("scriptEditorMenuMain");
	leftWindow->getScreen("scriptEditorMenuMain")->createTextField("lineCount", Vec2(0.0f, positions[0]), Vec2(TW("Lines: 0"), CH), "Lines: 0", Vec3(1.0f));
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("search", Vec2(0.0f, positions[1]), Vec2(TW("Search"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Search", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("create", Vec2(0.0f, positions[2]), Vec2(TW("Create Script"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Script", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("edit", Vec2(0.0f, positions[3]), Vec2(TW("Edit Script"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Script", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("rename", Vec2(0.0f, positions[4]), Vec2(TW("Rename Script"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rename Script", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("delete", Vec2(0.0f, positions[5]), Vec2(TW("Delete Script"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Script", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("back", Vec2(0.0f, positions[6]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void ScriptEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("scriptEditorMenuMain");
}