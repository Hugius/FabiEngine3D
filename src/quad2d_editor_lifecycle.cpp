#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "quad2d_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void Quad2dEditor::_load()
{
	_fe3d->camera_setYaw(270.0f);

	_gui->getOverlay()->createTextField("quadId", fvec2(0.0f, 0.85f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
}

void Quad2dEditor::_unload()
{
	_fe3d->camera_reset();

	for(const auto & id : _loadedEntityIds)
	{
		_fe3d->quad2d_delete(id);
	}

	_gui->getOverlay()->deleteTextField("quadId");

	_loadedEntityIds.clear();
	_currentQuadId = "";
	_hoveredQuadId = "";
}

void Quad2dEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = Mathematics::calculateDistributedPositions(4, CH, false);
	leftWindow->createScreen("quad2dEditorMenuMain");
	leftWindow->getScreen("quad2dEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create Quad2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Quad2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Quad2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Quad2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete Quad2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Quad2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(8, CH, false);
	leftWindow->createScreen("quad2dEditorMenuChoice");
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("diffuseMap", fvec2(0.0f, positions[0]), TEXT_SIZE("Diffuse Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Diffuse Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("color", fvec2(0.0f, positions[1]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("opacity", fvec2(0.0f, positions[2]), TEXT_SIZE("Opacity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Opacity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("textureRepeat", fvec2(0.0f, positions[3]), TEXT_SIZE("Texture Repeat"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texture Repeat", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("isHorizontallyFlipped", fvec2(0.0f, positions[4]), TEXT_SIZE("Flipped X: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Flipped X: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("isVerticallyFlipped", fvec2(0.0f, positions[5]), TEXT_SIZE("Flipped Y: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Flipped Y: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[6]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
}

void Quad2dEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("quad2dEditorMenuMain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("quad2dEditorMenuChoice");
}

void Quad2dEditor::update()
{
	if(isLoaded())
	{
		_updateMainMenu();
	}
	if(isLoaded())
	{
		_updateChoiceMenu();
	}
	if(isLoaded())
	{
		_updateQuadCreating();
	}
	if(isLoaded())
	{
		_updateQuadChoosing();
	}
	if(isLoaded())
	{
		_updateQuadDeleting();
	}
}