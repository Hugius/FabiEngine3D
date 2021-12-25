#include "billboard_editor.hpp"

void BillboardEditor::_updateMainMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "billboardEditorMenuMain")
	{
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused())) // Back button
		{
			_gui.getOverlay()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui.getOverlay()->createValueForm("billboardCreate", "Create Billboard", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingBillboard = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto IDs = getLoadedIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getOverlay()->createChoiceForm("billboardList", "Edit Billboard", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingBillboard = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto IDs = getLoadedIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getOverlay()->createChoiceForm("billboardList", "Delete Billboard", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingBillboard = true;
			_isDeletingBillboard = true;
		}

		if(_gui.getOverlay()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveToFile();
			unload();
			return;
		}
		if(_gui.getOverlay()->isAnswerFormDenied("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void BillboardEditor::_updateChoiceMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "billboardEditorMenuChoice")
	{
		auto size = _fe3d.billboard_getSize(_currentBillboardID);

		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_fe3d.billboard_setWireframed(_currentBillboardID, false);
			_fe3d.billboard_setVisible(_currentBillboardID, false);
			_fe3d.text_setVisible(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), false);
			_currentBillboardID = "";
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuMain");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui.getOverlay()->createValueForm("sizeX", "X", (size.x * 100.0f), fvec2(-0.15f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getOverlay()->createValueForm("sizeY", "Y", (size.y * 100.0f), fvec2(0.15f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("texturing")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuTexturing");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lighting")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuLighting");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("miscellaneous")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuMiscellaneous");
		}

		if(_gui.getOverlay()->checkValueForm("sizeX", size.x, {0.0f}))
		{
			size.x /= 100.0f;
			_fe3d.billboard_setSize(_currentBillboardID, size);
		}
		if(_gui.getOverlay()->checkValueForm("sizeY", size.y, {0.0f}))
		{
			size.y /= 100.0f;
			_fe3d.billboard_setSize(_currentBillboardID, size);
		}
	}
}