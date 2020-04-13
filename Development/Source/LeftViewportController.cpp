#include "LeftViewportController.hpp"

LeftViewportController::LeftViewportController(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	ViewportController(fe3d, gui),
	_modelEditor(fe3d, gui)
{

}

void LeftViewportController::update(float delta)
{
	_modelEditor.update(delta);

	//// Check if LMB pressed
	//if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	//{
	//	if (_activeScreenID == "mainScreen") // Main screen
	//	{
	//		if (_hoveredItemID == "modelEditor")
	//		{
	//			_gui->getViewport("leftViewport")->getWindow("mainWindow")->setActiveScreen("modelManagementScreen");
	//			_modelEditorEnabled = true;
	//		}
	//		else if (_hoveredItemID == "worldEditor")
	//		{
	//			_worldlEditorEnabled = true;
	//		}
	//		else if (_hoveredItemID == "placingEditor")
	//		{
	//			_placingEditorEnabled = true;
	//		}
	//		else if (_hoveredItemID == "lightingEditor")
	//		{
	//			_lightingEditorEnabled = true;
	//		}
	//		else if (_hoveredItemID == "scriptEditor")
	//		{
	//			_scriptEditorEnabled = true;
	//		}
	//	}
	//}
}