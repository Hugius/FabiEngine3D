#include "terrain_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

#define TW(text) VPC::calculateTextWidth(text, CW)

TerrainEditor::TerrainEditor(FabiEngine3D& fe3d, GuiManager& gui)
	:
	_fe3d(fe3d),
	_gui(gui)
{

}

void TerrainEditor::load()
{
	_loadGUI();

	_fe3d.camera_reset();
	_fe3d.camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d.camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d.camera_enableThirdPersonView(INITIAL_CAMERA_YAW, INITIAL_CAMERA_PITCH);
	_fe3d.camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);
	_fe3d.camera_setThirdPersonLookat(fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));

	_fe3d.gfx_enableAntiAliasing();
	_fe3d.gfx_setAnisotropicFilteringQuality(Config::MAX_ANISOTROPIC_FILTERING_QUALITY);
	_fe3d.gfx_enableAmbientLighting();
	_fe3d.gfx_setAmbientLightingColor(fvec3(1.0f));
	_fe3d.gfx_setAmbientLightingIntensity(1.0f);
	_fe3d.gfx_enableDirectionalLighting();
	_fe3d.gfx_setDirectionalLightingColor(fvec3(1.0f));
	_fe3d.gfx_setDirectionalLightingPosition(fvec3(10000.0f));
	_fe3d.gfx_setDirectionalLightingIntensity(3.0f);

	_fe3d.model_create("@@box", "engine\\assets\\mesh\\box.obj");
	_fe3d.model_setBasePosition("@@box", fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.model_setDiffuseMap("@@box", "", "engine\\assets\\image\\diffuse_map\\box.png");
	_fe3d.model_setFaceCulled("@@box", true);
	_fe3d.model_create("@@grid", "engine\\assets\\mesh\\plane.obj");
	_fe3d.model_setBasePosition("@@grid", fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d.model_setBaseSize("@@grid", fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d.model_setDiffuseMap("@@grid", "", "engine\\assets\\image\\diffuse_map\\grid.png");
	_fe3d.model_setTextureRepeat("@@grid", "", GRID_UV);
	_fe3d.model_setShadowed("@@grid", false);

	_gui.getOverlay()->createTextField("terrainID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(0.0f), true);

	_isEditorLoaded = true;
}

void TerrainEditor::unload()
{
	for (const auto& ID : _loadedTerrainIDs)
	{
		_fe3d.terrain_delete(ID);
	}

	_unloadGUI();

	_fe3d.gfx_disableAntiAliasing(true);
	_fe3d.gfx_setAnisotropicFilteringQuality(Config::MIN_ANISOTROPIC_FILTERING_QUALITY);
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);

	_fe3d.model_delete("@@box");
	_fe3d.model_delete("@@grid");

	_gui.getOverlay()->deleteTextField("terrainID");

	_loadedTerrainIDs.clear();
	_currentTerrainID = "";
	_isEditorLoaded = false;
	_isCreatingTerrain = false;
	_isChoosingTerrain = false;
	_isDeletingTerrain = false;

	if (_fe3d.camera_isThirdPersonViewEnabled())
	{
		_fe3d.camera_disableThirdPersonView();
	}
}

void TerrainEditor::_loadGUI()
{
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("terrainEditorMenuMain");
	leftWindow->getScreen("terrainEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(7, CH);
	leftWindow->createScreen("terrainEditorMenuChoice");
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("maxHeight", fvec2(0.0f, positions[0]), fvec2(TW("Max Height"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Max Height", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("diffuseMap", fvec2(0.0f, positions[1]), fvec2(TW("Diffuse Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Diffuse Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("normalMap", fvec2(0.0f, positions[2]), fvec2(TW("Normal Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("blendMap", fvec2(0.0f, positions[3]), fvec2(TW("Blend Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blend Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("lighting", fvec2(0.0f, positions[4]), fvec2(TW("Lighting"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("miscellaneous", fvec2(0.0f, positions[5]), fvec2(TW("Miscellaneous"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Miscellaneous", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[6]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(6, CH);
	leftWindow->createScreen("terrainEditorMenuDiffuseMap");
	leftWindow->getScreen("terrainEditorMenuDiffuseMap")->createButton("diffuseMap", fvec2(0.0f, positions[0]), fvec2(TW("Diffuse Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Diffuse Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuDiffuseMap")->createButton("redDiffuseMap", fvec2(0.0f, positions[1]), fvec2(TW("Red Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Red Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuDiffuseMap")->createButton("greenDiffuseMap", fvec2(0.0f, positions[2]), fvec2(TW("Green Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Green Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuDiffuseMap")->createButton("blueDiffuseMap", fvec2(0.0f, positions[3]), fvec2(TW("Blue Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blue Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuDiffuseMap")->createButton("clearMaps", fvec2(0.0f, positions[4]), fvec2(TW("Clear Maps"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Clear Maps", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuDiffuseMap")->createButton("back", fvec2(0.0f, positions[5]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(6, CH);
	leftWindow->createScreen("terrainEditorMenuNormalMap");
	leftWindow->getScreen("terrainEditorMenuNormalMap")->createButton("normalMap", fvec2(0.0f, positions[0]), fvec2(TW("Normal Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Normal Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuNormalMap")->createButton("redNormalMap", fvec2(0.0f, positions[1]), fvec2(TW("Red Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Red Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuNormalMap")->createButton("greenNormalMap", fvec2(0.0f, positions[2]), fvec2(TW("Green Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Green Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuNormalMap")->createButton("blueNormalMap", fvec2(0.0f, positions[3]), fvec2(TW("Blue Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blue Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuNormalMap")->createButton("clearMaps", fvec2(0.0f, positions[4]), fvec2(TW("Clear Maps"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Clear Maps", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuNormalMap")->createButton("back", fvec2(0.0f, positions[5]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(3, CH);
	leftWindow->createScreen("terrainEditorMenuBlendMap");
	leftWindow->getScreen("terrainEditorMenuBlendMap")->createButton("blendMap", fvec2(0.0f, positions[0]), fvec2(TW("Blend Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blend Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->createButton("clearMaps", fvec2(0.0f, positions[1]), fvec2(TW("Clear Maps"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Clear Maps", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->createButton("back", fvec2(0.0f, positions[2]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("terrainEditorMenuLighting");
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("lightness", fvec2(0.0f, positions[0]), fvec2(TW("Lightness"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("isSpecular", fvec2(0.0f, positions[1]), fvec2(TW("Specular: OFF"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("specularShininess", fvec2(0.0f, positions[2]), fvec2(TW("Specular Shininess"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular Shininess", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("specularIntensity", fvec2(0.0f, positions[3]), fvec2(TW("Specular Intensity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular Intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuLighting")->createButton("back", fvec2(0.0f, positions[4]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(5, CH);
	leftWindow->createScreen("terrainEditorMenuMiscellaneous");
	leftWindow->getScreen("terrainEditorMenuMiscellaneous")->createButton("textureRepeat", fvec2(0.0f, positions[0]), fvec2(TW("Texture Repeat"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Texture Repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMiscellaneous")->createButton("redTextureRepeat", fvec2(0.0f, positions[1]), fvec2(TW("Red Repeat"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Red Repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMiscellaneous")->createButton("greenTextureRepeat", fvec2(0.0f, positions[2]), fvec2(TW("Green Repeat"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Green Repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMiscellaneous")->createButton("blueTextureRepeat", fvec2(0.0f, positions[3]), fvec2(TW("Blue Repeat"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blue Repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("terrainEditorMenuMiscellaneous")->createButton("back", fvec2(0.0f, positions[4]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
}

void TerrainEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("terrainEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("terrainEditorMenuChoice");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("terrainEditorMenuDiffuseMap");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("terrainEditorMenuBlendMap");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("terrainEditorMenuNormalMap");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("terrainEditorMenuLighting");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("terrainEditorMenuMiscellaneous");
}

void TerrainEditor::update()
{
	if (_isEditorLoaded)
	{
		_updateMainMenu();
	}
	if (_isEditorLoaded)
	{
		_updateChoiceMenu();
	}
	if (_isEditorLoaded)
	{
		_updateDiffuseMapMenu();
	}
	if (_isEditorLoaded)
	{
		_updateNormalMapMenu();
	}
	if (_isEditorLoaded)
	{
		_updateBlendMapMenu();
	}
	if (_isEditorLoaded)
	{
		_updateLightingMenu();
	}
	if (_isEditorLoaded)
	{
		_updateMiscellaneousMenu();
	}
	if (_isEditorLoaded)
	{
		_updateTerrainCreating();
	}
	if (_isEditorLoaded)
	{
		_updateTerrainChoosing();
	}
	if (_isEditorLoaded)
	{
		_updateTerrainDeleting();
	}
	if (_isEditorLoaded)
	{
		_updateCamera();
	}
	if (_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}