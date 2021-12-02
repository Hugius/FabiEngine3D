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
	_fe3d.camera_setThirdPersonLookat(fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));

	// Default graphics
	_fe3d.gfx_enableAmbientLighting();
	_fe3d.gfx_setAmbientLightingColor(fvec3(1.0f));
	_fe3d.gfx_setAmbientLightingIntensity(1.0f);
	_fe3d.gfx_enableDirectionalLighting();
	_fe3d.gfx_setDirectionalLightingColor(fvec3(1.0f));
	_fe3d.gfx_setDirectionalLightingPosition(fvec3(10000.0f));
	_fe3d.gfx_setDirectionalLightingIntensity(3.0f);
	_fe3d.gfx_enableMotionBlur();
	_fe3d.gfx_setMotionBlurStrength(0.1f);

	// Editor models
	_fe3d.model_create("@@cube", "engine\\assets\\meshes\\cube.obj");
	_fe3d.model_setBasePosition("@@cube", fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.model_setDiffuseMap("@@cube", "", "engine\\assets\\textures\\cube.png");
	_fe3d.model_setFaceCulled("@@cube", true);
	_fe3d.model_create("@@grid", "engine\\assets\\meshes\\plane.obj");
	_fe3d.model_setBasePosition("@@grid", fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.model_setBaseSize("@@grid", fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d.model_setDiffuseMap("@@grid", "", "engine\\assets\\textures\\grid.png");
	_fe3d.model_setTextureRepeat("@@grid", "", GRID_UV);
	_fe3d.model_setShadowed("@@grid", false);

	// Miscellaneous
	_gui.getGlobalScreen()->createTextField("waterID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true, false);
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
	_fe3d.water_deleteAll();

	// Delete models
	_fe3d.model_deleteAll();

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
	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		_fe3d.camera_disableThirdPersonView();
	}
	if(_fe3d.misc_isDebugRenderingEnabled())
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
	leftWindow->getScreen("waterEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: waterEditorMenuChoice
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("waterEditorMenuChoice");
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("size", fvec2(0.0f, positions[0]), fvec2(TW("Size"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("texturing", fvec2(0.0f, positions[1]), fvec2(TW("Texturing"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Texturing", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("lighting", fvec2(0.0f, positions[2]), fvec2(TW("Lighting"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("miscellaneous", fvec2(0.0f, positions[3]), fvec2(TW("Miscellaneous"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Miscellaneous", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[4]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: waterEditorMenuTexturing
	positions = VPC::calculateButtonPositions(6, CH);
	leftWindow->createScreen("waterEditorMenuTexturing");
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("dudvMap", fvec2(0.0f, positions[0]), fvec2(TW("DUDV Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "DUDV Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("normalMap", fvec2(0.0f, positions[1]), fvec2(TW("Normal Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("displaceMap", fvec2(0.0f, positions[2]), fvec2(TW("Displace Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Displace Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("clearMaps", fvec2(0.0f, positions[3]), fvec2(TW("Clear Maps"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Clear Maps", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("textureRepeat", fvec2(0.0f, positions[4]), fvec2(TW("Texture Repeat"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Texture Repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuTexturing")->createButton("back", fvec2(0.0f, positions[5]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: waterEditorMenuLighting
	positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("waterEditorMenuLighting");
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("color", fvec2(0.0f, positions[0]), fvec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("isReflective", fvec2(0.0f, positions[1]), fvec2(TW("Reflective: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflective: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("isRefractive", fvec2(0.0f, positions[2]), fvec2(TW("Refractive: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Refractive: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("isSpecular", fvec2(0.0f, positions[3]), fvec2(TW("Specular: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("specularShininess", fvec2(0.0f, positions[4]), fvec2(TW("Specular Shininess"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular Shininess", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("specularIntensity", fvec2(0.0f, positions[5]), fvec2(TW("Specular Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuLighting")->createButton("back", fvec2(0.0f, positions[6]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);

	// Left-viewport: waterEditorMenuMiscellaneous
	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("waterEditorMenuMiscellaneous");
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("waveHeight", fvec2(0.0f, positions[0]), fvec2(TW("Wave Height"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Wave Height", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("speed", fvec2(0.0f, positions[1]), fvec2(TW("Water Speed"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water Speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("transparency", fvec2(0.0f, positions[2]), fvec2(TW("Transparency"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Transparency", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("quality", fvec2(0.0f, positions[3]), fvec2(TW("Quality"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Quality", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
	leftWindow->getScreen("waterEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, positions[4]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true, true, true);
}

void WaterEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("waterEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("waterEditorMenuChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("waterEditorMenuTexturing");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("waterEditorMenuLighting");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("waterEditorMenuMiscellaneous");
}