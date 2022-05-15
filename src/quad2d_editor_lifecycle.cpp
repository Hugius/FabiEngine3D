#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)
#define POSITIONS(count) Mathematics::calculateDistributedPositions(count, CH, false)

#include "quad2d_editor.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void Quad2dEditor::_load()
{
	_fe3d->camera_setYaw(CAMERA_YAW);

	_gui->getOverlay()->createTextField(QUAD2D_TEXT_ID, QUAD2D_TEXT_POSITION, QUAD2D_TEXT_SIZE, "", fvec3(1.0f), true);
}

void Quad2dEditor::_unload()
{
	for(const auto & quad2dId : _loadedQuad2dIds)
	{
		_fe3d->quad2d_delete(quad2dId);
	}

	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField(QUAD2D_TEXT_ID);

	_loadedQuad2dIds.clear();
}

void Quad2dEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	leftWindow->createScreen("quad2dEditorMenuMain");
	leftWindow->getScreen("quad2dEditorMenuMain")->createButton("create", fvec2(0.0f, POSITIONS(4)[0]), TEXT_SIZE("Create Quad2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Quad2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuMain")->createButton("edit", fvec2(0.0f, POSITIONS(4)[1]), TEXT_SIZE("Edit Quad2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Quad2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuMain")->createButton("delete", fvec2(0.0f, POSITIONS(4)[2]), TEXT_SIZE("Delete Quad2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Quad2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuMain")->createButton("back", fvec2(0.0f, POSITIONS(4)[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->createScreen("quad2dEditorMenuChoice");
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("diffuseMap", fvec2(0.0f, POSITIONS(7)[0]), TEXT_SIZE("Diffuse Map"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Diffuse Map", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("color", fvec2(0.0f, POSITIONS(7)[1]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("opacity", fvec2(0.0f, POSITIONS(7)[2]), TEXT_SIZE("Opacity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Opacity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("textureRepeat", fvec2(0.0f, POSITIONS(7)[3]), TEXT_SIZE("Texture Repeat"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Texture Repeat", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("isHorizontallyFlipped", fvec2(0.0f, POSITIONS(7)[4]), TEXT_SIZE("Flipped X: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Flipped X: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("isVerticallyFlipped", fvec2(0.0f, POSITIONS(7)[5]), TEXT_SIZE("Flipped Y: OFF"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Flipped Y: OFF", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("quad2dEditorMenuChoice")->createButton("back", fvec2(0.0f, POSITIONS(7)[6]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("quad2dEditorMenuMain");

	rightWindow->setActiveScreen("empty");
}

void Quad2dEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	leftWindow->deleteScreen("quad2dEditorMenuMain");
	leftWindow->deleteScreen("quad2dEditorMenuChoice");

	leftWindow->setActiveScreen("main");
	rightWindow->setActiveScreen("main");
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