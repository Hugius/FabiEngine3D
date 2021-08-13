#include "sky_editor.hpp"
#include "left_viewport_controller.hpp"

#define TW(text) VPC::calculateTextWidth(text, CW)

SkyEditor::SkyEditor(FabiEngine3D& fe3d, EngineGuiManager& gui)
	:
	_fe3d(fe3d),
	_gui(gui)
{

}

void SkyEditor::load()
{
	// GUI
	_loadGUI();

	// Camera
	_fe3d.camera_reset();
	_fe3d.camera_setMouseSensitivity(MOUSE_SENSITIVITY);
	
	// Default graphics
	_fe3d.gfx_enableMotionBlur(0.1f);

	// Miscellaneous
	_gui.getGlobalScreen()->createTextField("skyID", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("skyEditorControls");
	_isEditorLoaded = true;
}

void SkyEditor::unload()
{
	// GUI
	_unloadGUI();

	// Default graphics
	_fe3d.gfx_disableMotionBlur(true);

	// Delete entities
	unloadSkyEntities();

	// Reset editor properties
	_loadedSkyIDs.clear();
	_currentSkyID = "";
	_isEditorLoaded = false;
	_isCreatingSky = false;
	_isChoosingSky = false;
	_isEditingSky = false;
	_isDeletingSky = false;

	// Miscellaneous
	_gui.getGlobalScreen()->deleteTextField("skyID");
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	if (_fe3d.camera_isThirdPersonViewEnabled())
	{
		_fe3d.camera_disableThirdPersonView();
	}
	if (_fe3d.misc_isDebugRenderingEnabled())
	{
		_fe3d.misc_disableDebugRendering();
	}
}

void SkyEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: skyEditorMenuMain
	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("skyEditorMenuMain");
	leftWindow->getScreen("skyEditorMenuMain")->createButton("create", Vec2(0.0f, positions[0]), Vec2(TW("Create Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("edit", Vec2(0.0f, positions[1]), Vec2(TW("Edit Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("delete", Vec2(0.0f, positions[2]), Vec2(TW("Delete Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMain")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: skyEditorMenuChoice
	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("skyEditorMenuChoice");
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("mesh", Vec2(0.0f, positions[0]), Vec2(TW("3D Mesh"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "3D Mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("options", Vec2(0.0f, positions[1]), Vec2(TW("Options"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Options", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuChoice")->createButton("back", Vec2(0.0f, positions[2]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: skyEditorMenuMesh
	positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("skyEditorMenuMesh");
	leftWindow->getScreen("skyEditorMenuMesh")->createButton("leftTexture", Vec2(0.0f, positions[0]), Vec2(TW("Left Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Left Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMesh")->createButton("rightTexture", Vec2(0.0f, positions[1]), Vec2(TW("Right Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Right Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMesh")->createButton("frontTexture", Vec2(0.0f, positions[2]), Vec2(TW("Front Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Front Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMesh")->createButton("backTexture", Vec2(0.0f, positions[3]), Vec2(TW("Back Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Back Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMesh")->createButton("topTexture", Vec2(0.0f, positions[4]), Vec2(TW("Top Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Top Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMesh")->createButton("bottomTexture", Vec2(0.0f, positions[5]), Vec2(TW("Bottom Texture"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Bottom Texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMesh")->createButton("back", Vec2(0.0f, positions[6]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: skyEditorMenuOptions
	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("skyEditorMenuOptions");
	leftWindow->getScreen("skyEditorMenuOptions")->createButton("rotationSpeed", Vec2(0.0f, positions[0]), Vec2(TW("Rotation Speed"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rotation Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuOptions")->createButton("lightness", Vec2(0.0f, positions[1]), Vec2(TW("Lightness"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuOptions")->createButton("color", Vec2(0.0f, positions[2]), Vec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuOptions")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void SkyEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("skyEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("skyEditorMenuChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("skyEditorMenuMesh");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("skyEditorMenuOptions");
}