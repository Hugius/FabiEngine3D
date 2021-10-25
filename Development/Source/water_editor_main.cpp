#include "water_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

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
	_fe3d.camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d.camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d.camera_enableThirdPersonView(INITIAL_CAMERA_YAW, INITIAL_CAMERA_PITCH);
	_fe3d.camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);
	_fe3d.camera_setThirdPersonLookat(Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	
	// Default graphics
	_fe3d.gfx_enableAmbientLighting();
	_fe3d.gfx_setAmbientLightingColor(Vec3(1.0f));
	_fe3d.gfx_setAmbientLightingIntensity(1.0f);
	_fe3d.gfx_enableDirectionalLighting();
	_fe3d.gfx_setDirectionalLightingColor(Vec3(1.0f));
	_fe3d.gfx_setDirectionalLightingPosition(Vec3(10000.0f));
	_fe3d.gfx_setDirectionalLightingIntensity(3.0f);
	_fe3d.gfx_enableMotionBlur();
	_fe3d.gfx_setMotionBlurStrength(0.1f);

	// Editor models
	_fe3d.modelEntity_create("@@cube", "engine_assets\\meshes\\cube.obj");
	_fe3d.modelEntity_setBasePosition("@@cube", Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.modelEntity_setDiffuseMap("@@cube", "", "engine_assets\\textures\\cube.png");
	_fe3d.modelEntity_setFaceCulled("@@cube", true);
	_fe3d.modelEntity_create("@@grid", "engine_assets\\meshes\\plane.obj");
	_fe3d.modelEntity_setBasePosition("@@grid", Vec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.modelEntity_setBaseSize("@@grid", Vec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d.modelEntity_setDiffuseMap("@@grid", "", "engine_assets\\textures\\grid.png");
	_fe3d.modelEntity_setTextureRepeat("@@grid", "", GRID_UV);
	_fe3d.modelEntity_setShadowed("@@grid", false);

	// Miscellaneous
	_gui.getGlobalScreen()->createTextField("waterID", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("waterEditorControls");
	_isEditorLoaded = true;
}

void WaterEditor::unload()
{
	// GUI
	_unloadGUI();

	// Default graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableMotionBlur(true);

	// Delete waters
	unloadWaterEntities();

	// Editor models
	_fe3d.modelEntity_deleteAll();

	// Reset editor properties
	_loadedWaterIDs.clear();
	_currentWaterID = "";
	_isEditorLoaded = false;
	_isCreatingWater = false;
	_isChoosingWater = false;
	_isDeletingWater = false;

	// Miscellaneous
	_gui.getGlobalScreen()->deleteTextField("waterID");
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

void WaterEditor::_loadGUI()
{
	// Temporary values
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: waterEditorMenuMain
	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("waterEditorMenuMain");
	leftWindow->getScreen("waterEditorMenuMain")->createButton("create", Vec2(0.0f, positions[0]), Vec2(TW("Create Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMain")->createButton("edit", Vec2(0.0f, positions[1]), Vec2(TW("Edit Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMain")->createButton("delete", Vec2(0.0f, positions[2]), Vec2(TW("Delete Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMain")->createButton("back", Vec2(0.0f, positions[3]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: waterEditorMenuChoice
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("waterEditorMenuChoice");
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("size", Vec2(0.0f, positions[0]), Vec2(TW("Size"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("texturing", Vec2(0.0f, positions[1]), Vec2(TW("Texturing"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Texturing", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("lighting", Vec2(0.0f, positions[2]), Vec2(TW("Lighting"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("miscellaneous", Vec2(0.0f, positions[3]), Vec2(TW("Miscellaneous"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Miscellaneous", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: waterEditorMenuTexturing
	positions = VPC::calculateButtonPositions(6, CH);
	leftWindow->createScreen("waterEditorMenuTexturing");
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("dudvMap", Vec2(0.0f, positions[0]), Vec2(TW("DUDV Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "DUDV Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("normalMap", Vec2(0.0f, positions[1]), Vec2(TW("Normal Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("displaceMap", Vec2(0.0f, positions[2]), Vec2(TW("Displace Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Displace Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("clearMaps", Vec2(0.0f, positions[3]), Vec2(TW("Clear Maps"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Clear Maps", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("textureRepeat", Vec2(0.0f, positions[4]), Vec2(TW("Texture Repeat"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Texture Repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("back", Vec2(0.0f, positions[5]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	
	// Left-viewport: waterEditorMenuLighting
	positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("waterEditorMenuLighting");
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("color", Vec2(0.0f, positions[0]), Vec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("isReflective", Vec2(0.0f, positions[1]), Vec2(TW("Reflective: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflective: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("isRefractive", Vec2(0.0f, positions[2]), Vec2(TW("Refractive: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Refractive: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("isSpecular", Vec2(0.0f, positions[3]), Vec2(TW("Specular: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("specularShininess", Vec2(0.0f, positions[4]), Vec2(TW("Specular Shininess"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular Shininess", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("specularIntensity", Vec2(0.0f, positions[5]), Vec2(TW("Specular Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("back", Vec2(0.0f, positions[6]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: waterEditorMenuMiscellaneous
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("waterEditorMenuMiscellaneous");
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("waveHeight", Vec2(0.0f, positions[0]), Vec2(TW("Wave Height"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Wave Height", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("speed", Vec2(0.0f, positions[1]), Vec2(TW("Water Speed"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("transparency", Vec2(0.0f, positions[2]), Vec2(TW("Transparency"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Transparency", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("quality", Vec2(0.0f, positions[3]), Vec2(TW("Quality"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Quality", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("back", Vec2(0.0f, positions[4]), Vec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void WaterEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("waterEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("waterEditorMenuChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("waterEditorMenuTexturing");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("waterEditorMenuLighting");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("waterEditorMenuMiscellaneous");
}