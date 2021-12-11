#include "script_editor.hpp"
#include "left_viewport_controller.hpp"
#include "tools.hpp"

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

#define TW(text) VPC::calculateTextWidth(text, CW)

ScriptEditor::ScriptEditor(FabiEngine3D& fe3d, EngineGuiManager& gui, SkyEditor& skyEditor, TerrainEditor& terrainEditor, WaterEditor& waterEditor, ModelEditor& modelEditor, BillboardEditor& billboardEditor, MeshAnimationEditor& meshAnimationEditor, AudioEditor& audioEditor, WorldEditor& worldEditor)
	:
	_fe3d(fe3d),
	_gui(gui),
	_script(fe3d),
	_scriptExecutor(fe3d, _script, skyEditor, terrainEditor, waterEditor, modelEditor, billboardEditor, meshAnimationEditor, audioEditor, worldEditor)
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
	_fe3d.camera_setYaw(270.0f);
	_fe3d.camera_setPitch(0.0f);

	// Background
	_fe3d.sky_selectMainSky("");
	Tools::setRenderColor(BACKGROUND_COLOR);

	// Default graphics
	_fe3d.gfx_enableBloom();
	_fe3d.gfx_setBloomType(BloomType::PARTS);
	_fe3d.gfx_setBloomIntensity(0.95f);
	_fe3d.gfx_setBloomBlurCount(2);
	_fe3d.gfx_setBloomQuality(BLOOM_QUALITY);

	// Save anti aliasing state
	_wasAntiAliasingEnabled = _fe3d.gfx_isAntiAliasingEnabled();
	if(_wasAntiAliasingEnabled)
	{
		_fe3d.gfx_disableAntiAliasing(true);
	}

	// Miscellaneous
	_isEditorLoaded = true;
}

void ScriptEditor::unload()
{
	// GUI
	_unloadGUI();

	// Background
	_fe3d.sky_selectMainSky("@@background");
	Tools::setRenderColor(fvec3(0.0f));

	// Default graphics
	_fe3d.gfx_disableBloom(true);

	// Reset anti aliasing
	if(_wasAntiAliasingEnabled)
	{
		_fe3d.gfx_enableAntiAliasing();
	}

	// Delete created entities
	_fe3d.model_deleteAll();
	_fe3d.billboard_deleteAll();
	_fe3d.aabb_deleteAll();
	_fe3d.pointlight_deleteAll();

	// Unload script
	_script.reset();

	// Reset editor properties
	_scriptFileNamesToDelete.clear();
	_copyClipboard.clear();
	_currentScriptFileID = "";
	_scrollingAcceleration = 0.0f;
	_firstSelectedLineIndex = -1;
	_lastSelectedLineIndex = -1;
	_passedFrames = 0;
	_isEditorLoaded = false;
	_wasAntiAliasingEnabled = false;
	_isScriptLoadedFromFile = false;
	_isWritingScript = false;
	_isSingleActionAllowed = true;
	_isContinuousActionAllowed = false;
	_wasGuiFocused = false;
	_hasClickedLMB = false;
	_activeActionKey = InputType::NONE;
}

void ScriptEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: scriptEditorMenuMain
	auto positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("scriptEditorMenuMain");
	leftWindow->getScreen("scriptEditorMenuMain")->createTextField("lineCount", fvec2(0.0f, positions[0]), fvec2(TW("Lines: 0"), CH), "Lines: 0", fvec3(1.0f), true, false);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("search", fvec2(0.0f, positions[1]), fvec2(TW("Search"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Search", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("create", fvec2(0.0f, positions[2]), fvec2(TW("Create Script"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Script", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[3]), fvec2(TW("Edit Script"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Script", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("rename", fvec2(0.0f, positions[4]), fvec2(TW("Rename Script"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rename Script", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[5]), fvec2(TW("Delete Script"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Script", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("scriptEditorMenuMain")->createButton("back", fvec2(0.0f, positions[6]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
}

void ScriptEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("scriptEditorMenuMain");
}