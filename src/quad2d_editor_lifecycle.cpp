#define TW(text) VPC::calculateTextWidth(text, CW)

#include "quad2d_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

using VPC = BaseViewportController;
using LVPC = LeftViewportController;

void Quad2dEditor::load()
{
	_loadGUI();

	_fe3d->camera_reset();
	_fe3d->camera_setYaw(270.0f);

	_gui->getOverlay()->createTextField("quadId", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true);

	_isEditorLoaded = true;
}

void Quad2dEditor::unload()
{
	for(const auto& id : _loadedQuadIds)
	{
		_fe3d->quad2d_delete(id);
	}

	_unloadGUI();

	_gui->getOverlay()->deleteTextField("quadId");

	_loadedQuadIds.clear();
	_currentQuadId = "";
	_hoveredQuadId = "";
	_isEditorLoaded = false;
	_isCreatingQuad = false;
	_isChoosingQuad = false;
	_isDeletingQuad = false;
}

void Quad2dEditor::_loadGUI()
{
	auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("quad2dEditorMenuMain");
	leftWindow->getScreen("quad2dEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), fvec2(TW("Create Quad2D"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create Quad2D", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), fvec2(TW("Edit Quad2D"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit Quad2D", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), fvec2(TW("Delete Quad2D"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete Quad2D", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	positions = VPC::calculateButtonPositions(4, CH);
	leftWindow->createScreen("quad2dEditorMenuChoice");
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("diffuseMap", fvec2(0.0f, positions[0]), fvec2(TW("Diffuse Map"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Diffuse Map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("color", fvec2(0.0f, positions[1]), fvec2(TW("Color"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("opacity", fvec2(0.0f, positions[2]), fvec2(TW("Opacity"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Opacity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[3]), fvec2(TW("Go Back"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
}

void Quad2dEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("quad2dEditorMenuMain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("quad2dEditorMenuChoice");
}

void Quad2dEditor::update()
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