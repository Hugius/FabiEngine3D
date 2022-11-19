#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)
#define POSITIONS(count) Mathematics::calculateDistributedPositions(count, CH, false)

#include "captor_editor.hpp"
#include "tools.hpp"

void CaptorEditor::_load()
{
	_gui->getOverlay()->createTextField(CAPTOR_TITLE_ID, CAPTOR_TITLE_POSITION, CAPTOR_TITLE_SIZE, "", fvec3(1.0f), true);
}

void CaptorEditor::_unload()
{
	for(const auto & captorId : _loadedCaptorIds)
	{
		_fe3d->captor_delete(captorId);
	}

	_gui->getOverlay()->deleteTextField(CAPTOR_TITLE_ID);

	_loadedCaptorIds.clear();
}

void CaptorEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	rightWindow->createScreen("captorEditorMenuMain");
	rightWindow->getScreen("captorEditorMenuMain")->createButton("create", fvec2(0.0f, POSITIONS(4)[0]), TEXT_SIZE("Create Captor"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Captor", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("captorEditorMenuMain")->createButton("edit", fvec2(0.0f, POSITIONS(4)[1]), TEXT_SIZE("Edit Captor"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Captor", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("captorEditorMenuMain")->createButton("delete", fvec2(0.0f, POSITIONS(4)[2]), TEXT_SIZE("Delete Captor"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Captor", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("captorEditorMenuMain")->createButton("back", fvec2(0.0f, POSITIONS(4)[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("captorEditorMenuChoice");
	rightWindow->getScreen("captorEditorMenuChoice")->createButton("reflectionQuality", fvec2(0.0f, POSITIONS(3)[0]), TEXT_SIZE("Reflection Quality"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Reflection Quality", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("captorEditorMenuChoice")->createButton("refractionQuality", fvec2(0.0f, POSITIONS(3)[1]), TEXT_SIZE("Refraction Quality"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Refraction Quality", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("captorEditorMenuChoice")->createButton("back", fvec2(0.0f, POSITIONS(3)[2]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("empty");

	rightWindow->setActiveScreen("captorEditorMenuMain");
}

void CaptorEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	rightWindow->deleteScreen("captorEditorMenuMain");
	rightWindow->deleteScreen("captorEditorMenuChoice");

	leftWindow->setActiveScreen("main");

	rightWindow->setActiveScreen("main");
}

void CaptorEditor::_update()
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
		_updateCaptorCreating();
	}

	if(isLoaded())
	{
		_updateCaptorChoosing();
	}

	if(isLoaded())
	{
		_updateCaptorDeleting();
	}
}