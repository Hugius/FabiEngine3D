#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "quad2d_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void Quad2dEditor::_load()
{
	_fe3d->camera_setYaw(270.0f);

	_gui->getOverlay()->createTextField("quad2dId", fvec2(0.0f, 0.85f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
}

void Quad2dEditor::_unload()
{
	for(const auto & quad2dId : _loadedQuad2dIds)
	{
		_fe3d->quad2d_delete(quad2dId);
	}

	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField("quad2dId");

	_loadedQuad2dIds.clear();
}

void Quad2dEditor::_loadGUI()
{
	const auto window = _gui->getLeftViewport()->getWindow("main");

	auto positions = Mathematics::calculateDistributedPositions(4, CH, false);
	window->createScreen("quad2dEditorMenuMain");
	window->getScreen("quad2dEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create Quad2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Quad2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("quad2dEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Quad2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Quad2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("quad2dEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete Quad2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Quad2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("quad2dEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Mathematics::calculateDistributedPositions(8, CH, false);
	window->createScreen("quad2dEditorMenuChoice");
	window->getScreen("quad2dEditorMenuChoice")->createButton("diffuseMap", fvec2(0.0f, positions[0]), TEXT_SIZE("Diffuse Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Diffuse Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("quad2dEditorMenuChoice")->createButton("color", fvec2(0.0f, positions[1]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("quad2dEditorMenuChoice")->createButton("opacity", fvec2(0.0f, positions[2]), TEXT_SIZE("Opacity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Opacity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("quad2dEditorMenuChoice")->createButton("textureRepeat", fvec2(0.0f, positions[3]), TEXT_SIZE("Texture Repeat"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texture Repeat", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("quad2dEditorMenuChoice")->createButton("isHorizontallyFlipped", fvec2(0.0f, positions[4]), TEXT_SIZE("Flipped X: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Flipped X: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("quad2dEditorMenuChoice")->createButton("isVerticallyFlipped", fvec2(0.0f, positions[5]), TEXT_SIZE("Flipped Y: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Flipped Y: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	window->getScreen("quad2dEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[6]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
}

void Quad2dEditor::_unloadGUI()
{
	const auto window = _gui->getLeftViewport()->getWindow("main");

	window->deleteScreen("quad2dEditorMenuMain");
	window->deleteScreen("quad2dEditorMenuChoice");
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
		_updateQuad2dCreating();
	}
	if(isLoaded())
	{
		_updateQuad2dChoosing();
	}
	if(isLoaded())
	{
		_updateQuad2dDeleting();
	}
}