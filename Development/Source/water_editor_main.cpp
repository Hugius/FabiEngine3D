#include "water_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

#define TW(text) VPC::calculateTextWidth(text, CW)

WaterEditor::WaterEditor(FabiEngine3D& fe3d, EngineGuiManager& gui)
	:
	_fe3d(fe3d),
	_gui(gui)
{

}

void WaterEditor::load()
{
	// GUI
	_loadGUI();

	// Camera
	_fe3d.camera_reset();
	
	// Default graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 1.0f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 3.0f);
	_fe3d.gfx_enableSpecularLighting();
	_fe3d.gfx_enableMotionBlur(0.1f);

	// Miscellaneous
	_gui.getGlobalScreen()->createTextfield("selectedWaterName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("environmentEditorControls");
	_isEditorLoaded = true;
}

void WaterEditor::update()
{
}

void WaterEditor::unload()
{
	// GUI
	_unloadGUI();

	// Default graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableSpecularLighting(true);
	_fe3d.gfx_disableMotionBlur(true);

	// Delete entities
	unloadWaterEntities();

	// Reset editor properties
	_loadedWaterIDs.clear();
	_currentWaterID = "";
	_isCreatingWater = false;
	_isChoosingWater = false;
	_isEditingWater = false;
	_isDeletingWater = false;

	// Miscellaneous
	_gui.getGlobalScreen()->deleteTextfield("selectedWaterName");
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	if (_fe3d.camera_isThirdPersonViewEnabled())
	{
		_fe3d.camera_disableThirdPersonView();
	}
	if (_fe3d.misc_isDebugRenderingEnabled())
	{
		_fe3d.misc_disableDebugRendering();
	}
	_isEditorLoaded = false;
}

void WaterEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: waterEditorMenuMain
	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("waterEditorMenuMain");
	leftWindow->getScreen("waterEditorMenuMain")->createButton("add", Vec2(0.0f, positions[0]), Vec2(TW("Add Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMain")->createButton("edit", Vec2(0.0f, positions[1]), Vec2(TW("Edit Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMain")->createButton("delete", Vec2(0.0f, positions[2]), Vec2(TW("Delete Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMain")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: waterEditorMenuChoice
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("waterEditorMenuChoice");
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("terrain", Vec2(0.0f, positions[0]), Vec2(TW("Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("mesh", Vec2(0.0f, positions[1]), Vec2(TW("3D mesh"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "3D mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("effects", Vec2(0.0f, positions[2]), Vec2(TW("Effects"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Effects", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("options", Vec2(0.0f, positions[3]), Vec2(TW("Options"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Options", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: waterEditorMenuMesh
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("waterEditorMenuMesh");
	leftWindow->getScreen("waterEditorMenuMesh")->createButton("position", Vec2(0.0f, positions[0]), Vec2(TW("Position"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Position", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMesh")->createButton("size", Vec2(0.0f, positions[1]), Vec2(TW("Size"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMesh")->createButton("up", Vec2(0.0f, positions[2]), Vec2(TW("Move Up"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Move Up", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMesh")->createButton("down", Vec2(0.0f, positions[3]), Vec2(TW("Move Down"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Move Down", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMesh")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: waterEditorMenuEffects
	positions = VPC::calculateButtonPositions(10, CH);
	leftWindow->createScreen("waterEditorMenuEffects");
	leftWindow->getScreen("waterEditorMenuEffects")->createButton("uvRepeat", Vec2(0.0f, positions[0]), Vec2(TW("UV Repeat"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "UV Repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->createButton("dudvMap", Vec2(0.0f, positions[1]), Vec2(TW("Dudv Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Dudv Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->createButton("normalMap", Vec2(0.0f, positions[2]), Vec2(TW("Normal Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->createButton("displaceMap", Vec2(0.0f, positions[3]), Vec2(TW("Displace Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Displace Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->createButton("isReflective", Vec2(0.0f, positions[4]), Vec2(TW("Reflective: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflective: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->createButton("isRefractive", Vec2(0.0f, positions[5]), Vec2(TW("Refractive: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Refractive: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->createButton("isWaving", Vec2(0.0f, positions[6]), Vec2(TW("Waving: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Waving: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->createButton("isRippling", Vec2(0.0f, positions[7]), Vec2(TW("Rippling: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rippling: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->createButton("isSpecular", Vec2(0.0f, positions[8]), Vec2(TW("Specular: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->createButton("back", Vec2(0.0f, positions[9]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: waterEditorMenuOptions
	positions = VPC::calculateButtonPositions(8, CH);
	leftWindow->createScreen("waterEditorMenuOptions");
	leftWindow->getScreen("waterEditorMenuOptions")->createButton("speed", Vec2(0.0f, positions[0]), Vec2(TW("Water Speed"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuOptions")->createButton("transparency", Vec2(0.0f, positions[1]), Vec2(TW("Transparency"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Transparency", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuOptions")->createButton("color", Vec2(0.0f, positions[2]), Vec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuOptions")->createButton("specularFactor", Vec2(0.0f, positions[3]), Vec2(TW("Spec Factor"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec Factor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuOptions")->createButton("specularIntensity", Vec2(positions[4], -0.13f), Vec2(TW("Spec Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuOptions")->createButton("waveHeight", Vec2(0.0f, positions[5]), Vec2(TW("Wave Height"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Wave Height", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuOptions")->createButton("quality", Vec2(0.0f, positions[6]), Vec2(TW("Quality"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Quality", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuOptions")->createButton("back", Vec2(0.0f, positions[7]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void WaterEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("waterEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("waterEditorMenuChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("waterEditorMenuMesh");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("waterEditorMenuEffects");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("waterEditorMenuOptions");
}