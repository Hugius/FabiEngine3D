#include "quad_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

#define TW(text) VPC::calculateTextWidth(text, CW)

QuadEditor::QuadEditor(FabiEngine3D& fe3d, GuiManager& gui)
	:
	_fe3d(fe3d),
	_gui(gui)
{

}

void QuadEditor::load()
{
	_loadGUI();

	_fe3d.camera_reset();
	_fe3d.camera_setYaw(270.0f);

	_fe3d.billboard_create(PREVIEW_BILLBOARD_ID, true);
	_fe3d.billboard_setPosition(PREVIEW_BILLBOARD_ID, PREVIEW_BILLBOARD_POSITION);
	_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, false);

	_gui.getOverlay()->createTextField("quadID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(0.0f), true);

	_isEditorLoaded = true;
}

void QuadEditor::unload()
{
	for(const auto& ID : _loadedQuadIDs)
	{
		_fe3d.quad_delete(ID);
	}

	_unloadGUI();

	_fe3d.billboard_delete(PREVIEW_BILLBOARD_ID);

	_gui.getOverlay()->deleteTextField("quadID");

	_loadedQuadIDs.clear();
	_currentQuadID = "";
	_hoveredQuadID = "";
	_isEditorLoaded = false;
	_isCreatingQuad = false;
	_isChoosingQuad = false;
	_isDeletingQuad = false;
}

void QuadEditor::_loadGUI()
{
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("quadEditorMenuMain");
	leftWindow->getScreen("quadEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Quad"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Quad", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quadEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Quad"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Quad", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quadEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Quad"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Quad", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quadEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(2, CH);
	leftWindow->createScreen("quadEditorMenuChoice");
	leftWindow->getScreen("quadEditorMenuChoice")->createButton("diffuseMap", fvec2(0.0f, positions[0]), fvec2(TW("Diffuse Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Diffuse Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quadEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[1]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
}

void QuadEditor::_unloadGUI()
{
	_gui.getViewport("left")->getWindow("main")->deleteScreen("quadEditorMenuMain");
	_gui.getViewport("left")->getWindow("main")->deleteScreen("quadEditorMenuChoice");
}

void QuadEditor::update()
{
	if(_isEditorLoaded)
	{
		_updateMainMenu();
	}
	if(_isEditorLoaded)
	{
		_updateChoiceMenu();
	}
	if(_isEditorLoaded)
	{
		_updateQuadCreating();
	}
	if(_isEditorLoaded)
	{
		_updateQuadChoosing();
	}
	if(_isEditorLoaded)
	{
		_updateQuadDeleting();
	}
}