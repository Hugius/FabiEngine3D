#include "billboard_editor.hpp"

void BillboardEditor::update()
{
	if (_isLoaded)
	{
		_updateBillboardManagement();
		_updateBillboardCreation();
		_updateBillboardChoosing();
		_updateBillboardEditing();
	}
}

void BillboardEditor::_updateBillboardManagement()
{
	auto screen = _window->getScreen("billboardManagement");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("addBillboard")->isHovered()) // Add billboard button
		{
			//_gui->getGlobalScreen()->addValueForm("newBillboardName", "New billboard name", "", vec2(0.0f));
			_billboardCreationEnabled = true;
		}
		else if (screen->getButton("editBillboard")->isHovered()) // Edit billboard button
		{
			_billboardEditingEnabled = true;
			_window->setActiveScreen("BillboardChoice");
		}
		else if (screen->getButton("deleteBillboard")->isHovered()) // Deelete billboard button
		{
			_billboardRemovalEnabled = true;
			_window->setActiveScreen("BillboardChoice");
		}
		else if (screen->getButton("back")->isHovered()) // Back button
		{
			_gui->getGlobalScreen()->addAnswerForm("exitBillboardEditor", "Save changes?", vec2(0.0f, 0.25f));
		}
	}

	// Check if user wants to save changes
	if (_gui->getGlobalScreen()->checkAnswerFormConfirmed("exitBillboardEditor"))
	{
		save();
		_window->setActiveScreen("main");
		unload();
	}
	else if (_gui->getGlobalScreen()->checkAnswerFormDeclined("exitBillboardEditor"))
	{
		_window->setActiveScreen("main");
		unload();
	}
}

void BillboardEditor::_updateBillboardCreation()
{
	string newBillboardName = "";
	//_gui->getGlobalScreen()->checkValueForm("newBillboardName", newBillboardName);
}

void BillboardEditor::_updateBillboardChoosing()
{

}

void BillboardEditor::_updateBillboardEditing()
{

}